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
 * //TODO
 * PROBLEME : NE FONCTIONNE PAS
 * Tous ls pions, pris un à un, ont bien une caractéristiques en commun avec tous les autres
 * Mais les 4 pièces prises dans leur ensemble n'auront pas forcément toutes une caractéristiques en commun :
 * Ex avec un carré petit bleu, un cercle grand rouge, un cercle petit troué rouge et un carré petit troué rouge
 * cf doc pour verticalWin
 * @see bool Grille::verticalWin()
 * @return bool : gagné (true) ou non (false) à l'horizontale
 */
bool Grille::horizontalWin()
{
    unsigned int i;
    unsigned int j;
    unsigned int k;
    unsigned int nbVerificationsOK = 0;

    //On parcourt les lignes
    for(i = 0; i < this->dimX; i++)
    {
        // on reset le compteurs de verif car on change de ligne à la i-ème itération
        nbVerificationsOK = 0;
        // on parcourt les colonnes une à une
        for(j = 0; j < this->dimX; j++)
        {
            //on re-parcourt les colonnes, ce qui permet de parcourir les pions un à un
            for(k = 0; k < this->dimX; k++)
            {
               //std::cout << j << "," << i << " --> " << k << "," << i << std::endl;
                // si le pion courant (j, i) possède les mêmes caractéristiques que les 3 autres pions (k, i) dont lui-même
                if (this->getCase(j, i).getPion()->equals(this->getCase(k, i).getPion()))
                {
                    // on incrémente notre compteur
                    nbVerificationsOK++;
                    std::cout << nbVerificationsOK << std::endl;
                }
            }
        }
        // Si les 16 vérifications sont OK
        if(nbVerificationsOK == 16)
        {
            //std::cout<<"horizontal"<<std::endl;
            return true;
        }
    }
    // Si les 16 vérifications sont OK
    return false;
}

/**
*  L'algo compare le pion d'une colonne à son extrémité supérieure avec tous les autres.
*  Si le pion est similaire avec tous les autres, on incrémente un compteur de 1
*  Il y a donc 16 vérifications de correspondance de pion en tout. Si les 16 vérifications passent, on retourne vrai
*  En effet, on compare chaque pion à lui-même et aux 3 autres : Si un pion possède une caractéristique
*  en commun avec lui-même et les 3 autres de la même colonne,
*  nbVerificationsOK vaut 4, puis au prochain tour de boucle, on vérifie si le pion juste en dessous est possède
*  une caractéristique en commun avec lui-même et les 3 autres de la colonne et ainsi de suite,
*  jusqu'à avoir vérifié tous les pions de cette manière.
*  En vérifiant tous les pions de cette manière, on a donc au final 16 passages dans la conditionnelles
*  si les pions possèdent une caractéristiques en commun.
 * @param joueur le joueur sur lequel on souhaite faire la vérification de victoire
 * @return bool : gagné (true) ou non (false) à la verticale
 */
bool Grille::verticalWin()
{
    unsigned int i;
    unsigned int j;
    unsigned int k;
    unsigned int nbVerificationsOK = 0;

    //On parcourt les colonnes
    for(i = 0; i < this->dimX; i++)
    {
        // on reset le nombre de pions similaires car on change de colonne à la ième itération
        nbVerificationsOK = 0;
        // on parcourt les lignes une à une
        for(j = 0; j < this->dimX; j++)
        {
            //on re-parcourt les lignes une à une
            for(k = 0; k < this->dimX; k++)
            {
                // si le pion courant (i, j) possède les mêmes caractéristiques que les 3 autres pions (i, k) dont lui-même
                if (this->getCase(i, j).getPion()->equals(this->getCase(i, k).getPion()))
                {
                    // on incrémente notre compteur
                    nbVerificationsOK++;
                }
            }
        }
        // Si les 16 vérifications sont OK
        if(nbVerificationsOK == 16)
        {
            //std::cout<<"vertical"<<std::endl;
            return true;
        }
    }
    return false;
}


/**
 *
 * Compare chaque pion de la diagonale avec tous les autres
 * @return bool : gagné (true) ou non (false) avec la diagonale
 */
bool Grille::diagonalWin()
{
    unsigned int i;
    unsigned int j;
    unsigned int nbVerificationsOK = 0;

    for(i = 0; i < this->dimX; i++)
    {
        for(j = 0; j < this->dimX; j++)
        {
            if(this->getCase(i,i).getPion()->equals(this->getCase(j,j).getPion()))
            {
                nbVerificationsOK++;
            }
        }
    }
    return (nbVerificationsOK == 16);

}

/**
 *
 * Compare chaque pion de la diagonale inverse avec tous les autres
 * @return bool : gagné (true) ou non (false) avec la diagonale inverse
 */
bool Grille::reverseDiagonalWin()
{
    unsigned int i;
    unsigned int j;
    unsigned int k;
    unsigned int l;
    unsigned int nbVerificationsOK = 0;

    for(i = 0, j = 3; (i < this->dimX) && (j >= 0); i++, j--)
    {
        for(k = 0, l = 3; (k < this->dimX) && (l >= 0); k++, l--)
        {
            if(this->getCase(i, j).getPion()->equals(this->getCase(k, l).getPion()))
            {
                nbVerificationsOK++;
            }
        }
    }
    return (nbVerificationsOK == 16);
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
    }
}

bool Grille::batonWin()
{
    return this->horizontalWin();
}

bool Grille::l_normalWin()
{

}

bool Grille::l_inverseWin()
{

}

bool Grille::blocWin()
{

}

bool Grille::biais_normalWin()
{

}

bool Grille::tWin()
{

}

bool Grille::biais_inverseWin()
{

}
