#ifndef MORPION_GRILLE_H
#define MORPION_GRILLE_H


#include <vector>
#include "Case.h"
#include "Motif.h"

class Grille {
private:

    Case * grid;

    unsigned int dimX;

    unsigned int dimY;

    bool haveOneCommonCharacteristic(std::vector<Pion*> pions);

    bool batonWin();

    bool l_normalWin();

    bool l_inverseWin();

    bool blocWin();

    bool biais_normalWin();

    bool tWin();

    bool biais_inverseWin();

    bool horizontalOrVerticalWin();

    bool diagonalOrReverseDiagonalWin();

public:

    Grille();

    unsigned int getDimX() const;

    unsigned int getDimY() const;

    Case & getCase(unsigned int x, unsigned int y);

    void setCase(unsigned int x, unsigned int y, Pion * p);

    bool win();

    bool full();

    int heuristicValueHorizontal(unsigned int indice);

    int heuristicValueVertical(unsigned int indice);

    int heuristicValueDiagonal();

    int heuristicValueAntiDiagonal();

    int heuristicValue();

    bool win(Motif motif);


};


#endif //MORPION_GRILLE_H
