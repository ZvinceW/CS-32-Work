#include "provided.h"
#include <string>
#include <vector>
#include "MyMap.h"
#include <queue>
#include <stack>
#include "support.h"
//#include <iostream>
using namespace std;



class NavigatorImpl
{
public:
    NavigatorImpl();
    ~NavigatorImpl();
    bool loadMapData(string mapFile);
    NavResult navigate(string start, string end, vector<NavSegment>& directions) const;
private:
	string translateDir(double angle) const ;
	vector<NavSegment> generateDirList( GeoCoord& start,  GeoCoord& end, vector<GeoCoord> routeList);
	vector<NavSegment> generateNavSeg(GeoCoord & first,  GeoCoord & second,  GeoCoord & third, GeoCoord & begin, GeoCoord & end) const;
	SegmentMapper m_segMapper;
	AttractionMapper m_attrMapper;
	MapLoader m_mapLoader;
	//MyMap<string, StreetSegment> m_traveledStreet;
};

NavigatorImpl::NavigatorImpl()
{
}

NavigatorImpl::~NavigatorImpl()
{
}

bool NavigatorImpl::loadMapData(string mapFile)
{
	if (!m_mapLoader.load(mapFile))
		return false;
	//cout << "loading segmap";
	m_segMapper.init(m_mapLoader);
	m_attrMapper.init(m_mapLoader);
	return true;  // This compiles, but may not be correct
}

NavResult NavigatorImpl::navigate(string start, string end, vector<NavSegment> &directions) const
{
	MyMap<GeoCoord, GeoCoord> backTrackMap;
	if (directions.size() > 0) //clear the vector if its not empty
	{
		for (int i = directions.size() - 1; i >= 0; i--)
			directions.erase(directions.begin() + i);
	}
	queue<GeoCoord> pathFinder;
	GeoCoord startCoord;
	if (!m_attrMapper.getGeoCoord(start, startCoord))
		return NAV_BAD_SOURCE;
	GeoCoord endCoord;
	if (!m_attrMapper.getGeoCoord(end, endCoord))
		return NAV_BAD_DESTINATION;
	//cout << endCoord.latitudeText << endCoord.longitudeText << endl;
	vector<StreetSegment> connectedStreets = m_segMapper.getSegments(startCoord);
	//cout << "got" << endl;
	backTrackMap.associate(connectedStreets[0].segment.start, startCoord);
	backTrackMap.associate(connectedStreets[0].segment.end, startCoord);
	pathFinder.push(startCoord);
	bool pathExist = false;
	GeoCoord currentCoord;
	while (!pathFinder.empty() && !pathExist)
	{
		//cout << "Q size: " << pathFinder.size() << endl; //DEBUG
		currentCoord = pathFinder.front();
		pathFinder.pop();

		vector<StreetSegment> connectedStreets = m_segMapper.getSegments(currentCoord); //get a vector of streets related to the geoCoord
	//	cout << "connected: " << connectedStreets.size() << endl; //DEBUG
		for (unsigned int i = 0; i < connectedStreets.size(); i++)
		{
			bool startDone = false;
			bool endDone = false;
			//we can use backTrackMap to check if a streetSegment has been visited
			//add coord pairs to backTrackMap
			if (backTrackMap.find(connectedStreets[i].segment.start) != nullptr) {
				startDone = true;
				backTrackMap.associate(connectedStreets[i].segment.start, connectedStreets[i].segment.end); //map the start coord of the StreetSegment to the end coord
			}
			if (backTrackMap.find(connectedStreets[i].segment.end) != nullptr) {
				endDone = true;
				backTrackMap.associate(connectedStreets[i].segment.end, connectedStreets[i].segment.start); //map the end coord of the StreetSegment to the start coord
			}
			//add the geocoord of the other end of the streetSegment into the queue
			if (connectedStreets[i].segment.start == currentCoord)
				pathFinder.push(connectedStreets[i].segment.end);
			else
				pathFinder.push(connectedStreets[i].segment.start);
			if ((!startDone) && (!endDone)) //if both the start and end of a StreetSegment exist in the map, the segment has already been processed, skip it
				continue;
		//	cout << "this street has attraction: " << connectedStreets[i].attractions.size() << endl;
			if (connectedStreets[i].attractions.size() > 0) //check if the segment has attraction
			{
			//	cout << "the street has attractions" << endl; //DEBUG
				for (unsigned int j = 0; j < connectedStreets[i].attractions.size(); j++)
				{
				//	cout << "looping through attractions" << endl; //DEBUG
					//check if the attraction coords match the end coord
					if (connectedStreets[i].attractions[j].geocoordinates == endCoord)
					{
				//		cout << "pathexist" << endl; //DEBUG
						pathExist = true;
						break;
					}
				}
				//no need to store/mark attraction coord because we only need 
				//the start and end of a street to id a streat
			}
			if (pathExist)
				break;
		}
		if (pathExist)
			break;
	}
	if (!pathExist)
	{
		return NAV_NO_ROUTE;
	}

	stack<GeoCoord> routeStack;
	vector<GeoCoord> routeList;
	routeStack.push(endCoord);
	routeStack.push(currentCoord);
	while (!(currentCoord == startCoord)) //generate an in-order list of geoCoords from start to end
	{
		currentCoord = *backTrackMap.find(currentCoord);
		routeStack.push(currentCoord);
	}
	while (!routeStack.empty())
	{
		routeList.push_back(routeStack.top());
		routeStack.pop();
	} //a vector of in-order geoCoord should be now generated

	//after the path is confirmed, reconstuct the path
	//use the start and end of a street to find the streetSegment
	//directions = generateDirList(startCoord, endCoord, routeList);

	vector<NavSegment> dirList;
	for (unsigned int i = 0; i + 3 < routeList.size(); i++)
	{
		vector<NavSegment> shortDirList = generateNavSeg(routeList[i], routeList[i + 2], routeList[i + 3], startCoord, endCoord);
		dirList.insert(dirList.end(), shortDirList.begin(), shortDirList.end()); //append shortDirList to the end of dirList
		i++;
	}
	directions = dirList;
	
	return NAV_SUCCESS;  // This compiles, but may not be correct
}

