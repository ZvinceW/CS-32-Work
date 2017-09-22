#include "provided.h"
#include "MyMap.h"
#include <vector>
using namespace std;

class SegmentMapperImpl
{
public:
	SegmentMapperImpl();
	~SegmentMapperImpl();
	void init(const MapLoader& ml);
	vector<StreetSegment> getSegments(const GeoCoord& gc) const;
private:
	MyMap<string, vector<StreetSegment>> m_segMap;
};

SegmentMapperImpl::SegmentMapperImpl()
{
}

SegmentMapperImpl::~SegmentMapperImpl()
{
}

void SegmentMapperImpl::init(const MapLoader& ml)
{
	for (unsigned int i = 0; i < ml.getNumSegments(); i++)
	{
		StreetSegment currentSeg;
		ml.getSegment(i, currentSeg);
		//combine the lat and lon of a coord into one string
		string startCoord = currentSeg.segment.start.latitudeText + currentSeg.segment.start.longitudeText;
		string endCoord = currentSeg.segment.end.latitudeText + currentSeg.segment.end.longitudeText;
		vector<StreetSegment>* startFinding = m_segMap.find(startCoord);
		vector<StreetSegment>* endFinding = m_segMap.find(endCoord);
		if (startFinding != nullptr) //if the coordinate already exists
		{
			startFinding->push_back(currentSeg);
		}
		else
		{
			vector<StreetSegment> insert;
			insert.push_back(currentSeg);
			m_segMap.associate(startCoord, insert);
		}
		if (endFinding != nullptr)
		{
			endFinding->push_back(currentSeg);
		}
		else
		{
			vector<StreetSegment> insert;
			insert.push_back(currentSeg);
			m_segMap.associate(endCoord, insert);
		}
		for (unsigned int j = 0; j < currentSeg.attractions.size(); j++)
		{
			Attraction currentAttract = currentSeg.attractions[j];
			string attractCoord = currentAttract.geocoordinates.latitudeText + currentAttract.geocoordinates.longitudeText;
			vector<StreetSegment>* attractFinding = m_segMap.find(attractCoord);
			if (attractFinding != nullptr)
			{
				attractFinding->push_back(currentSeg);
			}
			else
			{
				vector<StreetSegment> insert;
				insert.push_back(currentSeg);
				m_segMap.associate(attractCoord, insert);
			}
		}
	}
}

vector<StreetSegment> SegmentMapperImpl::getSegments(const GeoCoord& gc) const
{
	vector<StreetSegment> result;
	string keyCoord = gc.latitudeText + gc.longitudeText;
	const vector<StreetSegment>* finding = m_segMap.find(keyCoord);
	if (finding == nullptr) //if nothing is associated with gc
	{
		return result; //return empty vector
	}
	else //if something is associated with gc
	{
		result = *finding; //set result equal to the vector found
		return result;
	}
}

//******************** SegmentMapper functions ********************************

// These functions simply delegate to SegmentMapperImpl's functions.
// You probably don't want to change any of this code.

SegmentMapper::SegmentMapper()
{
	m_impl = new SegmentMapperImpl;
}

SegmentMapper::~SegmentMapper()
{
	delete m_impl;
}

void SegmentMapper::init(const MapLoader& ml)
{
	m_impl->init(ml);
}

vector<StreetSegment> SegmentMapper::getSegments(const GeoCoord& gc) const
{
	return m_impl->getSegments(gc);
}
