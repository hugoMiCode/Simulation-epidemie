#include "Box.h"
#include <iostream>

int main()
{
    srand(time(NULL));

    sf::Vector2f sizeBox{ 500, 500 };

    Features features{};

    features.daySimulation = 100;
    features.initInfecte = 0.01f;
    features.multiplicateur = 1.8f;
    features.lengthDay = 1.f / features.multiplicateur;
    features.radius = 10.f;

    features.tau = 7.f / features.multiplicateur; // temps infecté
    features.delta = 14 / features.multiplicateur; // temps rétablie
    features.probaInfection = 0.15f;

    sf::RenderWindow window(sf::VideoMode(1080, 720), "TIPE simulation");
    Graph graph(sf::Vector2f(30, 110), sizeBox);
    Box box(&graph, sf::Vector2f(550, 110), sizeBox, features);

    box.setPeopleNumber(2000);


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        box.loop();

        window.clear(sf::Color::White);
        box.show(&window);
        graph.show(&window);
        window.display();
    }

    return 0;
}