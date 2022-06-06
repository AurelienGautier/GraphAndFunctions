#include "debug.hpp"

template <typename T>
void print_matrix(std::vector<std::vector<const T>> matrix)
{
	std::cout << "------------------------------------------" << std::endl;

	for (unsigned char i = 0; i < matrix.size(); i++)
	{
		for (unsigned char j = 0; j < matrix[i].size(); j++)
		{
			std::cout << matrix[i][j] << "   ";
		}

		std::cout << std::endl;
	}

	std::cout << "------------------------------------------" << std::endl;
}