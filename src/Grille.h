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
};


#endif //MORPION_GRILLE_H
