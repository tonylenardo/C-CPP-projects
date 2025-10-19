#pragma once
#include <iostream>
#include <queue>
#include <stack>
#include <string>

using namespace std;

// enum con todos los tipos de token.
enum TokenType {
    TOKEN_TYPE_UNKNOWN,
    TOKEN_TYPE_NUMBER,
    TOKEN_TYPE_OPERATOR,
    TOKEN_TYPE_PARENTHESIS,
    TOKEN_TYPE_END
};

//Este enum permite indicar el orden de prioridad de cada operador.
enum PrecedenceType { NULA, SUMA_RESTA, MULT_DIV, POTENCIA_RAIZ_LOG, PRECEDENCIA_END };

class Token
{
public:
    Token(TokenType token_type, string value);
    Token(TokenType token_type, double value);

    // Contructor que incluye precedencia de operadores.
    Token(TokenType token_type, PrecedenceType precedence_type, string value);
    // Contructor que incluye precedencia de operadores.
    Token(TokenType token_type, PrecedenceType precedence_type, double value);

    // retorna el tipo de token que se le asigna a cada elemento de la expresión.
    TokenType getType();
    // retorna el tipo de precedencia asignada a cada elemento de la expresión.
    PrecedenceType getPrecedenceType();

    string getValue();
    double getNumber();

    bool isNumber();
    bool isOperator();
    bool isParenthesis();
    bool isPotencia();
    bool is_mul_div();
    bool is_suma_resta();

private:
    TokenType tokenType;
    PrecedenceType precedenceType;
    string value;
    double numberValue;
};
