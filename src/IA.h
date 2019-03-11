//
// Created by Nathan ARMANET on 2019-03-11.
//

#ifndef QUARTO_IA_H
#define QUARTO_IA_H


#include <vector>
#include "Grille.h"

class IA {
private:
    Grille grid;

    std::vector<IA> children;

    int value;

    unsigned int dept, ind_x, ind_y;

    Pion pion;

public:

    void remplirArbre(Grille g, int deptDepart, int deptFin, std::vector<Pion> & tabPion);

    int alphaBeta(unsigned int & x, unsigned int & y, Pion & pion, int alpha, int beta, unsigned int tour, bool maximizingPlayer);

};


#endif //QUARTO_IA_H
