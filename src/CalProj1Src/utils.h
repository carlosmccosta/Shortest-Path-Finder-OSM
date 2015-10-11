#ifndef UTILS_H_
#define UTILS_H_

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <limits>
#include <climits>
#include <algorithm>
#include <cstdlib>
#include "Exceptions.h"

using std::string;
using std::stringstream;
using std::vector;
using std::cin;
using std::cout;
using std::setw;
using std::flush;
using std::endl;
using std::max;
using std::getline;
using std::istream;



/**
 * namespace com uma biblioteca de funções usadas na interface com o utilizador
 */
namespace utils {

/**
 * \brief Limpa as flags do cin e fica à espera de um input para prosseguir.
 * \details Serve para parar o programa e esperar que o utilizador faça algum input para prosseguir.
 *          Evita user system("pause"), que não é portable, não é standard e é muito mais "pesado" para o programa...
 */
void getUserInput();


/**
 * getline que faz o sync para não ler lixo do buffer.
 * @return Retorna a string com a linha lida do cin.
 */
string getlineCin();

/**
 * Método que limpa o ecrã da consola.
 * Evita usar system("cls"), que não é portable, não é standard e é muito mais "pesado" para o programa...
 */
void clearConsoleScreen();


/**
 * \brief Mostra a "message" ao utilizador e espera por um input de um número entre min (default é 0) e size-1 (default é INT_MAX).
 * \details Enquanto não for introduzido um input válido vai pedindo ao utilizador para introduzir novamente os dados mostrando a errorMessage.
 */
int getIntCin(const char* message, const char* errorMessage, int min = 0, int size = INT_MAX);



/**
 * \brief Mostra a "message" ao utilizador e espera por um input de um número entre min (default é 0) e size-1 (default é UINT_MAX).
 * \details Enquanto não for introduzido um input válido vai pedindo ao utilizador para introduzir novamente os dados.
 */
template <class Tipo>
Tipo getNumberCin(const char* message, Tipo size = UINT_MAX, Tipo min = 0, bool menu = false, const char* error_message = "Número fora do intervalo!") {

	if( (size == min) && min == 0)
		throw ExNoInterval();

	Tipo numero;
	do {
		cout << message << flush;

		/*
		 * Enquanto cin devolver um apontador NULL (e como tal no teste do if dar true (por estar negado)),
		 * devido ao facto de estar a ler dados que não são números, (ex: caracteres...)
		 * informa ao utilizador que tem que introduzir um nº e pede para introduzir os dados novamente.
		 */
		if (!(cin >> numero)) {

			//Limpa as flags do cin
			cin.clear();

			//Extrai e ignora todos os caracteres que estavam no buffer de cin, visto que ao tentar-se introduzir
			//caracteres num int (por ex), o cin entra em estado de erro e não remove os caracteres que leu do buffer
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << "Introduza um número!" << endl << endl;
		} else

			//Testa se os números introduzidos estão dentro do intervalo pedido
			if (menu)
				if (numero >= min && numero <= size)
					break; //Se estiverem sai-se do loop
				else
					cout << error_message << endl << endl; //Senão informasse o utilizador e pede-se novamente o nº
			else
				if (numero >= min && numero < size)
					break; //Se estiverem sai-se do loop
				else
					cout << error_message << endl << endl; //Senão informasse o utilizador e pede-se novamente o nº

	} while (true);

	if (menu)
		if(numero == 0)
			throw ExOutOfRange("");
		else
			return (numero - 1);
	else
		return numero;
}


///Pergunta message ao utilizador e retorna Sim/Não.
bool getYesNoCin(const char* message, const char* message_erro = "Introduziu uma opção incorrecta!\nIntroduza S para continuar ou N para parar: ");

///Converte uma string para maiúsculas.
string toUpper(string str);


///Converte uma string para minúsculas.
string toLower(string str);


///Função de conversão de objecto para string usando o operador <<.
template <class T>
string toString(T obj) {
	stringstream ss;
	ss << obj;
	return ss.str();
}


///Função que separa uma string em substrings sempre que encontrar o caracter delimitador ("delim").
vector <string> split(string in, char delim);


/**
 * \brief Método que imprime uma tabela com os dados de um vector de colunas (vector de strings).
 *
 * @param title Titulo da tabela.
 * @param columns Vector de colunas.
 * @param colNames Vector com o nome das colunas.
 * @param reverse Caso seja true, inverte-se a ordem dos dados na coluna (mostra a tabela invetida - linhas 0 1 2 3 passam a 3 2 1 0).
 * @param hide_index Caso seja true, não imprime a numeração das linhas.
 * @return Um booleano caso tenha sido feito algum output de dados.
 */
bool printMenu(string & title, const vector< vector <string> > & columns, const vector <string> & colNames, bool menu = false, bool reverse = false, bool hide_index = false, bool hide_colnames = false);


}

#endif
