#include "main.hpp"

int main()
{
    MathFunction affine("3x+2");
    
    std::cout << "Le resultat est : " << affine.getResult("5");

	/*sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Fenetre");

    sf::Event event;

    while(window.isOpen())
    {
        window.clear(sf::Color::Black);

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.display();
    }*/

	return 0;
}