#include "provided.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class MapLoaderImpl
{
public:
	MapLoaderImpl();
	~MapLoaderImpl();
	bool load(string mapFile);
	size_t getNumSegments() const;
	bool getSegment(size_t segNum, StreetSegment& seg) const;
private:
	vector<StreetSegment> m_segments;
	//int m_numSegments;
};

MapLoaderImpl::MapLoaderImpl()
{
}

MapLoaderImpl::~MapLoaderImpl()
{
}

bool MapLoaderImpl::load(string mapFile)
{
	//mapFile = "mapdata.txt";
	ifstream infile(mapFile);
	if (!infile)
	{
		cerr << "FILE DIDNT LOAD CORRECTLY" << endl;
		return false;
	}
	string streetName;
	while (getline(infile, streetName))
	{
		string lat1, space, lon1, lat2, lon2;
		StreetSegment currentSeg;
		currentSeg.streetName = streetName;
		//string lat1, lat2, lon1, lon2, ran;
		getline(infile, lat1, ',');
		getline(infile, space, ' '); //trash string, ignore
		getline(infile, lon1, ' ');
		getline(infile, lat2, ',');
		getline(infile, lon2, '\n');
		GeoCoord coordStart(lat1, lon1);
		GeoCoord coordEnd(lat2, lon2);
		GeoSegment geoSeg(coordStart, coordEnd);
		currentSeg.segment = geoSeg;
		int numOfAttract;
		infile >> numOfAttract;
		infile.ignore(10000, '\n');
		vector<Attraction> attractList;
		for (int i = 0; i < numOfAttract; i++)
		{
			string attractName, attractLat, attractLon;
			getline(infile, attractName, '|');
			getline(infile, attractLat, ',');
			getline(infile, space, ' ');
			getline(infile, attractLon, '\n');
			GeoCoord attractCoord(attractLat, attractLon);
			Attraction attract;
			attract.name = attractName;
			attract.geocoordinates = attractCoord;
			attractList.push_back(attract);
		}
		currentSeg.attractions = attractList;
		m_segments.push_back(currentSeg);
	}
	cout << "maploading done" << endl; //debug
	return true;
}

size_t MapLoaderImpl::getNumSegments() const
{
	return m_segments.size(); // This compiles, but may not be correct
}

bool MapLoaderImpl::getSegment(size_t segNum, StreetSegment &seg) const
{
	if (segNum < 0 || segNum > m_segments.size() - 1)
		return false;
	seg = m_segments[segNum];
	return true;
}

//******************** MapLoader functions ************************************

// These functions simply delegate to MapLoaderImpl's functions.
// You probably don't want to change any of this code.

MapLoader::MapLoader()
{
	m_impl = new MapLoaderImpl;
}

MapLoader::~MapLoader()
{
	delete m_impl;
}

bool MapLoader::load(string mapFile)
{
	return m_impl->load(mapFile);
}

size_t MapLoader::getNumSegments() const
{
	return m_impl->getNumSegments();
}

bool MapLoader::getSegment(size_t segNum, StreetSegment& seg) const
{
	return m_impl->getSegment(segNum, seg);
}
