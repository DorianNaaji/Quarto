/**
 * @file Jeu.h
 * @author ARMANET Nathan, NAAJI Dorian
 * @version 1.0
 * @date 10/04/2019
 */

#ifndef QUARTO_JEU_H
#define QUARTO_JEU_H


#include <vector>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Grille.h"
#include "IA.h"

class Jeu {
private:

    /**
     * @brief grille de jeu
     */
    Grille * g{};

    /**
     * @brief nombre detour écoulé
     */
    unsigned int tour{};

    /**
     * @brief nom J1 et J2
     */
    std::string J1, J2;

    /**
     * @brief tableau des pions disponibles
     */
    Pion ** tabPion{};

    /**
     * @brief instance de l'IA
     */
    IA * ia;

    /**
     * @brief Motif de victoire
     */
    Motif _motif = NONE;

public:

    /**
     * @brief constructeur de la classe Jeu
     */
    Jeu();

    /**
     * @brief Initialise tout les attribut pour que la partie puisse être joué
     */
    void init();

    /**
     * Affichage la fenêtre de choix des pièces / des règles
     * @param [in] pvp : si la partie est pvp (true) ou non
     */
    void choixPieces(bool pvp);

    /**
     * @brief selection le pion en fonction de la position de la sourie lors du clique
     * @param [in] mousseX coordonnées X de la sourie
     * @param [in] mousseY coordonnées Y de la sourie
     * @param [in] og tableau où les texture des pion sont représenter
     * @return l'indice du pion qui à été cliqué
     */
    int selectPion(int mousseX, int mousseY, std::vector<sf::RectangleShape> & og);

    /**
     * @brief selection la case de la grille en fonction de la position de la sourie lors du clique
     * @param [in] mousseX coordonnées X de la sourie
     * @param [in] mousseY coordonnées Y de la sourie
     * @param [in, out] x coordonnées X de la case
     * @param [in, out] y coordonnées Y de la case
     */
    void selectCaseGrille(int mousseX, int mousseY, int & x, int & y);

    /**
     * @brief affiche le menu du jeu
     */
    void menu();

    /**
     * @brief affiche le résultat du jeu
     * @param [in] gagnant nom du gagant ou "match nul" si il n'y a aucun vainqueur
     */
    void resultat(const std::string& gagnant);

    /**
     * @brief partie Joueur contre Joueur
     */
    void pvp();

    /**
     * @brief partie Jour-eur contre IA avec l'algorithme ALPHA-BETA
     */
    void IA_alpha_beta();
};


#endif //QUARTO_JEU_H
