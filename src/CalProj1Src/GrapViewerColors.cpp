#include "GrapViewerColors.h"

GrapViewerColors::GrapViewerColors() {}

GrapViewerColors::~GrapViewerColors() {}


vector <string> GrapViewerColors::grapViewerColorsStrings;

void GrapViewerColors::initGrapViewerColors() {
	grapViewerColorsStrings.push_back("black");
	grapViewerColorsStrings.push_back("blue");
	grapViewerColorsStrings.push_back("cyan");
	grapViewerColorsStrings.push_back("darkGray");
	grapViewerColorsStrings.push_back("gray");
	grapViewerColorsStrings.push_back("green");
	grapViewerColorsStrings.push_back("lightGray");
	grapViewerColorsStrings.push_back("magenta");
	grapViewerColorsStrings.push_back("orange");
	grapViewerColorsStrings.push_back("pink");
	grapViewerColorsStrings.push_back("red");
	grapViewerColorsStrings.push_back("white");
	grapViewerColorsStrings.push_back("yellow");
}

string GrapViewerColors::getGraphViewColorString(unsigned index) {
	if (index >= 0 && index < grapViewerColorsStrings.size())
		return grapViewerColorsStrings[index];
	else
		return "orange";
}
