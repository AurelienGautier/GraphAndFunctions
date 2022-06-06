#include "main.hpp"

int main()
{
	// sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Fenetre");

    sf::Event event;

    Graph graph("Mois", "Prix");

    MathFunction affine("7*x");
    std::cout << "Le resultat est : " << affine.getResult("2");

    //while(window.isOpen())
    //{
    //    window.clear(sf::Color::Black);

    //    while (window.pollEvent(event))
    //    {
    //        if (event.type == sf::Event::Closed)
    //        {
    //            window.close();
    //        }
    //    }

    //    graph.display(window);

    //    window.display();
    //}

	return 0;
}