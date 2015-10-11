#include "Map.h"
#include "GrapViewerColors.h"


int main() {
	GrapViewerColors::initGrapViewerColors();

	Map roadMap("Mapa de estradas");
	roadMap.loadMapCLI();

	utils::clearConsoleScreen();
	bool useNodeIDOnSearch = utils::getYesNoCin("Pretende usar a pesquisa usando o ID do nó? (N para usar a pesquisa por nome da rua)\n(S/N): ", "Introduza S ou N!");

	int option = 1;

	do {
		utils::clearConsoleScreen();
		cout << "#########################   CAL - Trabalho 1 - Tema 9   #########################\n";
		cout << "  >>>   Determinação do melhor caminho entre dois pontos numa rede viária   <<<  \n";
		cout << "#################################################################################\n\n\n";

		cout << " 1 - Mostrar mapa\n\n";

		cout << " 2 - Determinar caminho mais curto entre duas ruas\n";
		cout << "     (mostrando o mapa todo)\n";
		cout << " 3 - Determinar caminho mais rapido entre duas ruas\n";
		cout << "     (mostrando o mapa todo)\n\n";

		cout << " 4 - Determinar caminho mais curto entre duas ruas\n";
		cout << "     (mostrando uma janela com o mapa todo e outra com apenas os arredores do caminho)\n";
		cout << " 5 - Determinar caminho mais rapido entre duas ruas\n";
		cout << "     (mostrando uma janela com o mapa todo e outra com apenas os arredores do caminho)\n\n";

		cout << " 6 - Determinar caminho mais curto entre duas ruas\n";
		cout << "     (mostrando o algoritmo de Dijkstra a determinar o caminho)\n";
		cout << " 7 - Determinar caminho mais rapido entre duas ruas\n";
		cout << "     (mostrando o algoritmo de Dijkstra a determinar o caminho)\n\n";

		cout << " 8 - Limpar mapa\n\n";

		cout << " 9 - Guardar o caminho determinado anteriormente para um ficheiro\n";
		cout << "10 - Carregar o caminho a partir de um ficheiro\n\n\n";

		cout << "0 - Sair\n\n\n" << endl;


		option = utils::getIntCin("  >>> Opcao: ", "Introduza uma das opcoes mencionadas em cima!\n", 0, 11);


		switch (option) {
			case 1: {
				utils::clearConsoleScreen();
				roadMap.showMapOnGraphViewerCLI(false, true, false);
				break;
			}

			case 2: {
				utils::clearConsoleScreen();
				roadMap.calculateBestPathShowingFullMapCLI(false, useNodeIDOnSearch, NULL);
				break;
			}

			case 3: {
				roadMap.calculateBestPathShowingFullMapCLI(true, useNodeIDOnSearch, NULL);
				break;
			}

			case 4: {
				utils::clearConsoleScreen();
				roadMap.calculateBestPathShowingSurroundingsCLI(false, useNodeIDOnSearch);
				break;
			}

			case 5: {
				utils::clearConsoleScreen();
				roadMap.calculateBestPathShowingSurroundingsCLI(true, useNodeIDOnSearch);
				break;
			}

			case 6: {
				utils::clearConsoleScreen();
				roadMap.calculateBestPathShowingDijkastraRunningCLI(false, useNodeIDOnSearch);
				break;
			}

			case 7: {
				utils::clearConsoleScreen();
				roadMap.calculateBestPathShowingDijkastraRunningCLI(true, useNodeIDOnSearch);
				break;
			}

			case 8: {
				roadMap.resetNodes(NULL, false);
				break;
			}

			case 9: {
				utils::clearConsoleScreen();
				roadMap.savePathCLI();
				break;
			}

			case 10: {
				utils::clearConsoleScreen();
				roadMap.loadPathCLI();
				break;
			}

			default:
				break;
			}

	} while (option != 0);


	return 0;
}
