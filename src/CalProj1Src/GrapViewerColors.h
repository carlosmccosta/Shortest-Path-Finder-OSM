#ifndef GRAPVIEWERCOLORS_H_
#define GRAPVIEWERCOLORS_H_

#include <string>
#include <vector>

using std::string;
using std::vector;

/**
 * Struct usada para manter uma base de dados das cores que o GraphViewer permite.
 */
struct GrapViewerColors {
public:
	GrapViewerColors();
	virtual ~GrapViewerColors();

	/// enumeração com as cores que o GraphViewer suporta
	enum GrapViewerColorsEnum { BLACK, BLUE, CYAN, DARKGREY, GRAY, GREEN, LIGHTGREY, MAGENTA, ORANGE, PINK, RED, WHITE, YELLOW };

	/// vector com as strings respectivas de cada de cada uma das cores que estão na enumeração
	static vector<string> grapViewerColorsStrings;

	static void initGrapViewerColors();
	static string getGraphViewColorString(unsigned int index);
};

#endif /* GRAPVIEWERCOLORS_H_ */
