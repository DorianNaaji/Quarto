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
        std::cout<<"Pions en partant d'en bas à droite : "<<std::endl;
        std::cout<<"PION 1"<<std::endl;
        std::cout<<this->getCase(3, 3).getPion()->print() <<std::endl;
        std::cout<<"PION 2"<<std::endl;
        std::cout<<this->getCase(2, 2).getPion()->print() <<std::endl;
        std::cout<<"PION 3"<<std::endl;
        std::cout<<this->getCase(1, 1).getPion()->print() <<std::endl;
        std::cout<<"PION 4"<<std::endl;
        std::cout<<this->getCase(0, 0).getPion()->print() <<std::endl;
         if
         (
                 (this->getCase(i, j).getPion()->equals(this->getCase(0, 0).getPion()))
                 && (this->getCase(i, j).getPion()->equals(this->getCase(1, 1).getPion()))
                 && (this->getCase(i, j).getPion()->equals(this->getCase(2, 2).getPion()))
                 && (this->getCase(i, j).getPion()->equals(this->getCase(3, 3).getPion()))
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
 * @return bool : gagné (true) ou non (false) avec la diagonale inverse
 */
bool Grille::reverseDiagonalWin(std::string &joueur)
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
