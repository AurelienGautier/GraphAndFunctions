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
	bool isNumber(char character);
	bool isOperator(char character);
	int stringToNumber(std::string stringToTransform);
	void replaceX(std::string x);
	bool doOperation(double& result, std::vector<std::string>& vector, int index);
	bool isOperatorPresent(std::vector<std::string> vector, std::string stringOperator);
	void calculingOperations(std::string stringOperator, std::vector<std::string>& vector, double& result);

public:
	MathFunction(std::string function);
	double getResult(std::string x);
};
