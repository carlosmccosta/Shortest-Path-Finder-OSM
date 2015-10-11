#include "graphviewer.h"

void GraphViewer::startup(int width, int height, bool dynamic, int port) {
  this->width = width;
  this->height = height;
  this->isDynamic = dynamic;

  char cmd[256];
  sprintf(cmd, "java -jar GraphViewerController.jar --port %d", port);

#ifdef linux
  procId = 0;
  if (!(procId = fork())) {
    system(cmd);
    kill(getppid(), SIGINT);
    exit(0);
  }
  else {    
    usleep(2000000);
    
    con = new Connection(port);
    
    char buff[200];
    sprintf(buff, "newGraph %d %d %s\n", width, height, (dynamic?"true":"false"));
    string str(buff);
    
    con->sendMsg(str);
  }
#else
  STARTUPINFO si;
  PROCESS_INFORMATION pi;
  ZeroMemory( &si, sizeof(si) );
  si.cb = sizeof(si);
  ZeroMemory( &pi, sizeof(pi) );

  if( !CreateProcess( NULL,   // No module name (use command line)
		      cmd,        // Command line
		      NULL,           // Process handle not inheritable
		      NULL,           // Thread handle not inheritable
		      FALSE,          // Set handle inheritance to FALSE
		      0,              // No creation flags
		      NULL,           // Use parent's environment block
		      NULL,           // Use parent's starting directory 
		      &si,            // Pointer to STARTUPINFO structure
		      &pi )           // Pointer to PROCESS_INFORMATION structure
      ) {
    printf( "CreateProcess failed (%d).\n", GetLastError() );
    return;
  }
 
  // Close process and thread handles. 
  CloseHandle( pi.hProcess );
  CloseHandle( pi.hThread );

  Sleep(2000);
  con = new Connection(port);
  
  char buff[200];
  sprintf(buff, "newGraph %d %d %s\n", width, height, (dynamic?"true":"false"));
  string str(buff);
  con->sendMsg(str);
#endif
}

GraphViewer::GraphViewer(int width, int height, bool dynamic) {
  startup(width, height, dynamic, 7773);
}

GraphViewer::GraphViewer(int width, int height, bool dynamic, int port) {
  startup(width, height, dynamic, port);
}

bool GraphViewer::createWindow(int width, int height) {
  char buff[200];
  sprintf(buff, "createWindow %d %d\n", width, height);
  string str(buff);
  return con->sendMsg(str);
}

bool GraphViewer::closeWindow() {
  char buff[200];
  sprintf(buff, "closeWindow\n");
  string str(buff);
  return con->sendMsg(str);
}

bool GraphViewer::addNode(int id) {
  char buff[200];
  sprintf(buff, "addNode1 %d\n", id);
  string str(buff);
  return con->sendMsg(str);
}

bool GraphViewer::addNode(int id, int x, int y) {
  char buff[200];
  sprintf(buff, "addNode3 %d %d %d\n", id, x, y);
  string str(buff);
  return con->sendMsg(str);
}

bool GraphViewer::addEdge(int id, int v1, int v2, int edgeType) {
  char buff[200];
  sprintf(buff, "addEdge %d %d %d %d\n", id, v1, v2, edgeType);
  string str(buff);
  return con->sendMsg(str);
}

bool GraphViewer::setEdgeLabel(int k, string label) {
  char buff[200];
  sprintf(buff, "setEdgeLabel %d %s\n", k, label.c_str());
  string str(buff);
  return con->sendMsg(str);
}

bool GraphViewer::setVertexLabel(int k, string label) {
  char buff[200];
  sprintf(buff, "setVertexLabel %d %s\n", k, label.c_str());
  string str(buff);
  return con->sendMsg(str);
}

bool GraphViewer::defineEdgeColor(string color) {
  char buff[200];
  sprintf(buff, "defineEdgeColor %s\n", color.c_str());
  string str(buff);
  return con->sendMsg(str);
}

bool GraphViewer::removeNode(int id) {
  char buff[200];
  sprintf(buff, "removeNode %d\n", id);
  string str(buff);
  return con->sendMsg(str);
}

bool GraphViewer::removeEdge(int id) {
  char buff[200];
  sprintf(buff, "removeEdge %d\n", id);
  string str(buff);
  return con->sendMsg(str);
}

bool GraphViewer::setEdgeColor(int k, string color) {
  char buff[200];
  sprintf(buff, "setEdgeColor %d %s\n", k, color.c_str());
  string str(buff);
  return con->sendMsg(str);
}

bool GraphViewer::setEdgeThickness(int k, int thickness) {
  char buff[200];
  sprintf(buff, "setEdgeThickness %d %d\n", k, thickness);
  string str(buff);
  return con->sendMsg(str);
}


bool GraphViewer::defineVertexColor(string color) {
  char buff[200];
  sprintf(buff, "defineVertexColor %s\n", color.c_str());
  string str(buff);
  return con->sendMsg(str);
}

bool GraphViewer::setVertexColor(int k, string color) {
  char buff[200];
  sprintf(buff, "setVertexColor %d %s\n", k, color.c_str());
  string str(buff);
  return con->sendMsg(str);
}

bool GraphViewer::setBackground(string path) {
  char buff[200];
  sprintf(buff, "setBackground %s\n", path.c_str());
  string str(buff);
  return con->sendMsg(str);
}

bool GraphViewer::rearrange() {
  return con->sendMsg("rearrange\n");
}
