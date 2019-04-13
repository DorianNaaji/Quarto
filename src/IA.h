/**
 * @file IA.h
 * @author ARMANET Nathan, NAAJI Dorian
 * @version 1.0
 * @date 10/04/2019
 */

#ifndef QUARTO_IA_H
#define QUARTO_IA_H


#include <vector>
#include "Grille.h"

class IA {
private:

    /**
     * @brief Grille de jeu
     */
    Grille grid;

    /**
     * @brief toutes les situation possible a partie de grid
     */
    std::vector<IA> children;

    /**
     * @brief valeur de la situation
     */
    int value;

    /**
     * @brief coordonnées X et Y de la case et indice du pion
     */
    unsigned int ind_x, ind_y, ind_Pion;

public:

    /**
     * @brief crée un arbre de hauteur deptFin
     * @param [in] g grille de jeu
     * @param [in] deptDepart profondeur initiale
     * @param [in] deptFin profondeur finale
     * @param [in] tabPion tableau des pions disponibles
     * @param [in] pionDeart pion à jouer à la profondeur 0
     */
    void remplirArbre(Grille g, int deptDepart, int deptFin, Pion * * tabPion, Pion * pionDeart = nullptr);

    /**
     * @brief trouve la meilleur case pour placer le pion
     * @param [in,out] x coordonnées X de la case
     * @param [in,out] y coordonnées Y de la case
     * @param [in] alpha valeur extrème inférieur
     * @param [in] beta valeur extrème supérieur
     * @param [in] tour tour lié à la situation
     * @param [in] maximizingPlayer savoir si on veut la meilleur ou la pire case
     * @return valeur de la situation
     */
    int alphaBeta(int & x, int & y, int alpha, int beta, unsigned int tour, bool maximizingPlayer);

    /**
     *
     * @param [in,out] indPion indice du pion
     * @param [in] alpha valeur extrème inférieur
     * @param [in] beta valeur extrème supérieur
     * @param [in] tour tour lié à la situation
     * @param [in] maximizingPlayer savoir si on veut la meilleur ou la pire case
     * @return valeur de la situation
     */
    int selectPion(int & indPion, int alpha, int beta, unsigned int tour, bool maximizingPlayer);

};


#endif //QUARTO_IA_H
