#pragma once
#include "token.h"
#include "errors.h"

#include <math.h>
#include <queue>
#include <stack>


class postfix
{
public:
	// Metodo encargado de trasformar una expresi�n matematica en notaci�n posFija.
	bool algoritmo_posFix();
    // Metodo encargado de evaluar una expresi�n posFija.
	bool Evaluate();
	// Metodo encargado de retornar un double con el resultado final de la operaci�n.
	double GetResult();
	// Metodo encargado de ingresar cada elemento de la expresi�n.
	void push(Token token);
private:
	stack <Token> tokenOperators;
	queue <Token> tokenNumber;
	stack <Token> tokenNumbersEvaluate;
	queue <Token> tokenExpression;
	
	//	Metodo encargado de verificar que operaci�n se esta llamando y retorna el resultado
	//	de dicha operaci�n. 
	Token operaciones(Token operando_1, Token operando_2, Token operador);
};
