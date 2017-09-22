#include "provided.h"
#include "MyMap.h"
#include <string>
//#include <iostream> //debug
using namespace std;

class AttractionMapperImpl
{
public:
	AttractionMapperImpl();
	~AttractionMapperImpl();
	void init(const MapLoader& ml);
	bool getGeoCoord(string attraction, GeoCoord& gc) const;
private:
	MyMap<string, GeoCoord> m_attractMap;
};

AttractionMapperImpl::AttractionMapperImpl()
{
}

AttractionMapperImpl::~AttractionMapperImpl()
{
}

void AttractionMapperImpl::init(const MapLoader& ml)
{
	for (unsigned int i = 0; i < ml.getNumSegments(); i++)
	{
		StreetSegment currentSeg;
		ml.getSegment(i, currentSeg);
		for (unsigned int j = 0; j < currentSeg.attractions.size(); j++)
		{
			string name = currentSeg.attractions[j].name;
			string lowerName;
			for (unsigned int k = 0; k < name.size(); k++) //make the attraction name all lowercase so its easy to compare later, maybe not OK?
			{
				lowerName += tolower(name[k]);
			}
			//cout << lowerName << endl; //debug
			m_attractMap.associate(lowerName, currentSeg.attractions[j].geocoordinates);
		}
	}
}

bool AttractionMapperImpl::getGeoCoord(string attraction, GeoCoord& gc) const
{
	string name = attraction;
	string lowerName;
	for (unsigned int k = 0; k < name.size(); k++) //make the attraction name all lowercase so its easy to compare later, maybe not OK?
	{
		lowerName += tolower(name[k]);
	}
	const GeoCoord* finding = m_attractMap.find(lowerName);
	if (finding != nullptr) //all the names in map are already lowercase, so u need to find it with something thats also all lowercase
	{
		gc = *finding;
		return true;
	}
	else
	{
		return false;
	}
}

//******************** AttractionMapper functions *****************************

// These functions simply delegate to AttractionMapperImpl's functions.
// You probably don't want to change any of this code.

AttractionMapper::AttractionMapper()
{
	m_impl = new AttractionMapperImpl;
}

AttractionMapper::~AttractionMapper()
{
	delete m_impl;
}

void AttractionMapper::init(const MapLoader& ml)
{
	m_impl->init(ml);
}

bool AttractionMapper::getGeoCoord(string attraction, GeoCoord& gc) const
{
	return m_impl->getGeoCoord(attraction, gc);
}
