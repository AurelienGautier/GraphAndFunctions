#include "Graph.hpp"

Graph::Graph(std::string xAxisName, std::string yAxisName) : m_axisSize(700), m_graduationSize(15)
{
	this->m_graphPos.x = 100;
	this->m_graphPos.y = 800;

	// Loading the font
	if (!this->m_font.loadFromFile("BMgermar.TTF"))
	{
		std::cerr << "Impossible de charger la police" << std::endl;
		exit(EXIT_FAILURE);
	}

	// Creating the axis
	this->m_xAxis = sf::RectangleShape(sf::Vector2f(this->m_axisSize, 5));
	this->m_yAxis = sf::RectangleShape(sf::Vector2f(this->m_axisSize, 5));
	m_yAxis.rotate(270);

	// Placing the axis
	this->m_xAxis.setPosition(this->m_graphPos);
	this->m_yAxis.setPosition(this->m_graphPos);

	// Creating texts of the axis 
	this->m_xAxisText = sf::Text(xAxisName, this->m_font, 24);
	this->m_yAxisText = sf::Text(yAxisName, this->m_font, 24);

	// Placing texts of the axis
	this->m_xAxisText.setPosition(this->m_graphPos.x + this->m_axisSize, this->m_graphPos.y);
	this->m_yAxisText.setPosition(this->m_graphPos.x - 50, this->m_graphPos.y - (m_axisSize + 25));

	this->m_graduation = sf::RectangleShape(sf::Vector2f(this->m_graduationSize, 3));

	// Initializing the grid lines
	this->m_gridLine = sf::RectangleShape(sf::Vector2f(this->m_axisSize, 3));
	this->m_gridLine.setFillColor(sf::Color(155, 155, 155));

	this->m_point = sf::CircleShape(5.f);
}

/*---------------------------------------------------------------------------------------*/

void Graph::display(sf::RenderWindow &window)
{
	// Drawing the axis
	window.draw(this->m_xAxis);
	window.draw(this->m_yAxis);

	// Drawing the texts of the axis
	window.draw(this->m_xAxisText);
	window.draw(this->m_yAxisText);

	// Drawing every part of the graph if there 
	if (this->m_values.size() > 0)
	{
		this->drawXgraduationsAndGridLines(window);
		this->drawYgraduationsAndGridLines(window);
		this->drawPoints(window);
		this->drawLegend(window);
	}
}

/*---------------------------------------------------------------------------------------*/

void Graph::drawXgraduationsAndGridLines(sf::RenderWindow& window)
{
	// Creating the rectangle representing the graduations
	int graduationSize = 15;
	sf::RectangleShape graduation(sf::Vector2f(graduationSize, 3));

	// Creating the rectangle representing the grid lines
	sf::RectangleShape gridLine(sf::Vector2f(this->m_axisSize, 3));
	gridLine.setFillColor(sf::Color(155, 155, 155));

	// Drawing every graduation grid lines for the X axis
	for (float i = m_graphPos.x; i <= m_graphPos.x + m_axisSize; i += this->m_xInterval)
	{	
		graduation.setPosition(i, m_graphPos.y + graduationSize);
		gridLine.setPosition(i, m_graphPos.y);

		sf::Text graduationValue;

		if (graduation.getRotation() != 270)
		{
			graduation.rotate(270);
			gridLine.rotate(270);
		}

		window.draw(graduation);

		if (i != m_graphPos.x)
		{
			window.draw(gridLine);
		}
	}
}

/*---------------------------------------------------------------------------------------*/

void Graph::drawYgraduationsAndGridLines(sf::RenderWindow& window)
{	
	// Drawing every graduation grid lines for the Y axis
	for (float i = m_graphPos.y; i >= m_graphPos.y - m_axisSize; i -= this->m_yInterval)
	{
		this->m_graduation.setPosition(m_graphPos.x - this->m_graduationSize / 2 - 3, i);
		this->m_gridLine.setPosition(this->m_graphPos.x + this->m_graduationSize / 2, i);

		window.draw(this->m_graduation);

		if (i != m_graphPos.y)
		{
			window.draw(this->m_gridLine);
		}
	}
}

/*---------------------------------------------------------------------------------------*/

void Graph::drawPoints(sf::RenderWindow& window)
{
	for (int i = 0; i < this->m_values.size(); i++) // For each points cloud
	{
		this->m_point.setFillColor(this->m_curveColours[i]);

		for (int j = 0; j < m_values[i].size(); j++) // For each point of the points cloud
		{
			float posX = m_graphPos.x + this->m_values[i][j].x * m_xInterval - this->m_lowestXvalue * this->m_xInterval;
			float posY = m_graphPos.y - this->m_values[i][j].y * m_yInterval + this->m_lowestYvalue * this->m_yInterval;

			this->m_point.setPosition(posX, posY);

			window.draw(this->m_point);
		}
	}
}

/*---------------------------------------------------------------------------------------*/

void Graph::drawLegend(sf::RenderWindow& window)
{
	for (int i = 0; i < this->m_values.size(); i++) // For each points cloud
	{
		// Creating the square of the legend 
		sf::RectangleShape square(sf::Vector2f(20, 20));
		square.setFillColor(this->m_curveColours[i]);
		square.setPosition(m_graphPos.x + m_axisSize + 100, m_graphPos.y - m_axisSize + i*30);

		// Creating the text corresponding to the square
		sf::Text text(this->m_valuesNames[i], this->m_font, 30);
		text.setPosition(m_graphPos.x + m_axisSize + 130, m_graphPos.y - m_axisSize + i * 30 - 12);

		window.draw(square);
		window.draw(text);
	}
}

/*---------------------------------------------------------------------------------------*/

void Graph::addValues(std::vector<sf::Vector2f> valuesToAdd, std::string valuesName)
{
	// Set the default extreme values (if they are not initialized)
	if (this->m_values.size() == 0)
	{
		this->m_greatestXvalue = valuesToAdd[0].x;
		this->m_lowestXvalue = valuesToAdd[0].x;

		this->m_greatestYvalue = valuesToAdd[0].y;
		this->m_lowestYvalue = valuesToAdd[0].y;
	}

	 //Calculing the extreme values
	for (unsigned char i = 0; i < valuesToAdd.size(); i++)
	{
		// For the x values
		if (valuesToAdd[i].x > this->m_greatestXvalue)
		{
			this->m_greatestXvalue = valuesToAdd[i].x;
		}
		else if(valuesToAdd[i].x < this->m_lowestXvalue)
		{
			this->m_lowestXvalue = valuesToAdd[i].x;
		}

		// For the y values
		if (valuesToAdd[i].y > this->m_greatestYvalue)
		{
			this->m_greatestYvalue = valuesToAdd[i].y;
		}
		else if (valuesToAdd[i].y < this->m_lowestYvalue)
		{
			this->m_lowestYvalue = valuesToAdd[i].y;
		}
	}

	this->m_xInterval = m_axisSize / (m_greatestXvalue - m_lowestXvalue);
	this->m_yInterval = m_axisSize / (m_greatestYvalue - m_lowestYvalue);

	this->m_values.push_back(valuesToAdd);
	this->m_valuesNames.push_back(valuesName);
	this->m_curveColours.push_back(getRandomColour());
}

/*---------------------------------------------------------------------------------------*/

sf::Color getRandomColour()
{
	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_int_distribution<short> distr(100, 255);

	return sf::Color(distr(eng), distr(eng), distr(eng));
}