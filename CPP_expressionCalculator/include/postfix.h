#pragma once
#include "token.h"
#include "errors.h"

#include <math.h>
#include <queue>
#include <stack>


class postfix
{
public:
	// Metodo encargado de trasformar una expresión matematica en notación posFija.
	bool algoritmo_posFix();
    // Metodo encargado de evaluar una expresión posFija.
	bool Evaluate();
	// Metodo encargado de retornar un double con el resultado final de la operación.
	double GetResult();
	// Metodo encargado de ingresar cada elemento de la expresión.
	void push(Token token);
private:
	stack <Token> tokenOperators;
	queue <Token> tokenNumber;
	stack <Token> tokenNumbersEvaluate;
	queue <Token> tokenExpression;
	
	//	Metodo encargado de verificar que operación se esta llamando y retorna el resultado
	//	de dicha operación. 
	Token operaciones(Token operando_1, Token operando_2, Token operador);
};
