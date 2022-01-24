#include "Graph.h"

Graph::Graph(sf::Vector2f posInit, sf::Vector2f sizeInit)
{
	pos = posInit;
	size = sizeInit;
	nbPeople = 0;
}

void Graph::setPeopleNumber(unsigned int nbPeople)
{
	this->nbPeople = nbPeople;
}

void Graph::addOrdonne(Ordonne ord)
{
	coord.push_back(ord);
}

void Graph::reset()
{
	coord.clear();
}

void Graph::show2(sf::RenderWindow* window)
{
	sf::RectangleShape graph(size);
	graph.setFillColor(sf::Color::Black);
	graph.setPosition(pos);
	graph.setOutlineThickness(5);
	graph.setOutlineColor(sf::Color::White);

	window->draw(graph);
}

void Graph::show(sf::RenderWindow* window)
{
	sf::RectangleShape graph(size);
	graph.setFillColor(sf::Color::White);
	graph.setPosition(pos);
	graph.setOutlineThickness(5);
	graph.setOutlineColor(sf::Color::Black);

	window->draw(graph);

	std::vector<sf::Vector2f> coordPt;
	
	if (!coord.empty()) {
		sf::CircleShape pt(3);
		pt.setOrigin(pt.getRadius(), pt.getRadius());
	
		for (int x{ 0 }; x < coord.size(); x++) {
			float posX{ pos.x + size.x * (x / float(coord.size() - 1)) };
			float posYi{ pos.y + size.y - size.y * (coord[x].i / nbPeople) };
			float posYs{ pos.y + size.y - size.y * (coord[x].s / nbPeople) };
			float posYr{ pos.y + size.y - size.y * (coord[x].r / nbPeople) };

			pt.setPosition(posX, posYi);
			pt.setFillColor(sf::Color::Red);
			window->draw(pt);

			pt.setPosition(posX, posYs);
			pt.setFillColor(sf::Color::Blue);
			window->draw(pt);

			pt.setPosition(posX, posYr);
			pt.setFillColor(sf::Color(80, 80, 80));
			window->draw(pt);
		}
	}
}
