#pragma once
#include "token.h"

#include <math.h>

class Operation
{
public:
	double getSuma(Token operando_1, Token operando_2);
	double getResta(Token operando_1, Token operando_2);
	double getMult(Token operando_1, Token operando_2);
	double getDiv(Token numerador, Token divisor);
	double getPow(Token operando, Token exponente);
	double getRaiz(Token indice, Token radicando);
	double getLog(Token baseLog, Token argumento);
private:
};
