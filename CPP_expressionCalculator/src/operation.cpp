#include "operation.h"

double Operation::getSuma(Token operando_1, Token operando_2)
{
	return operando_1.getNumber() + operando_2.getNumber();
}

double Operation::getResta(Token operando_1, Token operando_2)
{
	return operando_1.getNumber() - operando_2.getNumber();
}

double Operation::getMult(Token operando_1, Token operando_2)
{
	return operando_1.getNumber() * operando_2.getNumber();
}

double Operation::getDiv(Token numerador, Token divisor)
{
	double result = 0;
	if (divisor.getNumber() == 0) {
		//error division por 0
		return result;
	}
	return numerador.getNumber() / divisor.getNumber();
}

double Operation::getPow(Token operando, Token exponente)
{
	return pow(operando.getNumber(), exponente.getNumber());
}

double Operation::getRaiz(Token operando_1, Token operando_2)
{
	double root = 0;
	if (operando_1.getNumber() == 0) {
		//error: indice igual a 0
		return 0;
	}
	root = 1 / operando_1.getNumber();
	return pow(operando_2.getNumber(), root);
}

double Operation::getLog(Token operando_1, Token operando_2)
{
	if (operando_1.getNumber() == 0 || operando_2.getNumber() == 0) {
		// error: log 0;
		return 0;
	}
	if (log2(operando_1.getNumber()) == 0) {
		// error division por 0
		return 0;
	}
	return log2(operando_2.getNumber()) / log2(operando_1.getNumber());
}
