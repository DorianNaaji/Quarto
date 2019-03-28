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
 * @return bool : gagné (true) ou non (false) à l'horizontale
 */
bool Grille::horizontalWin()
{
    for(unsigned int i = 0; i < this->dimY; i++)
    {
        //bool monT = this->getCase(0, 0).getPion()->equals(this->getCase(1, 0).getPion());

        if(this->getCase(0, i).getPion()->equals(this->getCase(1, i).getPion())
        &&  this->getCase(0, i).getPion()->equals(this->getCase(2, i).getPion())
        &&  this->getCase(0, i).getPion()->equals(this->getCase(3, i).getPion())
        &&  this->getCase(0, i).getPion() != nullptr)
        {
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
bool Grille::verticalWin()
{
    for(unsigned int i = 0; i < this->dimX; i++)
    {
        if( this->getCase(i, 0).getPion()->equals(this->getCase(i, 1).getPion())
        && this->getCase(i, 0).getPion()->equals(this->getCase(i, 2).getPion())
        && this->getCase(i, 0).getPion()->equals(this->getCase(i, 3).getPion()))
        {
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
bool Grille::diagonalWin()
{
    unsigned int i;
    unsigned int j;
    int nbPionsSimilaires = 0;

    // va faire des vérifications parfois déjà faites ou dont on pourrait se passer
    // durant un tour de boucle mais
    // assure que les 4 pions alignés sur la diagonale ont bien tous des caractéristiques
    // en commun : Le pion en (0,0) va être comparé à tous les autres & lui-même,
    // Le pion en (1,1) également, puis celui en (2,2) et en (3,3).
    // La fonction utilise un compteur @see nbPionsSimilaires qui compte le nombre de pions
    // alignés et retourne si il est égal à 4 en fin de fonction.
    for(i = 0, j = 0; j < this->dimX; i++, j++)
    {
        if ((this->getCase(i, j).getPion()->equals(this->getCase(0, 0).getPion()))
            && (this->getCase(i, j).getPion()->equals(this->getCase(1, 1).getPion()))
            && (this->getCase(i, j).getPion()->equals(this->getCase(2, 2).getPion()))
            && (this->getCase(i, j).getPion()->equals(this->getCase(3, 3).getPion()))) {

             nbPionsSimilaires++;
         }
    }
    return (nbPionsSimilaires == 4);
}

/**
 *
 * @return bool : gagné (true) ou non (false) avec la diagonale inverse
 */
bool Grille::reverseDiagonalWin()
{
    unsigned int i;
    unsigned int j;
    int nbPionsSimilaires = 0;

    for(i = 0, j = 3; (i < this->dimX) && (j >= 0); i++, j--)
    {

        if
        (
            (this->getCase(i, j).getPion()->equals(this->getCase(0, 3).getPion())
             && this->getCase(i, j).getPion()->equals(this->getCase(1, 2).getPion())
             && this->getCase(i, j).getPion()->equals(this->getCase(2, 1).getPion())
             && this->getCase(i, j).getPion()->equals(this->getCase(3, 0).getPion()))
        )
        {
            nbPionsSimilaires++;
        }
    }
    return (nbPionsSimilaires == 4);
}

/**
 *
 * @param joueur le joueur sur lequel on souhaite faire la vérification de victoire
 * @return bool : gagné (true) ou non (false)
 */
bool Grille::win()
{
    return
    (
        (this->horizontalWin())
        || (this->verticalWin())
        || (this->diagonalWin())
        || (this->reverseDiagonalWin())
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