#include "MathFunction.hpp"

MathFunction::MathFunction(std::string function) : m_stringFunction(function)
{
	this->separateTerms();
}

/*---------------------------------------------------------------------------------------*/

void MathFunction::separateTerms()
{
	unsigned char concernedIndex = 0;

	m_terms.push_back("");
	this->m_terms[0] += this->m_stringFunction.at(0);

	// Separating every part of the string of the function
	for (unsigned char i = 1; i < this->m_stringFunction.size(); i++)
	{
		// When there is not 2 successive numbers 
		if (!(this->isNumber(this->m_stringFunction.at(i - 1)) && 
			  this->isNumber(this->m_stringFunction.at(i))))
		{
			// Adding the multiplication when x is writtent without it
			if (this->m_stringFunction.at(i) == 'x' && isNumber(this->m_stringFunction.at(i-1)))
			{
				this->m_terms.push_back("*");
				concernedIndex++;
			}

			this->m_terms.push_back("");
			concernedIndex++;
		}
		
		this->m_terms[concernedIndex] += this->m_stringFunction.at(i);
	}

	for (std::string element : this->m_terms)
	{
		std::cout << element << std::endl;
	}
}

/*---------------------------------------------------------------------------------------*/

double MathFunction::getResult(std::string x)
{
	this->replaceX(x);
	
	double result = 0;
	
	// Calculing multiplications first
	calculingOperations("*", this->m_terms, result);

	// Calculing additions
	calculingOperations("+", this->m_terms, result);

	return result;
}

/*---------------------------------------------------------------------------------------*/

bool MathFunction::isNumber(char character)
{
	if (character >= 48 && character <= 57) return true;
	return false;
}

/*---------------------------------------------------------------------------------------*/

bool MathFunction::isOperator(char character)
{
	if (character == '+' ||
		character == '-' ||
		character == '*' ||
		character == '/')
	{
		return true;
	}

	return false;
}

/*---------------------------------------------------------------------------------------*/

int MathFunction::stringToNumber(std::string stringToTransform)
{
	int result = 0;

	// If the number is negative
	if (stringToTransform.at(0) == '-')
	{
		for (unsigned char i = 1; i < stringToTransform.size(); i++)
		{
			result += (stringToTransform.at(i) - 48) * pow(10, stringToTransform.size() - i - 1);
		}

		result = 0 - result;
	}
	else
	{
		for (unsigned char i = 0; i < stringToTransform.size(); i++)
		{
			result += (stringToTransform.at(i) - 48) * pow(10, stringToTransform.size() - i - 1);
		}
	}

	return result;
}

/*---------------------------------------------------------------------------------------*/

void MathFunction::replaceX(std::string x)
{
	unsigned char i = 0;

	for(unsigned char i = 0; i < this->m_terms.size(); i++)
	{
		if (this->m_terms[i] == "x")
		{
			this->m_terms[i] = x;
		}

		i++;
	}
}

/*---------------------------------------------------------------------------------------*/

bool MathFunction::doOperation(double& result, std::vector<std::string>& vector, int index)
{
	// Doing the operation
	if(vector[index] == "*") // If the operation is a multiplication
	{
		result = this->stringToNumber(vector[index - 1]) * this->stringToNumber(vector[index + 1]);
		vector[index - 1] = std::to_string(this->stringToNumber(vector[index - 1]) * this->stringToNumber(vector[index + 1]));
	}
	else if (vector[index] == "+") // If the operator is an addition
	{
		result = this->stringToNumber(vector[index - 1]) + this->stringToNumber(vector[index + 1]);
		vector[index - 1] = std::to_string(this->stringToNumber(vector[index - 1]) + this->stringToNumber(vector[index + 1]));
	}
	else if (vector[index] == "-") // If the operator is an substraction
	{
		result = this->stringToNumber(vector[index - 1]) - this->stringToNumber(vector[index + 1]);
		vector[index - 1] = std::to_string(this->stringToNumber(vector[index - 1]) - this->stringToNumber(vector[index + 1]));
	}

	// Erasing the previous and the following terms
	vector.erase(vector.begin() + index);
	vector.erase(vector.begin() + index);

	return true;
}

/*---------------------------------------------------------------------------------------*/

bool MathFunction::isOperatorPresent(std::vector<std::string> vector, std::string stringOperator)
{
	for (unsigned char i = 0; i < vector.size(); i++)
	{
		if (vector[i] == stringOperator)
		{
			return true;
		}
	}

	return false;
}

/*---------------------------------------------------------------------------------------*/

void MathFunction::calculingOperations(std::string stringOperator, std::vector<std::string>& vector, double& result)
{
	while (this->isOperatorPresent(vector, stringOperator))
	{
		unsigned char i = 0;
		bool operationDone = false;

		while (!operationDone && i < this->m_terms.size())
		{
			if (vector[i] == stringOperator)
			{
				operationDone = this->doOperation(result, vector, i);
			}

			i++;
		}
	}
}

/*---------------------------------------------------------------------------------------*/
