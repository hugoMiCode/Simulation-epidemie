#pragma once
#include <SFML/Graphics.hpp>

enum class State {
	I = 1,
	S = 2,
	R = 3,
};


struct Features {
	int daySimulation;
	float initInfecte;
	float multiplicateur;
	float radius;
	float lengthDay;
	float probaInfection;
	float tau;
	float delta;
	float probaRetablissement;
};


class People
{
public:
	People(sf::Vector2f posInit, Features features);

	sf::Vector2f getPosition();
	sf::Vector2f getDir();
	State getState();
	float getDistance(People people);
	float getDayClock();
	float getRecoveredClock();
	float getInfectedClock();
	float getAngle();
	int getnbPInfected();

	void setState(State newState);
	void setPosition(sf::Vector2f newPos);
	void setDir(sf::Vector2f newDir);
	void move(sf::Vector2f offset);
	void restartDayClock();
	void addNbPInfected();

	void loop();
	void show(sf::RenderWindow* window);


private:
	sf::Vector2f pos;
	sf::Vector2f dir;
	State state;
	sf::Clock dayClock;
	sf::Clock infectedClock;
	sf::Clock recoveredClock;
	sf::Clock moveClock;
	float speed;
	float initDelay;
	float offsetTau;
	float tau;

	std::vector<sf::Clock*> nbPInfected;
};

