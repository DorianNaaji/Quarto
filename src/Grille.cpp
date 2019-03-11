#include <iostream>
#include "Grille.h"
#include <assert.h>


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
 * @param joueur le joueur sur lequel on souhaite faire la vérification de victoire
 * @return bool : gagné (true) ou non (false) à l'horizontale
 */
bool Grille::horizontalWin(std::string &joueur)
{
    for(unsigned int i = 0; i < this->dimY; i++)
    {
        //bool monT = this->getCase(0, 0).getPion()->equals(this->getCase(1, 0).getPion());

        if(this->getCase(0, i).getPion()->equals(this->getCase(1, i).getPion())
        &&  this->getCase(0, i).getPion()->equals(this->getCase(2, i).getPion())
        &&  this->getCase(0, i).getPion()->equals(this->getCase(3, i).getPion())
        &&  this->getCase(0, i).getPion() != nullptr)
        {
            joueur = "horizontal";
            return true;
        }
    }
    return false;
}

/**
 *
 * @param joueur le joueur sur lequel on souhaite faire la vérification de victoire
 * @return bool : gagné (true) ou non (false) à la verticale
 */
bool Grille::verticalWin(std::string &joueur)
{
    for(unsigned int i = 0; i < this->dimX; i++)
    {
        if( this->getCase(i, 0).getPion()->equals(this->getCase(i, 1).getPion())
        && this->getCase(i, 0).getPion()->equals(this->getCase(i, 2).getPion())
        && this->getCase(i, 0).getPion()->equals(this->getCase(i, 3).getPion()))
        {
            joueur = "vertical";
            return true;
        }
    }
    return false;
}

/**
 *
 * @param joueur le joueur sur lequel on souhaite faire la vérification de victoire
 * @return bool : gagné (true) ou non (false) avec la diagonale
 */
bool Grille::diagonalWin(std::string &joueur)
{
    if (this->getCase(0, 0).getPion()->equals(this->getCase(1, 1).getPion())
        && this->getCase(0, 0).getPion()->equals(this->getCase(2, 2).getPion())
        && this->getCase(0, 0).getPion()->equals(this->getCase(3, 3).getPion())) {

        joueur = "diag";
        return true;
    }

    return false;
    /*return
        this->getCase(0, 0).getPion()->equals(this->getCase(1, 1).getPion())
        && this->getCase(0, 0).getPion()->equals(this->getCase(2, 2).getPion())
        && this->getCase(0, 0).getPion()->equals(this->getCase(3, 3).getPion());*/
}

/**
 *
 * @param joueur le joueur sur lequel on souhaite faire la vérification de victoire
 * @return bool : gagné (true) ou non (false) avec la diagonale inverse
 */
bool Grille::reverseDiagonalWin(std::string &joueur)
{
    if (this->getCase(0, 3).getPion()->equals(this->getCase(1, 2).getPion())
        && this->getCase(0, 3).getPion()->equals(this->getCase(2, 1).getPion())
        && this->getCase(0, 3).getPion()->equals(this->getCase(3, 0).getPion())) {

        joueur = "anti-diag";
        return true;
    }

    return false;

    /*return
        this->getCase(0, 3).getPion()->equals(this->getCase(1, 2).getPion())
        && this->getCase(0, 3).getPion()->equals(this->getCase(2, 1).getPion())
        && this->getCase(0, 3).getPion()->equals(this->getCase(3, 0).getPion());*/
}

/**
 *
 * @param joueur le joueur sur lequel on souhaite faire la vérification de victoire
 * @return bool : gagné (true) ou non (false)
 */
bool Grille::win(std::string &joueur)
{
    return
    (
        (this->horizontalWin(joueur))
        || (this->verticalWin(joueur))
        || (this->diagonalWin(joueur))
        || (this->reverseDiagonalWin(joueur))
    );
}

bool Grille::full() {
    for (unsigned int i = 0; i < dimX; ++i) {
        for (unsigned int j = 0; j < dimY; ++j) {
            if (getCase(i, j).getPion() == nullptr) return false;
        }
    }
    return true;
}
