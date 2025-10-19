#include "tokenizer.h"

Tokenizer::Tokenizer(string _expression) {
	expression = _expression;
	readNumber = false;
	access = false;
	number = 0.0;
	denominator = 1.0;
	decimal = false;
}

void Tokenizer::setTokens() {
	for (index = 0; index < expression.size(); index++) {
		char ch = expression[index];
		if (isdigit(ch) || ch == '.') {
			if (!readNumber) {
				number = 0.0;
				readNumber = true;
				decimal = false;
				denominator = 1.0;
				index--;
			}
			else if (isdigit(ch)) {
				if (decimal) { 
					denominator *= 10.0; 
				}
				int _digito = ch - '0';
				number *= 10;
				number += _digito;
				access = true;
			}
			else if (ch == '.') {
				if (decimal) {} //return error
				decimal = true;
			}
			else {} //retorn error
		}
		if (readNumber && access) {
			if (index != (expression.size() - 1)) {
				if (expression[index + 1] == '.' || isdigit(expression[index + 1])) {
					readNumber = true;
					access = false;
					continue;
				}
			}
			double temp = number / denominator;
			push(Token(TOKEN_TYPE_NUMBER, to_string(temp)));
			readNumber = false;
			access = false;
		}
		if (isWriteSpace(ch)) { } 
		else if (isOperator(ch)) {
			push(getTokenPrecedence(ch));
		}
		else if (isParenthesis(ch)) {
			string _StringOperator(1, ch);
			push(Token(TOKEN_TYPE_PARENTHESIS, NULA, _StringOperator));
		}
	}
	if (readNumber) {
		double temp = number / denominator;
		push(Token(TOKEN_TYPE_NUMBER, to_string(temp)));
	}
}

bool Tokenizer::isWriteSpace(char ch) { 
	return ch == ' ' || ch == '\t';
}

bool Tokenizer::isOperator(char ch) {
	bool result = false;
	char op[] = {'+','-', '*', '/', '^', '_', 'v', 'V'};
	for (auto var : op) {
		if (ch == var) { 
			result = true; 
			break;
		}
	}
	return result;
}

bool Tokenizer::isParenthesis(char ch) {
	return ch == '(' || ch == ')';
}

Token Tokenizer::getTokenPrecedence(char ch) {
	string _StringOperator(1, ch);
	if (ch == '+' || ch == '-') {
		return Token(TOKEN_TYPE_OPERATOR, SUMA_RESTA, _StringOperator);
	}
	else if (ch == '*' || ch == '/') {
		return Token(TOKEN_TYPE_OPERATOR, MULT_DIV, _StringOperator);
	}
	else if (ch == '^' || ch == '_' || ch == 'v' || ch == 'V') {
		return Token(TOKEN_TYPE_OPERATOR, POTENCIA_RAIZ_LOG, _StringOperator);
	}
}
