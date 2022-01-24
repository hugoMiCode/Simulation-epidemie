#pragma once
#include "People.h"
#include "Graph.h"


class Box
{
public:
	Box(Graph* relativeGraph, sf::Vector2f posInit, sf::Vector2f sizeInit, Features initFeatures);

	void resetPeople();
	float sigmoid(float x);

	sf::Vector2f getRandPos();
	unsigned int getPeopleNumber();

	void setPeopleNumber(unsigned int number);

	void loop();
	void show(sf::RenderWindow* window);

private:
	Features features;
	Graph* graph;
	unsigned int numberPeople;
	bool annimated;
	std::vector<People*> people;
	sf::Vector2f pos;
	sf::Vector2f size;
	sf::Clock clockGraph;

	sf::Font font;
	sf::Text textR0;

	int nbPointGraph;
	int day;

	float R0;
};

