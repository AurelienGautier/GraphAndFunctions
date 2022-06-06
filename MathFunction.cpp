#include "MathFunction.hpp"

MathFunction::MathFunction(std::string function) : m_stringFunction(function)
{
	this->separateTerms();
}

void MathFunction::separateTerms()
{
	// Separating every part of the string of the function
	for (unsigned char i = 0; i < this->m_stringFunction.size(); i++)
	{
		std::string toAdd = "";
		toAdd += this->m_stringFunction.at(i);

		m_terms.push_back(toAdd);
	}
}

double MathFunction::getResult(std::string x)
{
	this->replaceX(x);

	double resultat = 0;

	for (unsigned char i = 0; i < this->m_terms.size(); i++)
	{
		if (this->m_terms[i] == "*")
		{
			resultat += stringToNumber(this->m_terms[i - 1]) * stringToNumber(this->m_terms[i + 1]);
		}
	}

	return resultat;
}

bool MathFunction::isNumber(std::string character)
{
	if (character.at(0) >= 48 && character.at(0) <= 57) return true;
	return false;
}

int MathFunction::stringToNumber(std::string stringToTransform)
{
	return (int)stringToTransform.at(0) - 48;
}

void MathFunction::replaceX(std::string x)
{
	bool replaced = false;
	unsigned char i = 0;

	while (!replaced && i < this->m_terms.size())
	{
		if (this->m_terms[i] == "x")
		{
			this->m_terms[i] = x;
			replaced = true;
		}

		i++;
	}
}
