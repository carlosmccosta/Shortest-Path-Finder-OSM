#include "Node.h"


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <static variables init>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
unsigned int Node::nodeIDCounter = 0;
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </static variables init>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <constructors-destructors>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
Node::Node() :
	nodeID(++nodeIDCounter), latitude(0), longitude(0), longitudeProjection(0), latitudeProjection(0),
	cumulativeDistanceToSourceNode(0), cumulativeTimeToSourceNode(0),
	pathToSourceNode(NULL), visited(false),
	nodeColor((string)NODE_DEFAULT_COLOR) { stringstream label; label << nodeID; nodeLabel = label.str(); }

Node::Node(unsigned int _nodeID, unsigned int _latitude, unsigned int _longitude, unsigned int _longitudeProjection, unsigned int _latitudeProjection) :
		nodeID(_nodeID), latitude(_latitude), longitude(_longitude), longitudeProjection(_longitudeProjection), latitudeProjection(_latitudeProjection),
		cumulativeDistanceToSourceNode(0), cumulativeTimeToSourceNode(0),
		pathToSourceNode(NULL), visited(false),
		nodeColor((string)NODE_DEFAULT_COLOR) { ++nodeIDCounter; stringstream label; label << nodeID; nodeLabel = label.str(); }

Node::~Node() {}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </constructors-destructors>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <Node management>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void Node::addSubRoad(SubRoad* newSubRoad) {
	conectedSubRoads.push_back(newSubRoad);
}

bool Node::removeSubRoad(unsigned int subRoadIDToRemove) {
	for (vector<SubRoad*>::iterator it = conectedSubRoads.begin(); it != conectedSubRoads.end(); ++it) {
		if ((*it)->getSubRoadID() == subRoadIDToRemove) {
			conectedSubRoads.erase(it);
			return true;
		}
	}

	return false;
}

bool Node::operator<(const Node* node) const {
	return nodeID < node->getNodeID();
}

bool Node::operator<(const Node node) const {
	return nodeID < node.getNodeID();
}

bool Node::operator==(const Node* node) const {
	return nodeID == node->getNodeID();
}

bool Node::operator==(const Node node) const {
	return nodeID == node.getNodeID();
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </Node management>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <gets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
vector<SubRoad*>& Node::getConectedSubRoads() {
	return conectedSubRoads;
}

unsigned int Node::getCumulativeDistanceToSourceNode() const {
	return cumulativeDistanceToSourceNode;
}

unsigned int Node::getCumulativeTimeToSourceNode() const {
	return cumulativeTimeToSourceNode;
}

int Node::getLatitude() const {
	return latitude;
}

int Node::getLatitudeProjection() const {
	return latitudeProjection;
}

int Node::getLongitude() const {
	return longitude;
}

int Node::getLongitudeProjection() const {
	return longitudeProjection;
}

unsigned int Node::getNodeID() const {
	return nodeID;
}

unsigned int Node::getNodeIDCounter() {
	return Node::nodeIDCounter;
}

Node *Node::getPathToSourceNode() const {
	return pathToSourceNode;
}

bool Node::getVisited() const {
	return visited;
}

string Node::getNodeColor() const {
	return nodeColor;
}

string Node::getNodeLabel() const {
	return nodeLabel;
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </gets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <sets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void Node::setConectedSubRoads(const vector<SubRoad*>& conectedSubRoads) {
	this->conectedSubRoads = conectedSubRoads;
}

void Node::setCumulativeDistanceToSourceNode(unsigned int cumulativeDistanceToSourceNode) {
	this->cumulativeDistanceToSourceNode = cumulativeDistanceToSourceNode;
}

void Node::setCumulativeTimeToSourceNode(unsigned int cumulativeTimeToSourceNode) {
	this->cumulativeTimeToSourceNode = cumulativeTimeToSourceNode;
}

void Node::setLatitude(int latitude) {
	this->latitude = latitude;
}

void Node::setLatitudeProjection(int latitudeProjection) {
	this->latitudeProjection = latitudeProjection;
}

void Node::setLongitude(int longitude) {
	this->longitude = longitude;
}

void Node::setLongitudeProjection(int longitudeProjection) {
	this->longitudeProjection = longitudeProjection;
}

void Node::setNodeID(unsigned int nodeID) {
	this->nodeID = nodeID;
}

void Node::setNodeIDCounter(unsigned int nodeIDCounter) {
	Node::nodeIDCounter = nodeIDCounter;
}

void Node::setPathToSourceNode(Node *pathToSourceNode) {
	this->pathToSourceNode = pathToSourceNode;
}

void Node::setVisited(bool visited) {
	this->visited = visited;
}

void Node::setNodeColor(string nodeColor) {
	this->nodeColor = nodeColor;
}

void Node::setNodeLabel(string nodeLabel) {
	this->nodeLabel = nodeLabel;
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </sets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
