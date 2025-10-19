#include "token.h"

Token::Token(TokenType ttype, string value) : tokenType(ttype), value(value)
{
    if (ttype == TOKEN_TYPE_NUMBER)
    {
        numberValue = stod(value);
    }
}

Token::Token(TokenType ttype, double numberValue) :
    numberValue(numberValue), tokenType(ttype), value(to_string(numberValue))
{
}

Token::Token(TokenType ttype, PrecedenceType ptype, string value) :
    tokenType(ttype), precedenceType(ptype), value(value)
{
    if (ttype == TOKEN_TYPE_NUMBER)
    {
        numberValue = stod(value);
    }
}

Token::Token(TokenType ttype, PrecedenceType ptype, double numberValue) :
    numberValue(numberValue), tokenType(ttype), precedenceType(ptype),
    value(to_string(numberValue))
{
}

TokenType Token::getType() { return tokenType; }

PrecedenceType Token::getPrecedenceType() { return precedenceType; }

string Token::getValue() { return value; }

double Token::getNumber() { return numberValue; }

bool Token::isNumber() { return tokenType == TOKEN_TYPE_NUMBER; }

bool Token::isOperator() { return tokenType == TOKEN_TYPE_OPERATOR; }

bool Token::isParenthesis() { return tokenType == TOKEN_TYPE_PARENTHESIS; }

bool Token::isPotencia() { return precedenceType == POTENCIA_RAIZ_LOG; }

bool Token::is_mul_div() { return precedenceType == MULT_DIV; }

bool Token::is_suma_resta() { return precedenceType == SUMA_RESTA; }
