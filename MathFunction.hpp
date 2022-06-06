#pragma once

#include <string>
#include <vector>
#include <iostream>

class MathFunction
{
private:
	std::string m_stringFunction;
	std::vector<std::string> m_terms;

	void separateTerms();
	bool isNumber(std::string character);
	int stringToNumber(std::string stringToTransform);
	void replaceX(std::string x);

public:
	MathFunction(std::string function);
	double getResult(std::string x);
};
