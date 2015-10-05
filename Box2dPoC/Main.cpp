#include <iostream>
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

using namespace std;


int main(){
	

	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}



	//init();


	//cin.get();
	return 0;
}

void init(){
	b2Vec2 gravity;
	gravity.Set(0.0f, -10.0f);
	


}