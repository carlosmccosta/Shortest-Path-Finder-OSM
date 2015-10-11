#ifndef NODE_H_
#define NODE_H_

#include <vector>
#include <string>

#include "SubRoad.h"
#include "defs.h"

using std::vector;
using std::string;


//################################################################   Node   #######################################################################
/**
 * Classe que representa um n� no grafo, com as liga��es que esse n� tem com os restantes n�s do mapa,
 * bem como informa��es para possibilitar a sua correcta visualiza��o no GraphViewer.
 */
class Node {
private:
//=============================================================   <private>   =====================================================================
	//Contador dos n�meros de n�s criados at� ao momento
	static unsigned int nodeIDCounter;

	unsigned int nodeID;
	int latitude;
	int longitude;
	int longitudeProjection;						///< Posi��o no x na janela do GraphViewer
	int latitudeProjection;							///< Posi��o no y na janela do GraphViewer

	unsigned int cumulativeDistanceToSourceNode;	///< dist�ncia deste Node ao Node inicial
	unsigned int cumulativeTimeToSourceNode;		///< tempo que demora a chegar deste Node ao Node inicial

	Node* pathToSourceNode;							///< N� que num caminho que chega ao n� de inicio da pesquisa

	bool visited;									///< N� que indica se o n� j� foi visitado (usado no algiritmo de Dijkstra)

	string nodeColor;
	string nodeLabel;

	vector <SubRoad*> conectedSubRoads;				///< vector que cont�m as liga��es (SubRoads), que este Node tem com os restantes nodes do mapa
//=============================================================   </private>   ===================================================================


//==============================================================   <public>   ====================================================================
public:
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <constructors-destructors>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	Node();
	Node(unsigned int _nodeID, unsigned int _latitude, unsigned int _longitude, unsigned int _longitudeProjection, unsigned int _latitudeProjection);
	virtual ~Node();
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </constructors-destructors>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <auxiliary structs>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	struct functorToOrderNodeSet {
		bool operator()(const Node* node1, const Node* node2) const {
			return (node1->getNodeID() > node2->getNodeID());
		}
	};

	struct functorToMakeNodeHeapByCumulativeDistance {
		bool operator()(const Node* node1, const Node* node2) const {
			return (node1->getCumulativeDistanceToSourceNode() > node2->getCumulativeDistanceToSourceNode());
		}
	};

	struct functorToMakeNodeHeapByCumulativeTime {
		bool operator()(const Node* node1, const Node* node2) const {
			return (node1->getCumulativeTimeToSourceNode() > node2->getCumulativeTimeToSourceNode());
		}
	};
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </auxiliary structs>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <Node management>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	void addSubRoad(SubRoad* newSubRoad);
	bool removeSubRoad(unsigned int subRoadIDToRemove);
	bool operator<(const Node* node) const;
	bool operator<(const Node node) const;
	bool operator==(const Node* node) const;
	bool operator==(const Node node) const;
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </Node management>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <gets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    vector<SubRoad*>& getConectedSubRoads();
    unsigned int getCumulativeDistanceToSourceNode() const;
    unsigned int getCumulativeTimeToSourceNode() const;
    int getLatitude() const;
    int getLatitudeProjection() const;
    int getLongitude() const;
    int getLongitudeProjection() const;
    unsigned int getNodeID() const;
    static unsigned int getNodeIDCounter();
    Node *getPathToSourceNode() const;
    bool getVisited() const;
    string getNodeColor() const;
    string getNodeLabel() const;
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </gets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <sets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    void setConectedSubRoads(const vector<SubRoad*>& conectedSubRoads);
    void setCumulativeDistanceToSourceNode(unsigned int cumulativeDistanceToSourceNode);
    void setCumulativeTimeToSourceNode(unsigned int cumulativeTimeToSourceNode);
    void setLatitude(int latitude);
    void setLatitudeProjection(int latitudeProjection);
    void setLongitude(int longitude);
    void setLongitudeProjection(int longitudeProjection);
    void setNodeID(unsigned int nodeID);
    static void setNodeIDCounter(unsigned int nodeIDCounter);
    void setPathToSourceNode(Node *pathToSourceNode);
    void setVisited(bool visited);
    void setNodeColor(string nodeColor);
    void setNodeLabel(string nodeLabel);
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </sets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


    //==============================================================   </public>   ===================================================================
};

#endif /* NODE_H_ */
