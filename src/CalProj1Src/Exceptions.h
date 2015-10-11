#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include <iostream>
#include <string>
#include <exception>

using std::ostream;
using std::string;
using std::exception;



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  <LibraryExceptions>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
/**
 * \brief Superclasse de tratamento de excep��es.
 * \details Subclasse de std::exception para no programa ser poss�vel fazer catch das excep��es da std e das excep��es criadas para o programa.
 */
class Exceptions: public exception {
protected:
	const char* errorMessage;

public:
	explicit Exceptions(const char* pStr) : errorMessage(pStr) {}

	/**
	 * Destrutor que garante que n�o ir� lan�ar uma excep��o,
	 * porque a classe std::exception, obriga a que as subclasses que fazem override �s suas fun��es, n�o podem lan�ar excep��es.
	 * Isso inclui os destrutores e a fun��o what().
	 * Caso n�o fosse feito o compilador iria dar o erro "looser throw specifier...".
	 */
	virtual ~Exceptions() throw() {}
	const char* what() const throw() { return errorMessage; }
};
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  </LibraryExceptions>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  <FileDoesntExistException>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
///Classe usado no tratamento de excep��es que sinaliza que n�o foi poss�vel abrir o ficheiro especificado.
class FileDoesntExistException: public Exceptions {
private:
	char* filename;

public:
	explicit FileDoesntExistException(const char* pStr = "N�o foi poss�vel abrir o ficheiro!") : Exceptions(pStr) {}
	virtual ~FileDoesntExistException() throw() {}
	string getFilename() const { return filename; }
};
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  </FileDoesntExistException>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  <FileAlreadyExistException>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
///Classe usado no tratamento de excep��es que sinaliza que n�o foi poss�vel abrir o ficheiro especificado.
class FileAlreadyExistException: public Exceptions {
private:
	char* filename;

public:
	explicit FileAlreadyExistException(const char* pStr = "O ficheiro j� existe!") : Exceptions(pStr) {}
	virtual ~FileAlreadyExistException() throw() {}
	string getFilename() const { return filename; }
};
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  </FileDoesntExistException>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  <ElementAlreadyExistsException>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
///Classe usada no tratamento de excep��es que sinaliza que um dado elemento j� existe num dado contentor
template <class T>
class ElementAlreadyExistsException: public Exceptions {
private:
	T elementoRepetido;
public:
	explicit ElementAlreadyExistsException(T elemento_repetido, const char* pStr = "Elemento j� existe!") :
		Exceptions(pStr), elementoRepetido(elemento_repetido) {}
	virtual ~ElementAlreadyExistsException() throw() {}

	T getElementoRepetido() const { return elementoRepetido; }
};
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  </ElementAlreadyExistsException>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  <ElementDoesntExistsException>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
///Classe usada no tratamento de excep��es que sinaliza que um dado elemento j� existe num dado contentor
template <class T>
class ElementDoesntExistsException: public Exceptions {
private:
	T elementoInexistente;
public:
	explicit ElementDoesntExistsException(T elementoInexistente, const char* pStr = "Elemento n�o existe!") :
		Exceptions(pStr), elementoInexistente(elementoInexistente) {}
	virtual ~ElementDoesntExistsException() throw() {}

	T getElementoInexistente() const { return elementoInexistente; }
};
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  </ElementDoesntExistsException>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  <EmptyContainerException>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
///Classe usada no tratamento de excep��es que sinaliza que um vector se encontra vazio.
class EmptyContainerException: public Exceptions {
public:
	explicit EmptyContainerException(const char* pStr = "O container que est� a tentar aceder est� vazio!") : Exceptions(pStr) {}
	virtual ~EmptyContainerException() throw() {}
};
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  </EmptyContainerException>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  <CorruptedFileException>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
///Classe usado no tratamento de excep��es que sinaliza que um dado ficheiro que de dados est� corrupto ou num formato desconhecido.
class CorruptedFileException: public Exceptions {
private:
	char* filename;

public:
	explicit CorruptedFileException(const char* pStr = "Ficheiro com os dados corrompido!") : Exceptions(pStr) {}
	string getFilename() const { return filename; }
	virtual ~CorruptedFileException() throw() {}
};
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  </CorruptedFileException>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  ExOutOfRange  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
///Classe usada no tratamento de excep��es que sinaliza que um elemento que se est� a tentar aceder est� fora do dom�nio do contentor.
class ExOutOfRange: public Exceptions {
public:
	explicit ExOutOfRange(const char* pStr = "Valor fora do dom�nio do vector!") : Exceptions(pStr) {}
	virtual ~ExOutOfRange() throw() {}
};



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  ExNoInterval  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
///Classe usada no tratamento de excep��es que o intervalo fornecido � inv�lido
class ExNoInterval: public Exceptions {
public:
	explicit ExNoInterval(const char* pStr = "O intervalo come�a e acaba em zero!") : Exceptions(pStr) {}
	virtual ~ExNoInterval() throw() {}
};



#endif /* EXCEPTIONS_H_ */
