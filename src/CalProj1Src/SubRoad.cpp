#include "SubRoad.h"


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <static variables init>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
unsigned int SubRoad::SubRoadIDCounter = 0;
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </static variables init>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <constructors-destructors>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
SubRoad::SubRoad() :
		subRoadID(++SubRoadIDCounter), RoadID(0), sourceNodeID(0), destinationNodeID(0),
		lenght(0), timeToTravel(1), sourceNode(NULL), destinationNode(NULL),
		subRoadColor((string)SUBROAD_DEFAULT_COLOR), subRoadLabel(""), labelIsStreatName(false) {}

SubRoad::SubRoad(unsigned int _RoadID, unsigned int _sourceNodeID, unsigned int _destinationNodeID) :
		subRoadID(++SubRoadIDCounter), RoadID(_RoadID), sourceNodeID(_sourceNodeID), destinationNodeID(_destinationNodeID),
		lenght(0), timeToTravel(1), sourceNode(NULL), destinationNode(NULL),
		subRoadColor((string)SUBROAD_DEFAULT_COLOR), subRoadLabel(""), labelIsStreatName(false) {}

SubRoad::~SubRoad() {}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </constructors-destructors>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <SubRoad management>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
bool SubRoad::operator<(const SubRoad* subRoad) const {
	return subRoadID < subRoad->getSubRoadID();
}

bool SubRoad::operator==(const SubRoad* subRoad) const {
	return subRoadID == subRoad->getSubRoadID();
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </SubRoad management>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <gets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
unsigned int SubRoad::getRoadID() const {
	return RoadID;
}

Node *SubRoad::getDestinationNode() const {
	return destinationNode;
}

unsigned int SubRoad::getDestinationNodeID() const {
	return destinationNodeID;
}

int SubRoad::getLenght() const {
	return lenght;
}

Node *SubRoad::getSourceNode() const {
	return sourceNode;
}

unsigned int SubRoad::getSourceNodeID() const {
	return sourceNodeID;
}

unsigned int SubRoad::getSubRoadID() const {
	return subRoadID;
}

unsigned int SubRoad::getSubRoadIDCounter() {
	return SubRoadIDCounter;
}

int SubRoad::getTimeToTravel() const {
	return timeToTravel;
}

string SubRoad::getSubRoadColor() const {
	return subRoadColor;
}

string SubRoad::getSubRoadLabel() const {
	return subRoadLabel;
}

bool SubRoad::getLabelIsStreatName() const {
	return labelIsStreatName;
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </gets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <sets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void SubRoad::setRoadID(unsigned int RoadID) {
	this->RoadID = RoadID;
}

void SubRoad::setDestinationNode(Node *destinationNode) {
	this->destinationNode = destinationNode;
}

void SubRoad::setDestinationNodeID(unsigned int destinationNodeID) {
	this->destinationNodeID = destinationNodeID;
}

void SubRoad::setLenght(int lenght) {
	this->lenght = lenght;
}

void SubRoad::setSourceNode(Node *sourceNode) {
	this->sourceNode = sourceNode;
}

void SubRoad::setSourceNodeID(unsigned int sourceNodeID) {
	this->sourceNodeID = sourceNodeID;
}

void SubRoad::setSubRoadID(unsigned int subRoadID) {
	this->subRoadID = subRoadID;
}

void SubRoad::setSubRoadIDCounter(unsigned int SubRoadIDCounter) {
	SubRoad::SubRoadIDCounter = SubRoadIDCounter;
}

void SubRoad::setTimeToTravel(int timeToTravel) {
	this->timeToTravel = timeToTravel;
}

void SubRoad::setSubRoadColor(string subRoadColor) {
	this->subRoadColor = subRoadColor;
}

void SubRoad::setSubRoadLabel(string subRoadLabel) {
	this->subRoadLabel = subRoadLabel;
}

void SubRoad::setLabelIsStreatName(bool labelIsStreatName) {
	this->labelIsStreatName = labelIsStreatName;
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </sets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
