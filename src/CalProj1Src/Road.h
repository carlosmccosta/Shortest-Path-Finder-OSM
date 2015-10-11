#ifndef ROAD_H_
#define ROAD_H_

#include <set>
#include <string>
#include "SubRoad.h"

using std::set;
using std::string;

struct RoadSetCompareFunctionClass;


//################################################################   Road   #######################################################################
/**
 * Classe que representa uma rua no mapa.
 * Cada rua é constituída por SubRoads, que correspondem a subsegmentos da rua no mapa.
 */
class Road {
private:
//=============================================================   <private>   ====================================================================
	/// Contador dos números de nós criados até ao momento
	static unsigned int roadIDCounter;

	unsigned int roadID;
	string roadName;
	bool oneWayRoad;		///< Flag que indica se esta rua é de um sentido

	set <SubRoad*, SubRoad::functorToSortSubRoadsByID> StreetSubRoads;
//=============================================================   </private>   ===================================================================


//==============================================================   <public>   ====================================================================
public:
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <constructors-destructors>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	Road();
	Road(unsigned int _roadID, string _roadName, bool _oneWayRoad);
	virtual ~Road();
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </constructors-destructors>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <auxiliary structs>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	struct functorToSortRoadsByID {
		bool operator()(const Road* road1, const Road* road2) const {
			return (road1->getRoadID() < road2->getRoadID());
		}
	};

	struct functorToSortRoadsByName {
		bool operator()(const Road* road1, const Road* road2) const {
			return (road1->getRoadName() < road2->getRoadName());
		}
	};
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </auxiliary structs>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <Road management>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	void addSubRoad(SubRoad* newSubRoad);
	bool removeSubRoad(SubRoad* subRoadToRemove);
	bool removeSubRoad(unsigned int subRoadIDToRemove);
	bool operator<(const Road* road) const;
	bool operator==(const Road* road) const;
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </Road management>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <gets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    bool getOneWayRoad() const;
    unsigned int getRoadID() const;
    static unsigned int getRoadIDCounter();
    string getRoadName() const;
    set<SubRoad*, SubRoad::functorToSortSubRoadsByID>& getStreetSubRoads();
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </gets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <sets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    void setOneWayRoad(bool oneWayRoad);
    void setRoadID(unsigned int roadID);
    static void setRoadIDCounter(unsigned int roadIDCounter);
    void setRoadName(string roadName);
    void setStreetSubRoads(set<SubRoad*, SubRoad::functorToSortSubRoadsByID> StreetSubRoads);
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </sets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//==============================================================   </public>   ===================================================================
};


#endif /* ROAD_H_ */
