#include "errors.h"

string ERRORS::errors = "";
void ERRORS::setError(string err) { errors = err; }

string ERRORS::getError() { return errors; }
