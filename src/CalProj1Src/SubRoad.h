#ifndef SUBROAD_H_
#define SUBROAD_H_

#include <string>
#include <sstream>
#include <cstddef>

using std::string;
using std::stringstream;

#define SUBROAD_DEFAULT_COLOR "lightGray"
#define SUBROAD_PATH_COLOR "green"
#define SUBROAD_VISITED_COLOR "black"

class Node;

//##############################################################   SubRoad   #####################################################################
/**
 * Classe que representa uma parte de uma rua, ou seja, uma ligação entre dois Nodes
 */
class SubRoad {
//=============================================================   <private>   ====================================================================
private:
	static unsigned int SubRoadIDCounter;	///< Contador do numero de SubRoads criadas até ao momento

	unsigned int subRoadID;

	unsigned int RoadID;
	unsigned int sourceNodeID;
	unsigned int destinationNodeID;

	int lenght;
	int timeToTravel;

	// apontadores para os nós de inicio e fim da SubRoad para melhorar a performance
	Node* sourceNode;
	Node* destinationNode;

	string subRoadColor;
	string subRoadLabel;

	/// flag que indica se nesta SubRoad foi colocada o nome da rua no GraphViewer
	bool labelIsStreatName;
//=============================================================   </private>   ===================================================================


//==============================================================   <public>   ====================================================================
public:
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <constructors-destructors>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	SubRoad();
	SubRoad(unsigned int _subRoadID, unsigned int _sourceNodeID, unsigned int _destinationNodeID);
	virtual ~SubRoad();
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </constructors-destructors>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <auxiliary structs>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	struct functorToSortSubRoadsByID {
		bool operator()(const SubRoad* subRoad1, const SubRoad* subRoad2) const {
			return (subRoad1->getSubRoadID() < subRoad2->getSubRoadID());
		}
	};
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </auxiliary structs>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <SubRoad management>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	bool operator<(const SubRoad* subRoad) const;
	bool operator==(const SubRoad* subRoad) const;
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </SubRoad management>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <gets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	unsigned int getRoadID() const;
	Node *getDestinationNode() const;
    unsigned int getDestinationNodeID() const;
    int getLenght() const;
    Node *getSourceNode() const;
    unsigned int getSourceNodeID() const;
    unsigned int getSubRoadID() const;
    static unsigned int getSubRoadIDCounter();
    int getTimeToTravel() const;
    string getSubRoadColor() const;
    string getSubRoadLabel() const;
    bool getLabelIsStreatName() const;
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </gets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <sets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    void setRoadID(unsigned int RoadID);
    void setDestinationNode(Node *destinationNode);
    void setDestinationNodeID(unsigned int destinationNodeID);
    void setLenght(int lenght);
    void setSourceNode(Node *sourceNode);
    void setSourceNodeID(unsigned int sourceNodeID);
    void setSubRoadID(unsigned int subRoadID);
    static void setSubRoadIDCounter(unsigned int SubRoadIDCounter);
    void setTimeToTravel(int timeToTravel);
    void setSubRoadColor(string subRoadColor);
    void setSubRoadLabel(string subRoadLabel);
    void setLabelIsStreatName(bool labelIsStreatName);
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </sets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    //==============================================================   </public>   ===================================================================

};

#endif /* SUBROAD_H_ */
