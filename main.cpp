#include <iostream>
#include "src/Jeu.h"
#include <SFML/Graphics.hpp>

int main() {
    Jeu j;
    j.readListePion();

    // création de la fenêtre
    sf::RenderWindow window(sf::VideoMode(1350, 1100), "Quarto");

    std::vector<sf::RectangleShape> grille;

    for (int i = 0; i < 16; ++i) {
        sf::RectangleShape rect(sf::Vector2f(150.f, 150.f));
        rect.setPosition(20+155*(i%4), 20+155*(i/4));
        rect.setFillColor(sf::Color::Transparent);
        rect.setOutlineThickness(5.f);
        rect.setOutlineColor(sf::Color::Black);

        grille.push_back(rect);
    }

    std::vector<sf::RectangleShape> openGrille;

    for (int i = 0; i < 16; ++i) {
        sf::RectangleShape rect(sf::Vector2f(150.f, 150.f));
        rect.setPosition(20+155*(i%8), 700+155*(i/8));
        rect.setFillColor(sf::Color::Transparent);
        rect.setOutlineThickness(5.f);
        rect.setOutlineColor(sf::Color::Black);

        grille.push_back(rect);
    }


    // on fait tourner le programme tant que la fenêtre n'a pas été fermée
    while (window.isOpen())
    {
        // on traite tous les évènements de la fenêtre qui ont été générés depuis la dernière itération de la boucle
        sf::Event event;
        while (window.pollEvent(event))
        {
            // fermeture de la fenêtre lorsque l'utilisateur le souhaite
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // effacement de la fenêtre en blanc
        window.clear(sf::Color::White);

        // c'est ici qu'on dessine tout
        // window.draw(...);

        for (sf::RectangleShape child : grille) {
            window.draw(child);
        }

        // fin de la frame courante, affichage de tout ce qu'on a dessiné
        window.display();
    }

    return 0;
}