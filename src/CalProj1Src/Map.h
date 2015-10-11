#ifndef MAP_H_
#define MAP_H_

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <fstream>

#include "Node.h"
#include "Road.h"
#include "SubRoad.h"
#include "utils.h"
#include "defs.h"
#include "GrapViewerColors.h"
#include "../GraphViewer/graphviewer.h"

using std::cout;
using std::cerr;
using std::cin;
using std::ifstream;
using std::getline;
using std::vector;
using std::string;
using std::stringstream;
using std::set;
using std::make_heap;
using std::pop_heap;
using std::pow;
using std::sqrt;
using std::abs;
using std::min;
using std::max;
using std::getline;



//################################################################   Map   #######################################################################
/**
 * Classe que faz a gestão de um mapa, fornecendo toda a implementação necessária para carregamento, análise e visualização do grafo
 * que representa o mapa, bem como o algoritmo de Dijkstra para a determinação do melhor caminho entre dois Nodes.
 */
class Map {
private:
//=============================================================   <private>   ====================================================================
	/// set que armazena os nós do mapa por ID
	set <Node*, Node::functorToOrderNodeSet> mapNodesSet;

	/// set que armazena as ruas do mapa por ID (usado para acelerar a pesquisa interna aquando do carregamento do mapa)
	set <Road*, Road::functorToSortRoadsByID> mapRoadsSet;

	/// set que armazena as ruas do mapa por nome da rua (usado para acelerar a pesquisa da rua que o utilizador fornece)
	set <Road*, Road::functorToSortRoadsByName> mapRoadsSetSortedByName;

	/// set que armazena as subroads do mapa por ID
	set <SubRoad*, SubRoad::functorToSortSubRoadsByID> mapSubRoadsSet;

	/// string que descreve o Map em questão
	string description;

	/// Variável estática usada para permitir usar várias janelas do GraphViewer (ou seja, é a porta que o GraphViewer irá usar a comunicação entre a implementação em C++ e Java)
	static int graphViewPort;

	/// Vector com os nós que fazem parte do melhor caminho determinado pelo algoritmo de Dijkstra segundo o nodeID / roadName dado pelo user.
	/// Este vector tem os nodes do fim do caminho para o inicio.
	vector <Node*> currentPath;
//=============================================================   </private>   ===================================================================


//==============================================================   <public>   ====================================================================
public:
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <constructors-destructors>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	Map();
	Map(string _description);
	virtual ~Map();
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </constructors-destructors>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <map management>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	void addNode(Node* newNode);
	bool removeNode(Node* nodeIDToRemove);
	void addRoad(Road *newRoad);
	bool removeRoad(Road* roadIDToRemove);
	void addSubRoad(SubRoad *newSubRoad);
	bool removeSubRoad(SubRoad* subRoadIDToRemove);

	Node* findNode(unsigned int nodeID);
	Road* findRoad(unsigned int roadID);
	Road* findRoad(string roadName);
	SubRoad* findSubRoad(unsigned int subRoadID);
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </map management>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <best path on map algorithms>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	void calculateDijkstraPath(Node* sourceNode, Node* destinationNode, bool fastestPath, GraphViewer* graphViewer);
	void pathFromSourceToDestination(Node* sourceNode, Node* destinationNode, GraphViewer* graphViewer);
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </best path on map algorithms>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <CLI>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	GraphViewer* showMapOnGraphViewerCLI(bool fastest, bool nodesWithEmptyLabel, bool reset);
	void calculateBestPathShowingFullMapCLI(bool fastest, bool useNodeIDOnSearch, GraphViewer* graphViewer);
	void calculateBestPathShowingSurroundingsCLI(bool fastest, bool useNodeIDOnSearch);
	void calculateBestPathShowingDijkastraRunningCLI(bool fastest, bool useNodeIDOnSearch);
	void savePathCLI();
	void loadPathCLI();
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <CLI>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <CLI auxiliary functions>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	Node* findNodeCLI(const char* message, const char* errorMessage);
	Node* getSourceNodeCLI();
	Node* getDestinationNodeCLI();

	Road* findRoadCLI(const char* message, const char* errorMessage);
	void findSimilarRoadsCLI(string roadName, vector <Road*>& similarRoadsFound, vector< vector <string> >& tableColumns);
	Road* selectRoadFromSimilarRoadsCLI(vector <Road*>& similarRoadsFound, vector< vector <string> >& tableColumns);

	Road* getSourceRoadCLI();
	Road* getDestinationRoadCLI();

	void loadMapCLI();
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </CLI auxiliary functions>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <GraphViewer>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	void resetNodes(GraphViewer* graphViewer, bool nodesWithEmptyLabel);
	GraphViewer* showMapOnGraphViewer(int GraphWidth, int GraphHeigth, int GraphWindowWidth, int GraphWindowHeigth, bool automaticArranjeNodesPosition, bool fastest, bool nodesWithEmptyLabel, bool reset);
	void showPathAndSurroundingsOnGraphViewer(const vector <Node*>& nodesToShow, int GraphWidth, int GraphHeigth, int GraphWindowWidth, int GraphWindowHeigth, bool automaticArranjeNodesPosition, bool fastest, bool nodesWithEmptyLabel);
	void addConectedNodesAndSubRoadsToGraph(GraphViewer* graphViewer, vector <SubRoad*>& nodesToShow, bool fastest);
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </GraphViewer>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <loads-saves>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	void loadNodes(string filename) throw(FileDoesntExistException);
	void updateNodesProjectionsToFitWindow(int minLongitudeProjection, int maxLongitudeProjection, int minLatitudeProjection, int maxLatitudeProjection);
	void loadRoads(string filenam) throw(FileDoesntExistException);
	void loadSubRoads(string filename) throw(FileDoesntExistException);
	void finalizeLoad();
	void loadPath(string filename) throw(FileDoesntExistException);
	void saveCurrentPath(string filename) throw(FileAlreadyExistException);
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </loads-saves>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <gets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    string getDescription() const;
    set<Node*, Node::functorToOrderNodeSet>& getMapNodesSet();
    set<Road*, Road::functorToSortRoadsByID>& getMapRoadsSet();
    set<Road*, Road::functorToSortRoadsByName>& getMapRoadsSetSortedByName();
    set<SubRoad*, SubRoad::functorToSortSubRoadsByID>& getMapSubRoads();
    vector<Node*> getCurrentPath() const;
    static int getGraphViewPort();
    set<SubRoad*,SubRoad::functorToSortSubRoadsByID> getMapSubRoadsSet() const;
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </gets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <sets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    void setDescription(string description);
    void setMapNodesSet(const set<Node*, Node::functorToOrderNodeSet>& mapNodes);
    void setMapRoadsSet(const set<Road*, Road::functorToSortRoadsByID>& mapRoads);
    void setMapRoadsSetSortedByName(const set<Road*, Road::functorToSortRoadsByName>& mapRoadsSortedByName);
    void setMapSubRoadsSet(const set<SubRoad*, SubRoad::functorToSortSubRoadsByID>& mapSubRoads);
    void setCurrentPath(const vector<Node*>& currentPath);
    void setGraphViewPort(int graphViewPort);
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </sets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


//==============================================================   </public>   ===================================================================

};

#endif /* MAP_H_ */
