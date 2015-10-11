#include "Map.h"


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <constructors-destructors>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
Map::Map() : description("") {}

Map::Map(string _description) : description(_description) {}

Map::~Map() {
	for (set<Node*>::iterator it = mapNodesSet.begin(); it != mapNodesSet.end(); ++it) {
		delete(*it);
	}
	mapNodesSet.clear();


	for (set<Road*>::iterator it = mapRoadsSet.begin(); it != mapRoadsSet.end(); ++it) {
		delete(*it);
	}
	mapRoadsSet.clear();


	for (set<SubRoad*>::iterator it = mapSubRoadsSet.begin(); it != mapSubRoadsSet.end(); ++it) {
		delete(*it);
	}
	mapSubRoadsSet.clear();
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </constructors-destructors>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <map management>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
int Map::graphViewPort = 0;


void Map::addNode(Node* newNode) {
	mapNodesSet.insert(newNode);
}

bool Map::removeNode(Node* nodeIDToRemove) {
	set<Node*>::iterator it = mapNodesSet.find(nodeIDToRemove);

	if (it == mapNodesSet.end()) {
		return false;
	} else {
		mapNodesSet.erase(it);
		return true;
	}
}

void Map::addRoad(Road *newRoad)  {
	mapRoadsSet.insert(newRoad);
	mapRoadsSetSortedByName.insert(newRoad);
}

bool Map::removeRoad(Road* roadIDToRemove) {
	set<Road*>::iterator it = mapRoadsSet.find(roadIDToRemove);

	if (it == mapRoadsSet.end()) {
		return false;
	} else {
		mapRoadsSet.erase(it);
		return true;
	}
}

void Map::addSubRoad(SubRoad *newSubRoad) {
	mapSubRoadsSet.insert(newSubRoad);
}

bool Map::removeSubRoad(SubRoad* subRoadIDToRemove) {
	set<SubRoad*>::iterator it = mapSubRoadsSet.find(subRoadIDToRemove);

	if (it == mapSubRoadsSet.end()) {
		return false;
	} else {
		mapSubRoadsSet.erase(it);
		return true;
	}
}

Node* Map::findNode(unsigned int nodeID) {
	Node* nodeTemp = new Node();
	nodeTemp->setNodeID(nodeID);

	set<Node*>::iterator itNode = mapNodesSet.find(nodeTemp);
	delete nodeTemp;

	return (itNode == mapNodesSet.end())? NULL : *itNode;
}

Road* Map::findRoad(unsigned int roadID) {
	Road* roadTemp = new Road();
	roadTemp->setRoadID(roadID);

	set<Road*>::iterator itRoad = mapRoadsSet.find(roadTemp);
	delete roadTemp;

	return (itRoad == mapRoadsSet.end())? NULL : *itRoad;
}

Road* Map::findRoad(string roadName)  {
	Road* roadTemp = new Road();
	roadTemp->setRoadName(utils::toUpper(roadName));

	set<Road*, Road::functorToSortRoadsByName>::iterator itRoad = mapRoadsSetSortedByName.find(roadTemp);
	delete roadTemp;

	return (itRoad == mapRoadsSetSortedByName.end())? NULL : *itRoad;
}

SubRoad* Map::findSubRoad(unsigned int subRoadID) {
	SubRoad* subRoadTemp = new SubRoad();
	subRoadTemp->setSubRoadID(subRoadID);

	set<SubRoad*>::iterator itSubRoad = mapSubRoadsSet.find(subRoadTemp);
	delete subRoadTemp;

	return (itSubRoad == mapSubRoadsSet.end())? NULL : *itSubRoad;
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </map management>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <best path on map algorithms>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void Map::calculateDijkstraPath(Node* sourceNode, Node* destinationNode, bool fastestPath, GraphViewer* graphViewer) {
#ifdef DEBUG
	utils::clearConsoleScreen();
	cout << "Calculando DijkstraPath\n" << endl;
#endif

	resetNodes(graphViewer, true);


	sourceNode->setNodeColor((string)NODE_START_PATH_COLOR);
	destinationNode->setNodeColor((string)NODE_END_PATH_COLOR);

	if (graphViewer != NULL) {
		graphViewer->setVertexColor(sourceNode->getNodeID(), (string)NODE_START_PATH_COLOR);
		graphViewer->setVertexColor(destinationNode->getNodeID(), (string)NODE_END_PATH_COLOR);
		graphViewer->rearrange();
		Sleep(ANIMATION_SLEEP);
	}


	Node* currentNode = sourceNode;
	currentNode->setCumulativeDistanceToSourceNode(0);
	currentNode->setCumulativeTimeToSourceNode(0);

	vector <Node*> nodesHeap;
	nodesHeap.push_back(currentNode);

	if (fastestPath)
		make_heap(nodesHeap.begin(), nodesHeap.end(), Node::functorToMakeNodeHeapByCumulativeTime());
	else
		make_heap(nodesHeap.begin(), nodesHeap.end(), Node::functorToMakeNodeHeapByCumulativeDistance());


	while (!nodesHeap.empty()) {
		currentNode = nodesHeap.front();
		currentNode->setVisited(true);

		if ((graphViewer != NULL) && (currentNode->getNodeID() != sourceNode->getNodeID()) && (currentNode->getNodeID() != destinationNode->getNodeID())) {
			graphViewer->setVertexColor(currentNode->getNodeID(), NODE_VISITED_COLOR);
			graphViewer->rearrange();
			Sleep(ANIMATION_SLEEP);
		}

		if ((currentNode->getNodeID() != sourceNode->getNodeID()) && (currentNode->getNodeID() != destinationNode->getNodeID()))
			currentNode->setNodeColor((string)NODE_VISITED_COLOR);

		if (fastestPath)
			pop_heap(nodesHeap.begin(), nodesHeap.end(), Node::functorToMakeNodeHeapByCumulativeTime());
		else
			pop_heap(nodesHeap.begin(), nodesHeap.end(), Node::functorToMakeNodeHeapByCumulativeDistance());


		nodesHeap.pop_back();

		//caso em que mais nenhum Node está acessivel
		if ((fastestPath ? currentNode->getCumulativeTimeToSourceNode() : currentNode->getCumulativeDistanceToSourceNode()) == -1) {
#ifdef DEBUG
			cout << "\nMais nenhum node acessivel\n" << endl;
#endif
			break;
		}


#ifdef DEBUG
			cout << "Node com id " << currentNode->getNodeID() << " tem " << currentNode->getConectedSubRoads().size() << " edjes." << endl;
#endif

		for (size_t i = 0; i < currentNode->getConectedSubRoads().size(); i++) {
			Node* conectedNode = currentNode->getConectedSubRoads()[i]->getDestinationNode();

			int newNodeWeigth = fastestPath ?
					currentNode->getCumulativeTimeToSourceNode() + currentNode->getConectedSubRoads()[i]->getTimeToTravel() :
					currentNode->getCumulativeDistanceToSourceNode() + currentNode->getConectedSubRoads()[i]->getLenght();


			if (newNodeWeigth < (fastestPath ? conectedNode->getCumulativeTimeToSourceNode() : conectedNode->getCumulativeDistanceToSourceNode())) {

				if (fastestPath) {
					conectedNode->setCumulativeTimeToSourceNode(newNodeWeigth);
				} else {
					conectedNode->setCumulativeDistanceToSourceNode(newNodeWeigth);
				}

				if (graphViewer != NULL) {
					graphViewer->setEdgeThickness(currentNode->getNodeID(), newNodeWeigth);
					graphViewer->rearrange();
					Sleep(ANIMATION_SLEEP);
				}

				conectedNode->setPathToSourceNode(currentNode);

				//se já estiver no heap, apenas a actualiza
				if (!conectedNode->getVisited()) {
					nodesHeap.push_back(conectedNode);
				}


				if (fastestPath)
					make_heap(nodesHeap.begin(), nodesHeap.end(), Node::functorToMakeNodeHeapByCumulativeTime());
				else
					make_heap(nodesHeap.begin(), nodesHeap.end(), Node::functorToMakeNodeHeapByCumulativeDistance());
			}
		}
	}

#ifdef DEBUG
	cout << endl;
	utils::getUserInput();
#endif


	if (graphViewer == NULL)
		graphViewer = showMapOnGraphViewerCLI(fastestPath, false, false);

	pathFromSourceToDestination(sourceNode, destinationNode, graphViewer);
}



void Map::pathFromSourceToDestination(Node* sourceNode, Node* destinationNode, GraphViewer* graphViewer) {
	currentPath.clear();

	size_t numNodesOnPath = 1;

	for (Node* currentPathNode = destinationNode; currentPathNode != sourceNode && currentPathNode != NULL; currentPathNode = currentPathNode->getPathToSourceNode()) {
		if (currentPathNode->getNodeID() != destinationNode->getNodeID()) {
			currentPathNode->setNodeColor((string)NODE_PATH_COLOR);
		}

		currentPath.push_back(currentPathNode);
		++numNodesOnPath;
	}

	if (graphViewer != NULL) {
		for (vector <Node*>::reverse_iterator nodeReverseIt = currentPath.rbegin(); nodeReverseIt != currentPath.rend(); ++nodeReverseIt) {
			Node* currentPathNode = *nodeReverseIt;
			if (currentPathNode->getNodeID() != sourceNode->getNodeID() && currentPathNode->getNodeID() != destinationNode->getNodeID()) {
				graphViewer->setVertexColor(currentPathNode->getNodeID(), (string)NODE_PATH_COLOR);
				graphViewer->rearrange();
				Sleep(ANIMATION_SLEEP);
			}
		}
	}



	utils::clearConsoleScreen();
	cout << "Caminho com " << numNodesOnPath << " nodes.\n" << endl;
	utils::getUserInput();
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </best path on map algorithms>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <CLI>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
GraphViewer* Map::showMapOnGraphViewerCLI(bool fastest, bool nodesWithEmptyLabel, bool reset) {
	return showMapOnGraphViewer(GRAPH_VIEWER_WIDTH, GRAPH_VIEWER_HEIGTH, GRAPH_VIEWER_WINDOW_WIDTH, GRAPH_VIEWER_WINDOW_HEIGTH, GRAPH_VIEWER_AUTO_ARRANJE_NODES_POSITION_ON_GRAPH, fastest, nodesWithEmptyLabel, reset);
}

void Map::calculateBestPathShowingFullMapCLI(bool fastest, bool useNodeIDOnSearch, GraphViewer* graphViewer) {
	//**********************************************************  <sourceNode>  **************************************************************
	Node* sourceNode = NULL;

	if (useNodeIDOnSearch) {
		sourceNode = getSourceNodeCLI();

		if (sourceNode == NULL) {
			cout << "O ID do nó introduzido não existe!\n" << endl;
			utils::getUserInput();
			return;
		}

	} else {
		Road* sourceRoad = this->getSourceRoadCLI();
		if (sourceRoad != NULL && !(sourceRoad->getStreetSubRoads().empty())) {
			sourceNode = (*(sourceRoad->getStreetSubRoads().begin()))->getSourceNode();
		}

		if (sourceNode == NULL)
			return;
	}



	//**********************************************************  </sourceNode>  *************************************************************


	//*********************************************************  <destiantionNode>  **********************************************************
	Node* destinationNode = NULL;

	if (useNodeIDOnSearch) {
		destinationNode = getDestinationNodeCLI();

		if (sourceNode == NULL) {
			cout << "O ID do nó introduzido não existe!\n" << endl;
			utils::getUserInput();
			return;
		}

	} else {
		Road* destinationRoad = this->getDestinationRoadCLI();
		if (destinationRoad != NULL && !(destinationRoad->getStreetSubRoads().empty())) {
			destinationNode = (*(destinationRoad->getStreetSubRoads().begin()))->getSourceNode();
		}

		if (destinationNode == NULL)
			return;
	}

	//*********************************************************  </destiantionNode>  *********************************************************

	calculateDijkstraPath(sourceNode, destinationNode, fastest, graphViewer);
}

void Map::calculateBestPathShowingSurroundingsCLI(bool fastest, bool useNodeIDOnSearch) {
	calculateBestPathShowingFullMapCLI(fastest, useNodeIDOnSearch, NULL);
	showPathAndSurroundingsOnGraphViewer(currentPath, GRAPH_VIEWER_WIDTH, GRAPH_VIEWER_HEIGTH, GRAPH_VIEWER_WINDOW_WIDTH, GRAPH_VIEWER_WINDOW_HEIGTH, GRAPH_VIEWER_AUTO_ARRANJE_NODES_POSITION_ON_GRAPH, fastest, true);
}

void Map::calculateBestPathShowingDijkastraRunningCLI(bool fastest, bool useNodeIDOnSearch) {
	calculateBestPathShowingFullMapCLI(fastest, useNodeIDOnSearch, showMapOnGraphViewerCLI(fastest, true, true));
}

void Map::savePathCLI() {
	cout << "   >>> Introduza o nome do ficheiro onde quer guardar o último caminho determinado\n   >>> Nome: ";
	string filename = utils::getlineCin();

	try {
		saveCurrentPath(filename);
	} catch (FileAlreadyExistException& e) {
		cout << "\n\nJá existe um ficheiro com o nome que introduziu!\n\n";
		utils::getUserInput();
	}
}

void Map::loadPathCLI() {
	cout << "   >>> Introduza o nome do ficheiro de onde quer carregar o caminho\n   >>> Nome: ";
	string filename = utils::getlineCin();
	try {
		loadPath(filename);
	} catch (FileDoesntExistException &e) {
		cout << "\n\nO ficheiro com o nome introduzido não existe!\n" << endl;
		utils::getUserInput();
	}
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </CLI>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <CLI auxiliary functions>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
Node* Map::findNodeCLI(const char* message, const char* errorMessage) {
	unsigned int nodeID;

	nodeID = utils::getIntCin(message, errorMessage);
	return findNode(nodeID);
}

Node* Map::getSourceNodeCLI() {
	return findNodeCLI("\nIntroduza o ID do nó de inicio: ", "Introduza um dos IDs que são mostrados no mapa!");
}

Node* Map::getDestinationNodeCLI() {
	return findNodeCLI("\nIntroduza o ID do nó de fim: ", "Introduza um dos IDs que são mostrados no mapa!");
}




Road* Map::findRoadCLI(const char* message, const char* errorMessage) {
	cout << message;
	string roadName = utils::toUpper(utils::getlineCin());

	Road* roadFound = findRoad(roadName);

	if (roadFound == NULL) {
		vector <Road*> similarRoadsFound;
		vector< vector <string> > tableColumns;
		findSimilarRoadsCLI(roadName, similarRoadsFound, tableColumns);

		if (similarRoadsFound.empty()) {
			cout << errorMessage << endl;
			utils::getUserInput();
			return NULL;
		} else {
			return selectRoadFromSimilarRoadsCLI(similarRoadsFound, tableColumns);
		}

	} else {
		return roadFound;
	}
}

void Map::findSimilarRoadsCLI(string roadName, vector <Road*>& similarRoadsFound, vector< vector <string> >& tableColumns) {
	//inicialização
	similarRoadsFound.clear();
	tableColumns.clear();
	tableColumns.push_back(vector <string>());

	//obtenção das ruas com nome similar ao introduzido pelo utilizador
	set <Road*, Road::functorToSortRoadsByName>::iterator itSetRoads;
	for (itSetRoads = mapRoadsSetSortedByName.begin(); itSetRoads != mapRoadsSetSortedByName.end(); ++itSetRoads) {
		if ((*itSetRoads)->getRoadName().find(utils::toUpper(roadName)) != string::npos) {
			similarRoadsFound.push_back(*itSetRoads);
			tableColumns[0].push_back((*itSetRoads)->getRoadName());
		}

	}
}

Road* Map::selectRoadFromSimilarRoadsCLI(vector <Road*>& similarRoadsFound, vector< vector <string> >& tableColumns) {
	//dados a ser mostrados na tabela
	string tableTitle("\n\n  >>>>>  Ruas com nome similar ao introduzido  <<<<<\n");
	vector <string> tableColumnsNames;


	//inicialização da tabela
	tableColumnsNames.push_back((string)"Nome da rua");

	cout << "Escolha a rua que pretende selecionar introduzindo o respectivo indice da tabela:\n" << endl;
	utils::printMenu(tableTitle, tableColumns, tableColumnsNames);

	size_t index = utils::getNumberCin<size_t>("\n\nIntroduza o indice da rua: ", similarRoadsFound.size(), 0, false, "Introduza o número da tabela correspondente à rua que quer selecionar!");

	return (index >= 0 && index < similarRoadsFound.size()) ? similarRoadsFound[index] : NULL;
}


Road* Map::getSourceRoadCLI() {
	return findRoadCLI("\nIntroduza o nome da rua de origem: ", "\nNão foram encontradas nenhuma rua com o nome dado!\n");
}

Road* Map::getDestinationRoadCLI() {
	return findRoadCLI("\nIntroduza o nome da rua de destino: ", "\nNão foram encontradas nenhuma rua com o nome dado!\n");
}




void Map::loadMapCLI() {
	cout << "##########  Carregamento dos ficheiros de dados do mapa  ##########\n\n\n";

	cout << "  >>> Introduza o nome do ficheiro dos nodes: ";
	string nodesFilename = utils::getlineCin();

	try {
		loadNodes(nodesFilename);
	} catch (FileDoesntExistException& e) {
		cout << "O ficheiro com o nome dos nodes não existe!\n\nCarregando os nodes com o nome por default (nodes.txt)" << endl;
		try {
			loadNodes(NODES_DEFAULT_FILENAME);
		} catch (FileDoesntExistException& e) {
			cout << "O ficheiro com o nome por default dos nodes também não existe!\n\n\nEncerrando o programa...\n" << endl;
			utils::getUserInput();
			exit(EXIT_FAILURE);
		}
	}




	cout << "\n\n\n  >>> Introduza o nome do ficheiro das roads: ";
	string roadsFilename = utils::getlineCin();

	try {
		loadRoads(roadsFilename);
	} catch (FileDoesntExistException& e) {
		cout << "O ficheiro com o nome das roads não existe!\n\nCarregando as roads com o nome por default (roads.txt)" << endl;
		try {
			loadRoads(ROADS_DEFAULT_FILENAME);
		} catch (FileDoesntExistException& e) {

			cout << "O ficheiro com o nome por default das roads também não existe!\n\n\nEncerrando o programa...\n" << endl;
			utils::getUserInput();
			exit(EXIT_FAILURE);
		}
	}



	cout << "\n\n\n  >>> Introduza o nome do ficheiro das subroads: ";
	string subroadsFilename = utils::getlineCin();

	try {
		loadSubRoads(subroadsFilename);
	} catch (FileDoesntExistException& e) {
		cout << "O ficheiro com o nome das subroads não existe!\n\nCarregando as subroads com o nome por default (subroads.txt)" << endl;
		try {
			loadSubRoads(SUBROADS_DEFAULT_FILENAME);
		} catch (FileDoesntExistException& e) {
			cout << "O ficheiro com o nome por default das subroads também não existe!\n\n\nEncerrando o programa...\n" << endl;
			utils::getUserInput();
			exit(EXIT_FAILURE);
		}
	}


	finalizeLoad();


	cout << "\n\n\n";
	utils::getUserInput();
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </CLI auxiliary functions>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <GraphViewer>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void Map::resetNodes(GraphViewer* graphViewer, bool nodesWithEmptyLabel) {
	//inicialização de todos os nós
	for (set<Node*, Node::functorToOrderNodeSet>::iterator it = mapNodesSet.begin(); it != mapNodesSet.end(); ++it) {
		(*it)->setCumulativeDistanceToSourceNode(-1); 	//maximo nº que unsigned int possui
		(*it)->setCumulativeTimeToSourceNode(-1); 		//maximo nº que unsigned int possui
		(*it)->setPathToSourceNode(NULL);
		(*it)->setVisited(false);
		(*it)->setNodeColor(NODE_DEFAULT_COLOR);

		if (graphViewer != NULL) {
			graphViewer->setVertexColor((*it)->getNodeID(), NODE_DEFAULT_COLOR);

			if (nodesWithEmptyLabel)
				graphViewer->setVertexLabel((*it)->getNodeID(), (string)" ");
		}
	}
}

GraphViewer* Map::showMapOnGraphViewer(int GraphWidth, int GraphHeigth, int GraphWindowWidth, int GraphWindowHeigth, bool automaticArranjeNodesPosition, bool fastest, bool nodesWithEmptyLabel, bool reset) {
	++graphViewPort;
	GraphViewer *graphViewer = new GraphViewer(GraphWidth, GraphHeigth, automaticArranjeNodesPosition, graphViewPort);
	//graphViewer->setBackground("background.jpg");
	graphViewer->createWindow(GraphWindowWidth, GraphWindowHeigth);
	graphViewer->defineVertexColor("white");
	graphViewer->defineEdgeColor("grey");

	//nodes
	for (set <Node*, Node::functorToOrderNodeSet>::const_iterator itNodes = mapNodesSet.begin(); itNodes != mapNodesSet.end(); ++itNodes) {
		graphViewer->addNode((int)(*itNodes)->getNodeID(), (*itNodes)->getLongitudeProjection(), (*itNodes)->getLatitudeProjection());
		graphViewer->setVertexColor((int)(*itNodes)->getNodeID(), (*itNodes)->getNodeColor());
		graphViewer->setVertexLabel((int)(*itNodes)->getNodeID(), (*itNodes)->getNodeLabel());
	}

	//edjes
	for (set <SubRoad*, SubRoad::functorToSortSubRoadsByID>::const_iterator itSubRoads = mapSubRoadsSet.begin(); itSubRoads != mapSubRoadsSet.end(); ++itSubRoads) {
		graphViewer->addEdge((int)(*itSubRoads)->getSubRoadID(),
				(int)(*itSubRoads)->getSourceNodeID(),
				(int)(*itSubRoads)->getDestinationNodeID(),
				EdgeType::DIRECTED);
		graphViewer->setEdgeColor((int)(*itSubRoads)->getSubRoadID(), (*itSubRoads)->getSubRoadColor());
		stringstream label;

		if (fastest) {
			if ((*itSubRoads)->getLabelIsStreatName()) {
				label << (*itSubRoads)->getSubRoadLabel() << " / " << (*itSubRoads)->getTimeToTravel();
			} else {
				label << (*itSubRoads)->getTimeToTravel();
			}
		} else {
			if ((*itSubRoads)->getLabelIsStreatName()) {
				label << (*itSubRoads)->getSubRoadLabel() << " / " << (*itSubRoads)->getLenght();
			} else {
				label << (*itSubRoads)->getLenght();
			}
		}

		graphViewer->setEdgeLabel((int)(*itSubRoads)->getSubRoadID(), label.str());
		int thickness = 0;
		if (fastest) {
			thickness = (int)(*itSubRoads)->getLenght() % SUBROAD_THICKNESS_MAXIMUM;
			graphViewer->setEdgeThickness((int)(*itSubRoads)->getSubRoadID(), thickness);
		} else {
			thickness = (int)(*itSubRoads)->getTimeToTravel() % SUBROAD_THICKNESS_MAXIMUM;
			graphViewer->setEdgeThickness((int)(*itSubRoads)->getSubRoadID(), thickness);
		}

	}


	if (reset)
		resetNodes(graphViewer, nodesWithEmptyLabel);

	graphViewer->rearrange();

	return graphViewer;
}

void Map::showPathAndSurroundingsOnGraphViewer(const vector <Node*>& nodesToShow, int GraphWidth, int GraphHeigth, int GraphWindowWidth, int GraphWindowHeigth, bool automaticArranjeNodesPosition, bool fastest, bool nodesWithEmptyLabel) {
	++graphViewPort;
	GraphViewer *graphViewer = new GraphViewer(GraphWidth, GraphHeigth, automaticArranjeNodesPosition, graphViewPort);
	//graphViewer->setBackground("background.jpg");
	graphViewer->createWindow(GraphWindowWidth, GraphWindowHeigth);
	graphViewer->defineVertexColor("white");
	graphViewer->defineEdgeColor("grey");

	for (size_t nodeIndex = 0; nodeIndex < nodesToShow.size(); ++nodeIndex) {
		graphViewer->addNode((int)(nodesToShow[nodeIndex])->getNodeID(), (nodesToShow[nodeIndex])->getLongitudeProjection(), (nodesToShow[nodeIndex])->getLatitudeProjection());
		graphViewer->setVertexColor((int)(nodesToShow[nodeIndex])->getNodeID(), (nodesToShow[nodeIndex])->getNodeColor());
		graphViewer->setVertexLabel((int)(nodesToShow[nodeIndex])->getNodeID(), (nodesToShow[nodeIndex])->getNodeLabel());

		addConectedNodesAndSubRoadsToGraph(graphViewer, nodesToShow[nodeIndex]->getConectedSubRoads(), fastest);

		for (size_t subRoadIndexLevel1 = 0; subRoadIndexLevel1 < nodesToShow[nodeIndex]->getConectedSubRoads().size(); ++subRoadIndexLevel1) {
			addConectedNodesAndSubRoadsToGraph(graphViewer, nodesToShow[nodeIndex]->getConectedSubRoads()[subRoadIndexLevel1]->getDestinationNode()->getConectedSubRoads(), fastest);
		}

	}

	graphViewer->rearrange();
}

void Map::addConectedNodesAndSubRoadsToGraph(GraphViewer* graphViewer, vector <SubRoad*>& subRoadsToShow, bool fastest) {
	for (size_t subRoadIndex = 0; subRoadIndex < subRoadsToShow.size(); ++subRoadIndex) {
		graphViewer->addNode((int) (subRoadsToShow[subRoadIndex]->getDestinationNodeID()), (subRoadsToShow[subRoadIndex]->getDestinationNode()->getLongitudeProjection()), (subRoadsToShow[subRoadIndex]->getDestinationNode()->getLatitudeProjection()));
		graphViewer->setVertexColor((int) subRoadsToShow[subRoadIndex]->getDestinationNode()->getNodeID(), subRoadsToShow[subRoadIndex]->getDestinationNode()->getNodeColor());
		graphViewer->setVertexLabel((int) subRoadsToShow[subRoadIndex]->getDestinationNode()->getNodeID(), subRoadsToShow[subRoadIndex]->getDestinationNode()->getNodeLabel());

		graphViewer->addEdge((int) (subRoadsToShow[subRoadIndex])->getSubRoadID(), (int) (subRoadsToShow[subRoadIndex])->getSourceNodeID(), (int) (subRoadsToShow[subRoadIndex])->getDestinationNodeID(), EdgeType::DIRECTED);
		graphViewer->setEdgeColor((int) (subRoadsToShow[subRoadIndex])->getSubRoadID(), (subRoadsToShow[subRoadIndex])->getSubRoadColor());
		stringstream label;

		if (fastest) {
			if ((subRoadsToShow[subRoadIndex])->getLabelIsStreatName()) {
				label << (subRoadsToShow[subRoadIndex])->getSubRoadLabel() << " / " << (subRoadsToShow[subRoadIndex])->getTimeToTravel();
			} else {
				label << (subRoadsToShow[subRoadIndex])->getTimeToTravel();
			}
		} else {
			if ((subRoadsToShow[subRoadIndex])->getLabelIsStreatName()) {
				label << (subRoadsToShow[subRoadIndex])->getSubRoadLabel() << " / " << (subRoadsToShow[subRoadIndex])->getLenght();
			} else {
				label << (subRoadsToShow[subRoadIndex])->getLenght();
			}
		}

		graphViewer->setEdgeLabel((int) (subRoadsToShow[subRoadIndex])->getSubRoadID(), label.str());
		int thickness = 0;
		if (fastest) {
			thickness = (int) (subRoadsToShow[subRoadIndex])->getLenght() % SUBROAD_THICKNESS_MAXIMUM;
			graphViewer->setEdgeThickness((int) (subRoadsToShow[subRoadIndex])->getSubRoadID(), thickness);
		} else {
			thickness = (int) (subRoadsToShow[subRoadIndex])->getTimeToTravel() % SUBROAD_THICKNESS_MAXIMUM;
			graphViewer->setEdgeThickness((int) (subRoadsToShow[subRoadIndex])->getSubRoadID(), thickness);
		}
	}
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </GraphViewer>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <loads-saves>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void Map::loadNodes(string filename) throw(FileDoesntExistException) {
	ifstream nodesInputFileStream(((string)MAPS_DIRECTORY + filename).c_str());

	int minLatitudeProjection = INT_MAX;
	int maxLatitudeProjection = -INT_MAX;
	int minLongitudeProjection = INT_MAX;
	int maxLongitudeProjection = -INT_MAX;

	if (nodesInputFileStream.is_open()) {
		while (!nodesInputFileStream.eof()) {
			string newNodeInfo;
			getline(nodesInputFileStream, newNodeInfo);
			vector<string> newNodeInfoParsed = utils::split(newNodeInfo, ';');

			//só acrescenta nodes com info válida
			if (newNodeInfoParsed.size() == 5) {
				unsigned int nodeID;
				double latitude;
				double longitude;
				double longitudeProjection;
				double latitudeProjection;

				stringstream ssNodeID(newNodeInfoParsed[0]);
				ssNodeID >> nodeID;

				stringstream ssLatitude(newNodeInfoParsed[1]);
				ssLatitude >> latitude;

				stringstream ssLongitude(newNodeInfoParsed[2]);
				ssLongitude >> longitude;

				stringstream ssLongitudeProjection(newNodeInfoParsed[3]);
				ssLongitudeProjection >> longitudeProjection;

				stringstream ssLatitudeProjection(newNodeInfoParsed[4]);
				ssLatitudeProjection >> latitudeProjection;

				//offsets para que não se perca precisão devido à conversão para int
				longitude *= NODES_COORDENATES_OFFSET;
				latitude *= NODES_COORDENATES_OFFSET;

				longitudeProjection *= NODES_PROJECTION_OFFSET;
				latitudeProjection *= NODES_PROJECTION_OFFSET;

				//para usar a as coordanadas em vez da projecção
#ifdef USE_COORDINATES_INSTEAD_PROJECTIONS
				longitudeProjection = longitude;
				latitudeProjection = latitude;
#endif


				//a api de conversão de mapas exportou o valor da projecção em x com o simétrico, visto que usando os valores que são dados os mapas aparecem
				//simétricos em relação ao eixo do Y relativamente ao "mundo real"
				//portanto é usado o abs do projecção no X
				int longitudeProjectionInt = abs((int)longitudeProjection);
				int latitudeProjectionInt = (int)latitudeProjection;
/*
				longitudeProjectionInt = longitudeProjectionInt % (int)(2.2 * GRAPH_VIEWER_WIDTH);
				latitudeProjectionInt = latitudeProjectionInt % (int)(2.2 * GRAPH_VIEWER_HEIGTH);
*/

				//**************************************************  <min/max>  *******************************************************
				minLongitudeProjection = min(minLongitudeProjection, longitudeProjectionInt);
				maxLongitudeProjection = max(maxLongitudeProjection, longitudeProjectionInt);
				minLatitudeProjection = min(minLatitudeProjection, latitudeProjectionInt);
				maxLatitudeProjection = max(maxLatitudeProjection, latitudeProjectionInt);
				//**************************************************  </min/max>  ******************************************************


				Node* newNode = new Node(nodeID, (int)latitude, (int)longitude, longitudeProjectionInt, latitudeProjectionInt);

				this->addNode(newNode);
			}
		}

		updateNodesProjectionsToFitWindow(minLongitudeProjection, maxLongitudeProjection, minLatitudeProjection, maxLatitudeProjection);

		cout << "\nCarregados " << mapNodesSet.size() << " nodes." << endl;
	} else {
		throw FileDoesntExistException();
	}
}


void Map::updateNodesProjectionsToFitWindow(int minLongitudeProjection, int maxLongitudeProjection, int minLatitudeProjection, int maxLatitudeProjection) {
	minLongitudeProjection -= NODE_LONGITUDE_PROJECTION_TRANSFORMATION_OFFSET;
	maxLongitudeProjection += NODE_LONGITUDE_PROJECTION_TRANSFORMATION_OFFSET;
	minLatitudeProjection -= NODE_LATITUDE_PROJECTION_TRANSFORMATION_OFFSET;
	maxLatitudeProjection += NODE_LATITUDE_PROJECTION_TRANSFORMATION_OFFSET;

	double dx = (double)abs(abs(maxLongitudeProjection) - abs(minLongitudeProjection));
	double dy = (double)abs(abs(maxLatitudeProjection) - abs(minLatitudeProjection));

	//usada para fazer um escalamento uniforme, sem haver deformações diferentes em cada eixo
	//assim não à deformação das distâncias relativas em cada nó
	double scaleConst = abs(((double)min(GRAPH_VIEWER_WIDTH, GRAPH_VIEWER_HEIGTH)) / max(dx, dy));


	for (set <Node*, Node::functorToOrderNodeSet>::iterator itNodes = mapNodesSet.begin(); itNodes != mapNodesSet.end(); ++itNodes) {
		double prevLongitudeProjection = (double)(*itNodes)->getLongitudeProjection();
		double prevLatitudeProjection = (double)(*itNodes)->getLatitudeProjection();


		int newLongitudeProjection = (int)((prevLongitudeProjection - (double)minLongitudeProjection) * scaleConst);
		int newLatitudeProjection =  (int)((prevLatitudeProjection  - (double)minLatitudeProjection)  * scaleConst);


		(*itNodes)->setLongitudeProjection(newLongitudeProjection);
		(*itNodes)->setLatitudeProjection(newLatitudeProjection);
	}
}


void Map::loadRoads(string filename) throw(FileDoesntExistException) {
	ifstream roadsInputFileStream(((string)MAPS_DIRECTORY + filename).c_str());

		if (roadsInputFileStream.is_open()) {
			while (!roadsInputFileStream.eof()) {
				string newRoadInfo;
				getline(roadsInputFileStream, newRoadInfo);
				vector<string> newRoadInfoParsed = utils::split(newRoadInfo, ';');

				//só acrescenta nodes com info válida
				if (newRoadInfoParsed.size() == 3) {
					unsigned int roadID;
					string roadName = utils::toUpper(newRoadInfoParsed[1]);
					bool oneWayRoad = (newRoadInfoParsed[2] == "True") ? true : false;

					stringstream ssRoadID(newRoadInfoParsed[0]);
					ssRoadID >> roadID;


					Road* newRoad = new Road(roadID, roadName, oneWayRoad);

					this->addRoad(newRoad);
				}
			}
			cout << "\nCarregados " << mapRoadsSet.size() << " roads." << endl;
		} else {
			throw FileDoesntExistException();
		}
}

void Map::loadSubRoads(string filename) throw(FileDoesntExistException) {
	ifstream subRoadsInputFileStream(((string)MAPS_DIRECTORY + filename).c_str());

	if (subRoadsInputFileStream.is_open()) {
		while (!subRoadsInputFileStream.eof()) {
			string newSubRoadInfo;
			getline(subRoadsInputFileStream, newSubRoadInfo);
			vector<string> newSubRoadInfoParsed = utils::split(newSubRoadInfo, ';');

			//só acrescenta nodes com info válida
			if (newSubRoadInfoParsed.size() == 4) { // == 4 porque tem um ';' no final de cada linha
				unsigned int RoadID;
				unsigned int sourceNodeID;
				unsigned int destinationNodeID;

				stringstream ssSubRoadID(newSubRoadInfoParsed[0]);
				ssSubRoadID >> RoadID;

				stringstream ssSourceNodeID(newSubRoadInfoParsed[1]);
				ssSourceNodeID >> sourceNodeID;

				stringstream ssDestinationNodeID(newSubRoadInfoParsed[2]);
				ssDestinationNodeID >> destinationNodeID;


				SubRoad* newSubRoad = new SubRoad(RoadID, sourceNodeID, destinationNodeID);

				this->addSubRoad(newSubRoad);
			}
		}

		cout << "\nCarregados " << mapSubRoadsSet.size() << " subRoads." << endl;
	} else {
		throw FileDoesntExistException();
	}
}

void Map::finalizeLoad() {
	//**********************************  <actualização dos pointers das roads e subroads e nodes>  *******************************************
	for (set <SubRoad*, SubRoad::functorToSortSubRoadsByID>::iterator itSubRoads = mapSubRoadsSet.begin(); itSubRoads != mapSubRoadsSet.end(); ++itSubRoads) {
		Node* sourceNode = findNode((*itSubRoads)->getSourceNodeID());
		if (sourceNode != NULL) {
			(*itSubRoads)->setSourceNode(sourceNode);
			sourceNode->addSubRoad(*itSubRoads);
		}

		(*itSubRoads)->setDestinationNode(findNode((*itSubRoads)->getDestinationNodeID()));


		Road* roadToAddSubRoad = findRoad((*itSubRoads)->getRoadID());

		if (roadToAddSubRoad != NULL) {
			roadToAddSubRoad->addSubRoad(*itSubRoads);
		}
	}
	//**********************************  </actualização dos pointers das roads e subroads e nodes>  ******************************************


	//*****************  <colocação de cada rua com as suas subroas da mesma cor e verificação se a rua é de 1 ou 2 sentidos>  ****************
	unsigned int currentSubRoadColor = 0;

	for (set <Road*, Road::functorToSortRoadsByID>::iterator itRoads = mapRoadsSet.begin(); itRoads != mapRoadsSet.end(); ++itRoads) {
		++currentSubRoadColor;
		if (!((*itRoads)->getStreetSubRoads().empty())) {
			//*****************************************  <colocação do nome na rua>  **********************************************************
			SubRoad* firstSubRoadOnRoad = *((*itRoads)->getStreetSubRoads().begin());
			firstSubRoadOnRoad->setSubRoadLabel((*itRoads)->getRoadName());
			firstSubRoadOnRoad->setLabelIsStreatName(true);
			//*****************************************  </colocação do nome na rua>  *********************************************************


			vector<SubRoad*> subRoadsToAdd;

			for (set <SubRoad*, SubRoad::functorToSortSubRoadsByID>::iterator itSubRoads = (*itRoads)->getStreetSubRoads().begin(); itSubRoads != (*itRoads)->getStreetSubRoads().end(); ++itSubRoads) {
				//************************************ <determinação do comprimento da subRoad>  **************************************************
				int dx = (*itSubRoads)->getSourceNode()->getLongitudeProjection() - (*itSubRoads)->getDestinationNode()->getLongitudeProjection();
				int dy = (*itSubRoads)->getSourceNode()->getLatitudeProjection() -  (*itSubRoads)->getDestinationNode()->getLatitudeProjection();
				int subRoadlenght = (int)abs(sqrt(dx*dx + dy*dy));

				(*itSubRoads)->setLenght(subRoadlenght);
				//************************************ </determinação do comprimento da subRoad>  *************************************************

				//********************************* <determinação do tempo de percurso da subRoad>  ***********************************************
				int subRoadtimeToTravel = (int)abs((*itSubRoads)->getDestinationNode()->getConectedSubRoads().size() * (*itSubRoads)->getLenght() * SUBROAD_TIME_TO_TRAVEL_OFFSET_PER_CONNECTED_SUBROAD);

				(*itSubRoads)->setTimeToTravel(subRoadtimeToTravel);
				//********************************* <determinação do tempo de percurso da subRoad>  ***********************************************


				//****************************************  <colocação das cores nas subruas>  ****************************************************
				(*itSubRoads)->setSubRoadColor(GrapViewerColors::getGraphViewColorString(currentSubRoadColor));


				if (currentSubRoadColor >= GrapViewerColors::grapViewerColorsStrings.size()) {
					currentSubRoadColor = 0;
				}
				//****************************************  </colocação das cores nas subruas>  ***************************************************

				//*************************  <se a rua for de 2 sentidos coloca uma subroad no sentido contrário>  ********************************
				if (!((*itRoads)->getOneWayRoad())) {
					SubRoad* newSubRoad = new SubRoad();
					newSubRoad->setRoadID((*itRoads)->getRoadID());
					newSubRoad->setSourceNodeID((*itSubRoads)->getDestinationNodeID());
					newSubRoad->setDestinationNodeID((*itSubRoads)->getSourceNodeID());
					newSubRoad->setLenght((*itSubRoads)->getLenght());
					newSubRoad->setTimeToTravel((*itSubRoads)->getTimeToTravel());
					newSubRoad->setSourceNode((*itSubRoads)->getDestinationNode());
					newSubRoad->setDestinationNode((*itSubRoads)->getSourceNode());
					newSubRoad->setSubRoadColor((*itSubRoads)->getSubRoadColor());
					newSubRoad->setSubRoadLabel((*itSubRoads)->getSubRoadLabel());

					subRoadsToAdd.push_back(newSubRoad);
				}
				//*************************  </se a rua for de 2 sentidos coloca uma subroad no sentido contrário>  *******************************
			}


			for (size_t i = 0; i < subRoadsToAdd.size(); ++i) {
				(*itRoads)->addSubRoad(subRoadsToAdd[i]);
				this->addSubRoad(subRoadsToAdd[i]);
				subRoadsToAdd[i]->getSourceNode()->addSubRoad(subRoadsToAdd[i]);
			}
		}
	}
	//*****************  </colocação de cada rua com as suas subroas da mesma cor e verificação se a rua é de 1 ou 2 sentidos>  ***************

}


void Map::saveCurrentPath(string filename) throw(FileAlreadyExistException) {
	ifstream ifStream(filename.c_str());
	if (ifStream.is_open()) {
		throw FileAlreadyExistException();
	}

	ofstream outPutFileStream(filename.c_str());

	for (size_t i = 0; i < currentPath.size(); ++i) {
		outPutFileStream << currentPath[i]->getNodeID() << "\n";
	}

	outPutFileStream.close();
}

void Map::loadPath(string filename) throw(FileDoesntExistException) {
	resetNodes(NULL, false);

	ifstream inputFileStream(filename.c_str());

	if (inputFileStream.is_open()) {

		unsigned int nodeID;
		Node* currentNode = NULL;
		Node* prevNode = NULL;

		bool firstNode = true;
		while(!inputFileStream.eof()) {
			string nodeIDStr;
			getline(inputFileStream, nodeIDStr);
			stringstream ss(nodeIDStr);
			ss >> nodeID;

			currentNode = findNode(nodeID);

			if (currentNode != NULL) {
				if (prevNode != NULL)
					prevNode->setPathToSourceNode(currentNode);

				if (firstNode)
					currentNode->setNodeColor(NODE_END_PATH_COLOR);
				else
					currentNode->setNodeColor(NODE_PATH_COLOR);
			}

			firstNode = false;
		}

		currentNode->setNodeColor(NODE_START_PATH_COLOR);
	} else {
		throw FileDoesntExistException();
	}

}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <loads-saves>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <gets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
string Map::getDescription() const {
	return description;
}

set<Node*, Node::functorToOrderNodeSet>& Map::getMapNodesSet() {
	return mapNodesSet;
}

set<Road*, Road::functorToSortRoadsByID>& Map::getMapRoadsSet() {
	return mapRoadsSet;
}

set<Road*, Road::functorToSortRoadsByName>& Map::getMapRoadsSetSortedByName() {
	return mapRoadsSetSortedByName;
}

set<SubRoad*, SubRoad::functorToSortSubRoadsByID>& Map::getMapSubRoads() {
	return mapSubRoadsSet;
}

vector<Node*> Map::getCurrentPath() const {
	return currentPath;
}

int Map::getGraphViewPort() {
	return graphViewPort;
}

set<SubRoad*, SubRoad::functorToSortSubRoadsByID> Map::getMapSubRoadsSet() const {
	return mapSubRoadsSet;
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </gets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <sets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void Map::setDescription(string description) {
	this->description = description;
}

void Map::setMapNodesSet(const set<Node*, Node::functorToOrderNodeSet>& mapNodes) {
	this->mapNodesSet = mapNodes;
}

void Map::setMapRoadsSet(const set<Road*, Road::functorToSortRoadsByID>& mapRoads) {
	this->mapRoadsSet = mapRoads;
}

void Map::setMapRoadsSetSortedByName(const set<Road*, Road::functorToSortRoadsByName>& mapRoadsSortedByName) {
	this->mapRoadsSetSortedByName = mapRoadsSortedByName;
}

void Map::setCurrentPath(const vector<Node*>& currentPath) {
	this->currentPath = currentPath;
}

void Map::setGraphViewPort(int graphViewPort) {
	this->graphViewPort = graphViewPort;
}

void Map::setMapSubRoadsSet(const set<SubRoad*, SubRoad::functorToSortSubRoadsByID>& mapSubRoads) {
	this->mapSubRoadsSet = mapSubRoads;
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </sets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
