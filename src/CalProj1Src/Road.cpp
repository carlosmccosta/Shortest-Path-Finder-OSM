#include "Road.h"


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <static variables init>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
unsigned int Road::roadIDCounter = 0;
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </static variables init>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <constructors-destructors>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
Road::Road() :
		roadID(++roadIDCounter), roadName("unknown"), oneWayRoad(false) {}

Road::Road(unsigned int _roadID, string _roadName, bool _oneWayRoad) :
		roadID(_roadID), roadName(_roadName), oneWayRoad(_oneWayRoad) { ++roadIDCounter; }

Road::~Road() {}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </constructors-destructors>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <Road management>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void Road::addSubRoad(SubRoad* newSubRoad) {
	StreetSubRoads.insert(newSubRoad);
}

bool Road::removeSubRoad(SubRoad* subRoadToRemove) {
	return (StreetSubRoads.erase(subRoadToRemove) == 0)? false : true;
}

bool Road::removeSubRoad(unsigned int subRoadIDToRemove) {
	for (set<SubRoad*>::iterator it = StreetSubRoads.begin(); it != StreetSubRoads.end(); ++it) {
		if ((*it)->getSubRoadID() == subRoadIDToRemove) {
			StreetSubRoads.erase(it);
			return true;
		}
	}

	return false;
}

bool Road::operator<(const Road* road) const {
	return this->roadID < road->getRoadID();
}

bool Road::operator==(const Road* road) const {
	return this->roadID == road->getRoadID();
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </Road management>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <gets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
bool Road::getOneWayRoad() const {
	return oneWayRoad;
}

unsigned int Road::getRoadID() const {
	return roadID;
}

unsigned int Road::getRoadIDCounter() {
	return roadIDCounter;
}

string Road::getRoadName() const {
	return roadName;
}

set<SubRoad*, SubRoad::functorToSortSubRoadsByID>& Road::getStreetSubRoads() {
	return StreetSubRoads;
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </gets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <sets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void Road::setOneWayRoad(bool oneWayRoad) {
	this->oneWayRoad = oneWayRoad;
}

void Road::setRoadID(unsigned int roadID) {
	this->roadID = roadID;
}

void Road::setRoadIDCounter(unsigned int roadIDCounter) {
	Road::roadIDCounter = roadIDCounter;
}

void Road::setRoadName(string roadName) {
	this->roadName = roadName;
}

void Road::setStreetSubRoads(set<SubRoad*, SubRoad::functorToSortSubRoadsByID> StreetSubRoads) {
	this->StreetSubRoads = StreetSubRoads;
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </sets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
