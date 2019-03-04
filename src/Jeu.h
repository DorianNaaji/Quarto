//
// Created by Nathan ARMANET on 2019-02-25.
//

#ifndef QUARTO_JEU_H
#define QUARTO_JEU_H


#include <vector>
#include "Grille.h"

class Jeu {
private:

    Grille * g;
    std::string J1, J2;
    std::vector<Pion> tabPion;

public:

    Jeu();

    void readListePion();
};


#endif //QUARTO_JEU_H
