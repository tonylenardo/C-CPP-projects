#include "postfix.h"
#include "operation.h"
#include "errors.h"

void postfix::push(Token token) { tokenExpression.push(token); }

bool postfix::algoritmo_posFix()
{
    while (!tokenExpression.empty()) {
        Token token = tokenExpression.front();
        tokenExpression.pop();

        if (token.isNumber()) { tokenNumber.push(token); }
        else if (token.isOperator()) {
            if (!tokenOperators.empty()) {
                char valorTokenActual = tokenOperators.top().getValue()[0];
                int precedenceType = token.getPrecedenceType();

                while (valorTokenActual != '(' && tokenOperators.top().getPrecedenceType() >= precedenceType) {
                    if (tokenOperators.empty()) { break; }
                    Token temp = tokenOperators.top();
                    tokenOperators.pop();
                    tokenNumber.push(temp);
                    if (tokenOperators.empty()) { break; }
                }
            }
            tokenOperators.push(token);
        }
        if (token.getValue()[0] == '(') { tokenOperators.push(token); }
        if (token.getValue()[0] == ')') {
            while (tokenOperators.top().getValue()[0] != '(') {
                if (tokenOperators.empty()) {
                    ERRORS::setError("Los parentesis no coinciden");
                    return false;
                }
                Token temp = tokenOperators.top();
                tokenOperators.pop();
                tokenNumber.push(temp);
            }
            if (tokenOperators.top().getValue()[0] == '(') {
                Token temp = tokenOperators.top();
                tokenOperators.pop();
            }
        }
    }
    while (!tokenOperators.empty()) {
        if (tokenOperators.top().getValue()[0] != '(') { 
            ERRORS::setError("Los parentesis no coinciden");
        }
        Token temp = tokenOperators.top();
        tokenOperators.pop();
        tokenNumber.push(temp);
    }
    return true;
}

bool postfix::Evaluate()
{
    while (!tokenNumber.empty()) {
        Token token = tokenNumber.front();
        tokenNumber.pop();

        if (token.isNumber()) { tokenNumbersEvaluate.push(token); }
        else if (token.isOperator()) {

            if (tokenNumbersEvaluate.size() < 2) {
               ERRORS::setError("Error: no hay suficientes operandos");
                return false;
            }

            Token operand2 = tokenNumbersEvaluate.top();
            tokenNumbersEvaluate.pop();
            Token operand1 = tokenNumbersEvaluate.top();
            tokenNumbersEvaluate.pop();

            Token result = operaciones(operand1, operand2, token);
            if (result.getType() == TOKEN_TYPE_UNKNOWN) { return false; }
            tokenNumbersEvaluate.push(result);
        }
        else {
            ERRORS::setError("Error: no hay suficientes operandos");
            return false;
        }
    }
    if (tokenNumber.size() != 1) {
        ERRORS::setError("Error: no hay operandos suficientes");
        return false;
    }
    return true;
}

Token postfix::operaciones(Token operando_1, Token operando_2, Token operador)
{
    Operation operation;
    double result = 0;
    switch (operador.getValue()[0]) {
    case '+':
        result = operation.getSuma(operando_1, operando_2);
        break;
    case '-':
        result = operation.getResta(operando_1, operando_2);
        break;
    case '*':
        result = operation.getMult(operando_1, operando_2);
        break;
    case '/':
        result = operation.getDiv(operando_1, operando_2);
        break;
    case '^':
        result = operation.getPow(operando_1, operando_2);
        break;
    case 'V':
        result = operation.getRaiz(operando_1, operando_2);
        break;
    case '_':
        result = operation.getLog(operando_1, operando_2);
        break;
    default:
        return Token(TOKEN_TYPE_UNKNOWN, "");
    }
    return Token(TOKEN_TYPE_NUMBER, result); 
}

double postfix::GetResult() { return tokenNumbersEvaluate.top().getNumber(); }
