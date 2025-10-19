#pragma once
#include <string>

using namespace std;

class ERRORS
{
public:

	static string errors;
	static void setError(string err);
	static string getError();
};

