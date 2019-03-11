//
// Created by Nathan ARMANET on 2019-02-25.
//

#include "Jeu.h"
#include <math.h>
#include <iostream>
#include <SFML/Graphics.hpp>

Jeu::Jeu() {
    this->g = new Grille;
    this->J1 = "J1";
    this->J2 = "J2";

    Pion * p;
    bool tab[4];
    int k;
    std::string link;
    for (int i = 0; i < 16; i++) {
        k = i;
        link = "../images/";
        for (int j = 3; j >=0 ; --j) {
            if (k >= pow(2, j)) {
                tab[j] = true;
                k -= (int)pow(2, j);
                link += "1";
            } else {
                tab[j] = false;
                link += "0";
            }
        }
        link += ".png";
        p = new Pion(tab[3], tab[2], tab[1], tab[0], link);
        this->tabPion.push_back(*p);
    }
}

int Jeu::selectPion(int mousseX, int mousseY, std::vector<sf::RectangleShape> & og) {

    for (int i = 0; i < 16; ++i) {
        if ((20+155*(i%8) < mousseX)
            && (mousseX < (20+155*(i%8)+150))
            && ((700+155*(i/8)) < mousseY)
            && (mousseY < (700+155*(i/8)+150))
            && (og[i].getTexture() != nullptr)) {

            og[i].setOutlineColor(sf::Color::Red);

            return i;
        }
    }

    return -1;
}

void Jeu::selectCaseGrille(int mousseX, int mousseY, int & x, int & y) {
    for (unsigned int i = 0; i < 4; ++i) {
        for (unsigned int j = 0; j < 4; ++j) {
            if ((20+155*i < mousseX)
                && (mousseX < 150+20+155*i)
                && (20+155*j < mousseY)
                && (mousseY < 150+20+155*j)
                && (this->g->getCase(i, j).getPion() == nullptr)) {
                x = i;
                y = j;
                return;
            }
        }
    }
}

void Jeu::run() {
    int ind_pion = -1, ind_x = -1, ind_y = -1;

    // création de la fenêtre
    sf::RenderWindow _window(sf::VideoMode(1350, 1100), "Quarto", sf::Style::Titlebar | sf::Style::Close);

    std::vector<sf::RectangleShape> _grille;

    for (int i = 0; i < 16; ++i) {
        sf::RectangleShape rect(sf::Vector2f(150.f, 150.f));
        rect.setPosition(20+155*(i%4), 20+155*(i/4));
        rect.setOutlineThickness(5.f);
        rect.setOutlineColor(sf::Color::Black);
        rect.setTexture(nullptr);
        _grille.push_back(rect);
    }

    std::vector<sf::RectangleShape> _openGrille;

    sf::Texture * texture;
    for (int i = 0; i < 16; ++i) {
        texture = new sf::Texture;

        sf::RectangleShape rect(sf::Vector2f(150.f, 150.f));
        rect.setPosition(20+155*(i%8), 700+155*(i/8));
        rect.setOutlineThickness(5.f);
        rect.setOutlineColor(sf::Color::Transparent);

        texture->loadFromFile(this->tabPion[i].getLien_image(), sf::IntRect(0, 0, 400, 400));

        texture->setSmooth(true);

        rect.setTexture(texture);

        _openGrille.push_back(rect);
    }

    sf::Event event;

    // on fait tourner le programme tant que la fenêtre n'a pas été fermée
    while (_window.isOpen())
    {
        // on traite tous les évènements de la fenêtre qui ont été générés depuis la dernière itération de la boucle
        while (_window.pollEvent(event))
        {
            // fermeture de la fenêtre lorsque l'utilisateur le souhaite
            switch (event.type) {
                case sf::Event::Closed: _window.close();
                    break;

                case sf::Event::MouseButtonPressed:
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && ind_pion == -1) {
                        ind_pion = this->selectPion(sf::Mouse::getPosition(_window).x, sf::Mouse::getPosition(_window).y, _openGrille);
                    } else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        this->selectCaseGrille(sf::Mouse::getPosition(_window).x, sf::Mouse::getPosition(_window).y, ind_x, ind_y);

                        if (ind_pion != -1 && ind_y != -1) {
                            this->g->setCase(static_cast<unsigned int>(ind_x), static_cast<unsigned int>(ind_y), & this->tabPion[ind_pion]);
                            _grille[ind_y*4+ind_x].setTexture(_openGrille[ind_pion].getTexture());
                            _openGrille[ind_pion].setTexture(nullptr);
                        }

                        _openGrille[ind_pion].setOutlineColor(sf::Color::Transparent);

                        ind_pion = -1;
                        ind_x = -1;
                        ind_y = -1;

                        //gestion des conditions de victoire (affichage console uniquement)
                        bool win = this->g->win(J1);
                        if(win) {
                            std::cout<<"--- J1/J2 Gagne ---"<<std::endl;
                            std::cout<<J1<<std::endl;
                            // on ferme si c'est gagné (juste du test)
                            //_window.close();
                        } else if (this->g->full()) {
                            std::cout<<"pas de victoire"<<std::endl;
                        }
                    }
                    break;

                default:
                    break;
            }
        }

        // effacement de la fenêtre en blanc
        _window.clear(sf::Color::White);

        // c'est ici qu'on dessine tout
        // window.draw(...);

        for (sf::RectangleShape  & child : _grille) {
            _window.draw(child);
        }

        for (sf::RectangleShape & child : _openGrille) {
            _window.draw(child);
        }

        // fin de la frame courante, affichage de tout ce qu'on a dessiné
        _window.display();
    }

}
