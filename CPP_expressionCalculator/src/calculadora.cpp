#include "postfix.h"
#include "tokenizer.h"
#include "errors.h"

#include <iostream>
#include <string>

using namespace std;
int main() {
	string expresion;
	while (true) {
		std::getline(cin, expresion);
	
		for (int index = 0; index < expresion.size(); index++) {
			expresion[index] = toupper(expresion[index]);
		}
		if (expresion == "SALIR" || expresion.empty()) {
			break;
		}
		postfix postfix;
		Tokenizer tokenizer(expresion);
		tokenizer.setTokens();
		tokenizer.algoritmo_posFix();
		tokenizer.Evaluate();
		std::cout << "a.  " << expresion << std::endl;
		std::cout << "b.  RESULTADO: " << tokenizer.GetResult() << std::endl;
		std::cout << ERRORS::getError();
	}
	return 0;
}
