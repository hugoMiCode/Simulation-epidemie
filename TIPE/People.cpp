#include "People.h"
#include <iostream>

People::People(sf::Vector2f posInit, Features features)
{
	state = State::S;
	pos = posInit;
	dir = pos;
	speed = 15.f * features.multiplicateur;
	initDelay = features.lengthDay * rand() / float(RAND_MAX);
	offsetTau = (features.tau * 0.25f) * (2.f * rand() / float(RAND_MAX) - 1.f);
	tau = features.tau;

	nbPInfected = std::vector<sf::Clock*>{};

	if (features.initInfecte > rand() / float(RAND_MAX))
		state = State::I;
}

sf::Vector2f People::getPosition()
{
	return pos;
}

sf::Vector2f People::getDir()
{
	return dir;
}

State People::getState()
{
	return state;
}

float People::getDistance(People people)
{
	sf::Vector2f pos0{ people.getPosition() };
	return std::sqrt(pow(pos.x - pos0.x, 2) + pow(pos.y - pos0.y, 2));
}

float People::getDayClock()
{
	return dayClock.getElapsedTime().asSeconds() + initDelay;
}

float People::getRecoveredClock()
{
	return recoveredClock.getElapsedTime().asSeconds();
}

float People::getInfectedClock()
{
	return infectedClock.getElapsedTime().asSeconds() + offsetTau;
}

float People::getAngle()
{
	float x1{ pos.x };
	float y1{ pos.y };

	float x2{ dir.x };
	float y2{ dir.y };

	float dis{ sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)) };
	if (dis > 0.1) {
		if (x2 < x1)
			return (acos((y1 - y2) / dis));
		else
			return (-acos((y1 - y2) / dis));
	}
	return 0;
}

int People::getnbPInfected()
{
	return nbPInfected.size();
}


void People::setState(State newState)
{
	if (state == State::S && newState == State::I) {
		dayClock.restart();
		infectedClock.restart();
	}
	else if (newState == State::R) {
		recoveredClock.restart();
	}

	state = newState;
}

void People::setPosition(sf::Vector2f newPos)
{
	pos = newPos;
}

void People::setDir(sf::Vector2f newDir)
{
	dir = newDir;
}

void People::move(sf::Vector2f offset)
{
	pos += offset;
}

void People::restartDayClock()
{
	initDelay = 0;
	dayClock.restart();
}

void People::addNbPInfected()
{
	nbPInfected.push_back(new sf::Clock);
}

void People::loop()
{
	float distance{ speed * moveClock.restart().asMicroseconds() * 0.000001f };
	float alpha;

	alpha = getAngle();

	pos.x += sin(alpha + 3.14f) * distance;
	pos.y += cos(alpha + 3.14f) * distance;

	
	std::vector<int> toDelete;
	if (!nbPInfected.empty())
		for (int i{ int(nbPInfected.size()) - 1 }; i >= 0; i--)
			if (nbPInfected[i]->getElapsedTime().asSeconds() > tau)
				toDelete.push_back(i);

	for (int i : toDelete) {
		delete nbPInfected[i];
		nbPInfected.erase(nbPInfected.begin() + i);
	}
}

void People::show(sf::RenderWindow* window)
{
	sf::CircleShape pt(3);
	pt.setOrigin(pt.getRadius(), pt.getRadius());
	pt.setPosition(pos);

	if (state == State::S)
		pt.setFillColor(sf::Color::Blue);
	else if (state == State::R)
		pt.setFillColor(sf::Color(80, 80, 80));
	else if (state == State::I)
		pt.setFillColor(sf::Color::Red);

	window->draw(pt);
}
