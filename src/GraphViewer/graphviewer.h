#ifndef _GRAPH_VIEWER_H_
#define _GRAPH_VIEWER_H_

#ifdef linux
	#include <unistd.h>
#else
	#include <winsock2.h>
	#include <Windows.h>
#endif

#include <stdlib.h>
#include <signal.h>
#include <string>

#include "edgetype.h"
#include "connection.h"

class GraphViewer {
 public:
  GraphViewer(int, int, bool);
  GraphViewer(int, int, bool, int);
  bool createWindow(int width, int height);
  bool closeWindow();

  bool addNode(int id, int x, int y);
  bool addNode(int id); 
  bool addEdge(int id, int v1, int v2, int edgeType);

  bool removeNode(int id); 
  bool removeEdge(int id); 

  bool setVertexLabel(int id, string label);

  bool setEdgeLabel(int id, string label);
  bool setEdgeColor(int id, string color);
  bool setEdgeThickness(int id, int thickness);

  bool setVertexColor(int id, string color);

  bool defineEdgeColor(string color);
  bool defineVertexColor(string color);
  
  bool setBackground(string path);

  bool rearrange();

#ifdef linux
  pid_t procId;
#endif

 private:
  void startup(int, int, bool, int);

  int width, height;
  bool isDynamic;

  Connection *con;
};

#endif
