#include <iostream>
#include "Grille.h"
#include <assert.h>
#include <vector>


Grille::Grille() {
    this->dimX = 4;
    this->dimY = 4;

    this->grid = new Case[this->dimX * this->dimY];
}

unsigned int Grille::getDimX() const {
    return dimX;
}

unsigned int Grille::getDimY() const {
    return dimY;
}

Case & Grille::getCase(unsigned int x, unsigned int y) {
    assert(x<dimX);
    assert(y<dimY);
    return grid[y*dimX+x];
}

void Grille::setCase(unsigned int x, unsigned int y, Pion * p) {
    if (x < dimX && y < dimY) grid[y*dimX+x].setPion(p);
}

/**
 *
 * @param pions A 4-sized vector containing pions
 * @return true if the "pions" have one common characteristic. False otherwise
 */
bool Grille::haveOneCommonCharacteristic(std::vector<Pion*> pions)
{
    bool canCheck = true;

    // making sure there's no nulls pions before checking their characteristics
    for(int i = 0; i < 4; i ++)
    {
        if(pions.at(i) == nullptr)
        {
            canCheck = false;
        }
    }
    if(canCheck)
    {
        if
        (
            // les pions ont tous un trou
            ((pions.at(0)->getTrou()) && (pions.at(1)->getTrou()) && (pions.at(2)->getTrou()) && (pions.at(3)->getTrou()))
            // les pions n'ont pas de trou
            ||  (!(pions.at(0)->getTrou()) && !(pions.at(1)->getTrou()) && !(pions.at(2)->getTrou()) && !(pions.at(3)->getTrou()))
            // les pions sont bleu
            ||  ((pions.at(0)->getCouleur()) && (pions.at(1)->getCouleur()) && (pions.at(2)->getCouleur()) && (pions.at(3)->getCouleur()))
            // les pions sont rouges
            ||  (!(pions.at(0)->getCouleur()) && !(pions.at(1)->getCouleur()) && !(pions.at(2)->getCouleur()) && !(pions.at(3)->getCouleur()))
            // les pions sont rectangulaires
            ||  ((pions.at(0)->getForme()) && (pions.at(1)->getForme()) && (pions.at(2)->getForme()) && (pions.at(3)->getForme()))
            // les pions sont ronds
            ||  (!(pions.at(0)->getForme()) && !(pions.at(1)->getForme()) && !(pions.at(2)->getForme()) && !(pions.at(3)->getForme()))
            // les pions sont grands
            ||  ((pions.at(0)->getTaille()) && (pions.at(1)->getTaille()) && (pions.at(2)->getTaille()) && (pions.at(3)->getTaille()))
            // les pions sont petits
            ||  (!(pions.at(0)->getTaille()) && !(pions.at(1)->getTaille()) && !(pions.at(2)->getTaille()) && !(pions.at(3)->getTaille()))
        )
        {
            return true;
        }
    }
    else
    {
        return false;
    }
}


bool Grille::horizontalOrVerticalWin()
{
    std::vector<Pion*> horizontalPions;
    std::vector<Pion*> verticalPions;
    for(unsigned int i = 0; i < this->dimX; i++)
    {
        horizontalPions.clear();
        verticalPions.clear();
        for(unsigned int j = 0; j < this->dimX; j++)
        {
            verticalPions.push_back(this->getCase(i, j).getPion());
            horizontalPions.push_back(this->getCase(j, i).getPion());
        }
        if(this->haveOneCommonCharacteristic(horizontalPions) || this->haveOneCommonCharacteristic(verticalPions))
        {
            return true;
        }
    }
    return false;
}



/**
 *
 * @return bool : gagné (true) ou non (false) avec la diagonale ou diagonale inverse
 */
