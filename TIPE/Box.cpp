#include "Box.h"
#include <iostream>

Box::Box(Graph* relativeGraph, sf::Vector2f posInit, sf::Vector2f sizeInit, Features initFeatures)
{
	pos = posInit;
	size = sizeInit;
	numberPeople = 0;
	graph = relativeGraph;
	annimated = true;
	nbPointGraph = 0;

	R0 = 0.f;
	day = 0;

	features = initFeatures;

	font.loadFromFile("OpenSans-Bold.ttf");
	textR0.setFont(font);
	textR0.setCharacterSize(20);
	textR0.setPosition(posInit);
	textR0.move(0, sizeInit.y + 10.f);
	textR0.setFillColor(sf::Color::Black);
}

void Box::resetPeople()
{
	for (unsigned int i{ 0 }; i < people.size(); i++) {
		delete people[i];
	}

	people.clear();
	graph->reset();

	for (unsigned int i{ 0 }; i < numberPeople; i++) {
		people.push_back(new People(getRandPos(), features));
	}
}

float Box::sigmoid(float x)
{
	return 1/(1 + std::exp(-x));
}

sf::Vector2f Box::getRandPos()
{
	sf::Vector2f posBox;
	posBox.x = (size.x * rand() / float(RAND_MAX)) + pos.x;
	posBox.y = (size.y * rand() / float(RAND_MAX)) + pos.y;

	return posBox;
}

unsigned int Box::getPeopleNumber()
{
	return numberPeople;
}

void Box::setPeopleNumber(unsigned int number)
{
	numberPeople = number;
	graph->setPeopleNumber(numberPeople);

	resetPeople();
}

void Box::loop()
{
	if (annimated) {
		if (clockGraph.getElapsedTime().asSeconds() > 0.04 / features.multiplicateur) {
			nbPointGraph++;
			float nbS{ 0 };
			float nbR{ 0 };
			float nbI{ 0 };

			for (People* person : people) {
				if (person->getState() == State::I)
					nbI++;
				else if (person->getState() == State::R)
					nbR++;
				else if (person->getState() == State::S)
					nbS++;
			}

			graph->addOrdonne(Ordonne{ nbS, nbI, nbR });

			clockGraph.restart();
		}


		// interaction entre les personnes 
		std::vector<unsigned int> tab;
		if (day < features.daySimulation) {
			for (unsigned int i{ 0 }; i < people.size(); i++) {
				if (people[i]->getDayClock() > features.lengthDay) {
					if (i == 0)
						day++;
					people[i]->restartDayClock();


					if (people[i]->getState() == State::I) {
						if (rand() / float(RAND_MAX) < sigmoid(people[i]->getInfectedClock() - features.tau)) {
							people[i]->setState(State::R);
						}
					}


					if (people[i]->getState() == State::R) {
						if (rand() / float(RAND_MAX) < sigmoid(people[i]->getRecoveredClock() - features.delta)) {
							people[i]->setState(State::S);
						}
					}

					else if (people[i]->getState() == State::I) {
						for (unsigned int j{ 0 }; j < people.size(); j++) {
							if (i == j) {
								j++;
								continue;
							}

							if (people[j]->getState() == State::S && people[i]->getDistance(*people[j]) <= features.radius) {
								if (rand() / float(RAND_MAX) < features.probaInfection) {
									tab.push_back(j);
									people[i]->addNbPInfected();
								}
							}
						}
					}
				}
			}
		}
		else {
			annimated = false;
		}

		std::vector <int> tabR0;
		for (People* person : people)
			if (person->getState() == State::I && person->getInfectedClock() > features.tau)
				tabR0.push_back(person->getnbPInfected());

		R0 = 0;
		if (!tabR0.empty()) {
			for (int val : tabR0)
				R0 += val;
			R0 /= float(tabR0.size());
		}

		textR0.setString("Ro = " + std::to_string(R0));

		for (int i : tab)
			people[i]->setState(State::I);

		for (People* person : people) {
			person->loop();
			sf::Vector2f dirPeople{ person->getDir() };
			sf::Vector2f posPeople{ person->getPosition() };

			if (sqrt(pow(dirPeople.x - posPeople.x, 2) + pow(dirPeople.y - posPeople.y, 2)) < 5) {
				person->setDir(getRandPos());
			}
		}
	}
	else
		for (People* person : people)
			person->restartDayClock();
}

void Box::show(sf::RenderWindow* window)
{
	sf::RectangleShape box(size);
	box.setFillColor(sf::Color::Transparent);
	box.setPosition(pos);
	box.setOutlineThickness(5);
	box.setOutlineColor(sf::Color::Black);


	for (People* p : people) {
		p->show(window);
	}

	window->draw(textR0);
	window->draw(box);
}
