#pragma once
#include "token.h"
#include "postfix.h"

#include <queue>

class Tokenizer : public postfix {
public:
	Tokenizer(string _expression);
	// Metodo ecargado de procesar elementos de una expresion y
	// asignarlos a un determiando tipo de token.
	void setTokens();
	// retorna true si procesa un espacio en blanco.
	bool isWriteSpace(char ch);
	// retorna true si procesa un operador implementado.
	bool isOperator(char ch);
	// retorna true si procesa un parentesis izquierdo o derecho.
	bool isParenthesis(char ch);
	// Metodo encargado de asignar un tipo de precedencia a cada operador que procese.
	Token getTokenPrecedence(char ch);
private:
	bool readNumber;
	double number;
	double denominator;
	bool decimal;
	string expression;
	int index;
	bool access;
};


