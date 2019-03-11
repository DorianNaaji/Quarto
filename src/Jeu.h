//
// Created by Nathan ARMANET on 2019-02-25.
//

#ifndef QUARTO_JEU_H
#define QUARTO_JEU_H


#include <vector>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Grille.h"

class Jeu {
private:

    Grille * g;
    unsigned int tour;
    std::string J1, J2;
    std::vector<Pion> tabPion;

public:

    Jeu();

    int selectPion(int mousseX, int mousseY, std::vector<sf::RectangleShape> & og);

    void selectCaseGrille(int mousseX, int mousseY, int & x, int & y);

    void run();
};


#endif //QUARTO_JEU_H