string NavigatorImpl::translateDir(double angle) const
{
	/*
	0 degrees <= travelAngle <= 22.5 degrees: east 
	22.5 degrees < travelAngle <= 67.5 degrees: northeast 
	67.5 degrees < travelAngle <= 112.5 degrees: north 
	112.5 degrees < travelAngle <= 157.5 degrees: northwest 
	157.5 degrees < travelAngle <= 202.5 degrees: west 
	202.5 degrees < travelAngle <= 247.5 degrees: southwest 
	247.5 degrees < travelAngle <= 292.5 degrees: south 
	292.5 degrees < travelAngle <= 337.5 degrees: southeast
	337.5 degrees < travelAngle < 360 degrees: east
	*/
	if (0 <= angle && angle <= 22.5)
		return "east";
	else if (22.5 < angle && angle <= 67.5)
		return "northeast";
	else if (67.5 < angle && angle <= 112.5)
		return "north";
	else if (112.5 < angle && angle <= 157.5)
		return "northwest";
	else if (157.5 < angle && angle <= 202.5)
		return "west";
	else if (202.5 < angle && angle <= 247.5)
		return "southwest";
	else if (247.5 < angle && angle <= 292.5)
		return "south";
	else if (292.5 < angle && angle <= 337.5)
		return "southeast";
	else if (337.5 < angle && angle < 360)
		return "east";
	else
		return "BAD DIRECTION";
}

vector<NavSegment> NavigatorImpl::generateDirList( GeoCoord & start, GeoCoord & end, vector<GeoCoord> routeList)
{
	vector<NavSegment> dirList;
	for (unsigned int i = 0; i + 3 < routeList.size(); i++)
	{
		vector<NavSegment> shortDirList = generateNavSeg(routeList[i], routeList[i + 2], routeList[i + 3], start, end);
		dirList.insert(dirList.end(), shortDirList.begin(), shortDirList.end()); //append shortDirList to the end of dirList
		i++;
	}
	return dirList;
}

vector<NavSegment> NavigatorImpl::generateNavSeg( GeoCoord & first,  GeoCoord & second,  GeoCoord & third, GeoCoord & begin, GeoCoord & end) const
{
	vector<NavSegment> resultList;
	vector<StreetSegment> streetList = m_segMapper.getSegments(second);
	StreetSegment target;
	StreetSegment nextTarget;
	for (unsigned int i = 0; i < streetList.size(); i++)
	{
		if (streetList[i].segment.start == first && streetList[i].segment.end == second)
		{
			target = streetList[i];
		}
		if (streetList[i].segment.start == second && streetList[i].segment.end == first)
		{
			target = streetList[i];
		}
		if (streetList[i].segment.start == second && streetList[i].segment.end == third)
		{
			nextTarget = streetList[i];
		}
		if (streetList[i].segment.start == third && streetList[i].segment.end == second)
		{
			nextTarget = streetList[i];
		}
	}

	//special action for the very last navSegment
	if (third == end)
	{
		nextTarget = m_segMapper.getSegments(end)[0];
		if (nextTarget.segment.start == second) //adjust one of the boundary coord to the coord of the attraction
			nextTarget.segment.end == end;
		else
			nextTarget.segment.start == end;
	}

	bool isProceed = true;
	if (target.streetName != nextTarget.streetName)
		isProceed = false;

	double angle = angleOfLine(target.segment);
	string direction = translateDir(angle);
	double distance = 0;

	if(first == begin) //special action for generating the very first navSegment
		distance = distanceEarthMiles(first, second);
	else
		distance = distanceEarthMiles(target.segment.start, target.segment.end);

	NavSegment proceed = NavSegment(direction, target.streetName, distance, target.segment);
	resultList.push_back(proceed);

	if (!isProceed)
	{
		double angle = angleBetween2Lines(target.segment, nextTarget.segment);
		string direction;
		if (angle < 180)
			direction = "left";
		else
			direction = "right";
		NavSegment turn = NavSegment(direction, nextTarget.streetName);
		resultList.push_back(turn);
	}

	//special action for the very last navSegment
	if (third == end)
	{
		//basically generate one more proceed segment using nextTarget
		//nextTarget should be the last segment that leads directly to the destination attraction.
		double angle = angleOfLine(nextTarget.segment);
		string direction = translateDir(angle);
		double distance = distanceEarthMiles(nextTarget.segment.start, nextTarget.segment.end);
		NavSegment proceed = NavSegment(direction, nextTarget.streetName, distance, nextTarget.segment);
		resultList.push_back(proceed);
	}

	return resultList;
}

//******************** Navigator functions ************************************

// These functions simply delegate to NavigatorImpl's functions.
// You probably don't want to change any of this code.

Navigator::Navigator()
{
    m_impl = new NavigatorImpl;
}

Navigator::~Navigator()
{
    delete m_impl;
}

bool Navigator::loadMapData(string mapFile)
{
    return m_impl->loadMapData(mapFile);
}

NavResult Navigator::navigate(string start, string end, vector<NavSegment>& directions) const
{
    return m_impl->navigate(start, end, directions);
}
