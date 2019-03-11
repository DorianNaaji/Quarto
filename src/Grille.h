#ifndef MORPION_GRILLE_H
#define MORPION_GRILLE_H


#include "Case.h"

class Grille {
private:

    Case * grid;

    unsigned int dimX;

    unsigned int dimY;

public:

    Grille();

    unsigned int getDimX() const;

    unsigned int getDimY() const;

    Case & getCase(unsigned int x, unsigned int y);

    void setCase(unsigned int x, unsigned int y, Pion * p);

    bool horizontalWin(std::string &joueur);

    bool verticalWin(std::string &joueur);

    bool diagonalWin(std::string &joueur);

    bool reverseDiagonalWin(std::string &joueur);

    bool win(std::string &joueur);

    bool full();
};


#endif //MORPION_GRILLE_H
