#pragma once
#include "SFML/Graphics.hpp"

struct Ordonne {
	float s;
	float i;
	float r;
};

class Graph
{
public:
	Graph(sf::Vector2f posInit, sf::Vector2f sizeInit);

	void setPeopleNumber(unsigned int nbPeople);
	void addOrdonne(Ordonne ord);

	void reset();

	void show(sf::RenderWindow* window);
	void show2(sf::RenderWindow* window);


private:
	unsigned int nbPeople;

	std::vector<Ordonne> coord;

	sf::Vector2f pos;
	sf::Vector2f size;
};

