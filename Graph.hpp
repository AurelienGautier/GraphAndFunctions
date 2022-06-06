#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <array>
#include <vector>
#include <random>
#include "debug.hpp" // Temporary

class Graph
{
private:
	sf::Vector2f m_graphPos;
	int m_axisSize;

	sf::RectangleShape m_xAxis;
	sf::RectangleShape m_yAxis;

	sf::Font m_font;

	sf::Text m_xAxisText;
	sf::Text m_yAxisText;

	// The space between each graduation
	float m_xInterval;
	float m_yInterval;

	// Values to represent into the graph
	std::vector<std::vector<sf::Vector2f>> m_values;
	
	// Color of the curves
	std::vector<sf::Color> m_curveColours;

	std::vector<std::string> m_valuesNames;

	float m_greatestXvalue;
	float m_lowestXvalue;

	float m_greatestYvalue;
	float m_lowestYvalue;

	// Size and rectangle corresponding to the graduations of the graph
	int m_graduationSize;
	sf::RectangleShape m_graduation;

	sf::RectangleShape m_gridLine;

	sf::CircleShape m_point;

	void drawXgraduationsAndGridLines(sf::RenderWindow &window);
	void drawYgraduationsAndGridLines(sf::RenderWindow& window);
	void drawPoints(sf::RenderWindow& window);
	void drawLegend(sf::RenderWindow& window);
public:
	Graph(std::string xAxisName = "", std::string yAxisName = "");
	void display(sf::RenderWindow &window);
	void addValues(std::vector<sf::Vector2f> valuesToAdd, std::string valuesName);
};

sf::Color getRandomColour();