bool Grille::diagonalOrReverseDiagonalWin()
{
    unsigned int i;
    unsigned int j;
    std::vector<Pion*> diagonalPions;
    std::vector<Pion*> reverseDiagonalPions;
    for(i = 0, j = 3; (i < this->dimX) && (j >= 0); i++, j--)
    {
        diagonalPions.push_back(this->getCase(i, j).getPion());
        reverseDiagonalPions.push_back(this->getCase(i, i).getPion());
    }
    if(this->haveOneCommonCharacteristic(diagonalPions) || this->haveOneCommonCharacteristic(reverseDiagonalPions))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 *
 * @param joueur le joueur sur lequel on souhaite faire la vérification de victoire
 * @return bool : gagné (true) ou non (false)
 */
bool Grille::win()
{
    return ( (this->horizontalOrVerticalWin()) || this->diagonalOrReverseDiagonalWin() );
}

bool Grille::full() {
    for (unsigned int i = 0; i < dimX; ++i) {
        for (unsigned int j = 0; j < dimY; ++j) {
            if (getCase(i, j).getPion() == nullptr) return false;
        }
    }
    return true;
}

int Grille::heuristicValueHorizontal(unsigned int indice) {
    int value, bestValue = 0;
    std::vector<Pion> tab;
    bool equals;
    for (unsigned int j1 = 0; j1 < dimY; ++j1) {
        tab.clear();
        tab.push_back(*(this->getCase(indice, j1).getPion()));

        for (unsigned int j2 = j1; j2 < dimY; ++j2) {
            for (auto &k : tab) {
                equals = k.equals(this->getCase(indice, j2).getPion());
            }
            tab.push_back(*(this->getCase(indice, j2).getPion()));
        }
        value = (int)tab.size();
        if (value > bestValue) bestValue = value;
    }

    return bestValue;
}

int Grille::heuristicValueVertical(unsigned int indice) {
    int value, bestValue = 0;
    std::vector<Pion> tab;
    bool equals;
    for (unsigned int i1 = 0; i1 < dimY; ++i1) {
        tab.clear();
        tab.push_back(*(this->getCase(i1, indice).getPion()));

        for (unsigned int i2 = i1; i2 < dimY; ++i2) {
            for (auto &k : tab) {
                equals = k.equals(this->getCase(i2, indice).getPion());
            }
            tab.push_back(*(this->getCase(i2, indice).getPion()));
        }
        value = (int)tab.size();
        if (value > bestValue) bestValue = value;
    }

    return bestValue;
}

int Grille::heuristicValueDiagonal() {
    int value, bestValue = 0;
    std::vector<Pion> tab;
    bool equals;
    for (unsigned int ind1 = 0; ind1 < dimX; ++ind1) {
        tab.clear();
        tab.push_back(*(this->getCase(ind1, ind1).getPion()));

        for (unsigned int ind2 = ind1; ind2 < dimY; ++ind2) {
            for (auto &k : tab) {
                equals = k.equals(this->getCase(ind2, ind2).getPion());
            }
            tab.push_back(*(this->getCase(ind2, ind2).getPion()));
        }
        value = (int)tab.size();
        if (value > bestValue) bestValue = value;
    }

    return bestValue;
}

int Grille::heuristicValueAntiDiagonal() {
    int value, bestValue = 0;
    std::vector<Pion> tab;
    bool equals;
    for (unsigned int ind1 = 0; ind1 < dimX; ++ind1) {
        tab.clear();
        tab.push_back(*(this->getCase(ind1, 3-ind1).getPion()));

        for (unsigned int ind2 = ind1; ind2 < dimY; ++ind2) {
            for (auto &k : tab) {
                equals = k.equals(this->getCase(ind2, 3-ind2).getPion());
            }
            tab.push_back(*(this->getCase(ind2, 3-ind2).getPion()));
        }
        value = (int)tab.size();
        if (value > bestValue) bestValue = value;
    }

    return bestValue;
}

int Grille::heuristicValue() {
    int value, bestValue = 0;
    // Comme dimX = dimY on peut faire une seule boucle
    for (unsigned int indice = 0; indice < dimX; ++indice) {
        value = heuristicValueHorizontal(indice);
        if (value > bestValue) bestValue = value;

        value = heuristicValueVertical(indice);
        if (value > bestValue) bestValue = value;
    }

    value = heuristicValueDiagonal();
    if (value > bestValue) bestValue = value;

    value = heuristicValueAntiDiagonal();
    if (value > bestValue) bestValue = value;

    return bestValue;
}


bool Grille::win(Motif motif)
{
    switch(motif)
    {
        case BATON:
            return this->batonWin();
            break;
        case L_NORMAL:
            return this->l_normalWin();
            break;
        case L_INVERSE:
            return this->l_inverseWin();
            break;
        case BLOC:
            return this->blocWin();
            break;
        case BIAIS_NORMAL:
            return this->biais_normalWin();
            break;
        case T:
            return this->tWin();
            break;
        case BIAIS_INVERSE:
            return this->biais_inverseWin();
            break;
        case NONE:
            break;
    }
}

bool Grille::batonWin()
{
    return this->horizontalOrVerticalWin();
}

bool Grille::l_normalWin()
{
    // (i, j), (i, j-1), (i+1, j), (i+2, j)
    // (i, j), (i-1, j), (i, j-1), (i, j-2)
    // (i, j), (i-1, j), (i-2, j), (i, j+1)
    // (i, j), (i+1, j), (i, j+1), (i, j+2)

    int offsets1 [] = {0, 0, 0, -1, 1, 0, 2, 0};
    int offsets2 [] = {0, 0, -1, 0, 0, -1, 0, -2};
    int offsets3 [] = {0, 0, -1, 0, -2, 0, 0, 1};
    int offsets4 [] = {0, 0, 1, 0, 0, 1, 0, 2};
    return ( (this->winMotifTetris(offsets1)) || (this->winMotifTetris(offsets2)) || (this->winMotifTetris(offsets3)) || (this->winMotifTetris(offsets4)) );
}

bool Grille::l_inverseWin()
{
    //todo
}

/**
 * thanks to the params, returns true if 4 given pions (according to their coordinates) have a common characteristics. False otherwise
 * @param coordinates : a vector of pairs of ints.
 * @return
 */
bool Grille::checkPionsWith4Coordinates(std::vector<std::pair<int, int>> coordinates)
{
    std::vector <Pion*> blockPions;
    for(int i = 0; i < coordinates.size(); i++)
    {
        blockPions.push_back(this->getCase(coordinates.at(i).first, coordinates.at(i).second).getPion());
    }
    return this->haveOneCommonCharacteristic(blockPions);
}

/**
 * Checks if the block tetris pattern is made in the grid
 * @return true if so. False otherwise
 * To perform a square pattern, the coordinates are : square : (i,j), (i+1,j), (i+1, j+1), (i, j+1)
 * so the offsets are 0, 0, 1, 0, 1, 1, 0, 1
 */
bool Grille::blocWin()
{
    // square : (i,j), (i+1,j), (i+1, j+1), (i, j+1)
    int offsets [] = {0, 0, 1, 0, 1, 1, 0, 1};
    return this->winMotifTetris(offsets);
}

bool Grille::biais_normalWin()
{
    //todo
}

bool Grille::tWin()
{
    // T : (i,j), (i-1,j), (i+1,j), (i,j-1) _|_
    // or : (i,j), (i,j-1), (i+1,j), (i,j+1) |-
    // or : (i,j), (i-1,j), (i+1,j), (i,j+1)  T
    // or : (i,j), (i-1,j), (i, j-1), (i, j+1) -|

    int offsets1 [] = {0, 0, -1, 0, 1, 0, 0, -1};
    int offsets2 [] = {0, 0, 0, -1, 1, 0, 0, 1};
    int offsets3 [] = {0, 0, -1, 0, 1, 0, 0, 1};
    int offsets4 [] = {0, 0, -1, 0, 0, -1, 0, 1};
    return ( (this->winMotifTetris(offsets1)) || (this->winMotifTetris(offsets2)) || (this->winMotifTetris(offsets3)) || (this->winMotifTetris(offsets4)) );
}

/**
 * says if the coordinates are out of the grid or not
 * @param coordinates
 * @return true if some of the coordinates are out of the grid. false otherwise
 */
bool Grille::outOfGrid(std::vector<std::pair<int, int>> coordinates)
{
    for(int i = 0; i < coordinates.size(); i++)
    {
        if
        (
                (coordinates.at(i).first < 0)
            ||  (coordinates.at(i).first > 3)
            ||  (coordinates.at(i).second < 0)
            ||  (coordinates.at(i).second > 3)
        )
        {
            return true;
        }
    }
    return false;
}

/**
 *
 * @param offsets array of 8 offsets applicated to 8 coordinates
 * @return true if the pattern is made. False otherwise
 */
bool Grille::winMotifTetris(int offsets[7])
{
    for(int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            std::vector <std::pair<int, int>> block;
            block.emplace_back(std::make_pair(i+offsets[0], j+offsets[1]));
            block.emplace_back(std::make_pair(i+offsets[2], j+offsets[3]));
            block.emplace_back(std::make_pair(i+offsets[4], j+offsets[5]));
            block.emplace_back(std::make_pair(i+offsets[6], j+offsets[7]));
            if(!this->outOfGrid(block))
            {
                if(this->checkPionsWith4Coordinates(block))
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Grille::biais_inverseWin()
{
    //todo
}
