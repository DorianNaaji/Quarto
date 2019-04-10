//
// Created by Nathan ARMANET on 2019-02-25.
//

#ifndef QUARTO_JEU_H
#define QUARTO_JEU_H


#include <vector>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Grille.h"
#include "IA.h"

class Jeu {
private:

    Grille * g{};
    unsigned int tour{};
    std::string J1, J2;
    Pion * * tabPion{};
    IA * ia{};
    void choixPieces(bool pvp);
    Motif _motif = NONE;

public:

    Jeu();

    void init();

    int selectPion(int mousseX, int mousseY, std::vector<sf::RectangleShape> & og);

    void selectCaseGrille(int mousseX, int mousseY, int & x, int & y);

    void menu();

    void resultat(const std::string& gagnant);

    void pvp();

    void IA_alpha_beta();
};


#endif //QUARTO_JEU_H
