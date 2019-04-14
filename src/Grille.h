/**
 * @file Grille.h
 * @author ARMANET Nathan, NAAJI Dorian
 * @version 1.0
 * @date 10/04/2019
 */

#ifndef MORPION_GRILLE_H
#define MORPION_GRILLE_H

#include <vector>
#include "Case.h"
#include "Motif.h"

class Grille {
private:

    /**
     * @brief array in CAse
     */
    Case * grid;

    /**
     * @brief grid's heigth
     */
    unsigned int dimX;

    /**
     * @brief grid's length
     */
    unsigned int dimY;

public:

    /**
     * @brief Grille's constructor
     */
    Grille();

    /**
     * @brief get the grid's heigth
     * @return grid's heigth
     */
    unsigned int getDimX() const;

    /**
     * @brief get the grid's length
     * @return grid's length
     */
    unsigned int getDimY() const;

    /**
     * @brief get a case
     * @param [in] x Case's X coordinate
     * @param [in] y case's Y coordinate
     * @return the Case
     */
    Case & getCase(unsigned int x, unsigned int y);

    /**
     * @brief Set les case with a Pion
     * @param [in] x Case's X coordinate
     * @param [in] y case's Y coordinate
     * @param [in] p Pion to put in the Case
     */
    void setCase(unsigned int x, unsigned int y, Pion * p);

    /**
     * @return bool : gagné (true) ou non (false)
     */
    bool win();

    /**
     * @brief Checks if the grid is full
     * @return true if the gris is full. False otherwise
     */
    bool full();

    /**
     * @brief Calculate a heurestical value of the grid
     * @param [in] indice line index
     * @return heurestical value of the grid
     */
    int heuristicValueHorizontal(unsigned int indice);

    /**
     * @brief Calculate a heurestical value of the grid
     * @param [in] indice column index
     * @return heurestical value of the grid
     */
    int heuristicValueVertical(unsigned int indice);

    /**
     * @brief Calculate a heurestical value of the grid's diagonal
     * @return heurestical value of the grid
     */
    int heuristicValueDiagonal();

    /**
     * @brief Calculate a heurestical value of the grid's second diagonal
     * @return heurestical value of the grid
     */
    int heuristicValueAntiDiagonal();

    /**
     * @brief Calculate a heurestical value of the grid
     * @return heurestical value of the grid
     */
    int heuristicValue();

    /**
     * Calls the appropriate win condition checking function according to a given pattern
     * @param motif : the tetris pattern
     * @return true if the pattern is made (win). False otherwise
     */
    bool win(Motif motif);

    /**
     *
     * @param pions A 4-sized vector containing pions
     * @return true if the "pions" have one common characteristic. False otherwise
     */
    bool haveOneCommonCharacteristic(std::vector<Pion*> pions);

    /**
     * @brief checks if the player made the stick tetris pattern
     * @return true if won. False otherwise
     */
    bool batonWin();

    /**
     * @brief Checks if the player made the "L" pattern
     * To checks if the game is won, we just check the cells around an (i,j) given cell to see if a L is made.
     * @return true if the player won. False otherwise
     */
    bool l_normalWin();

    /**
     * @brief Checks if the player made a reverse "L" pattern
     * @return true if won. False otherwise
     */
    bool l_inverseWin();

    /**
     * @brief Checks if the block tetris pattern is made in the grid
     * To perform a square pattern, the coordinates are : square : (i,j), (i+1,j), (i+1, j+1), (i, j+1)
     * so the offsets are 0, 0, 1, 0, 1, 1, 0, 1
     * @return true if so. False otherwise
     */
    bool blocWin();

    /**
     * @brief Checks if the "__--" pattern is made
     * @return true if won. False otherwise
     */
    bool biais_normalWin();

    /**
     * @brief Checks if the "T" pattern is made
     * @return true if won. False otherwise
     */
    bool tWin();

    /**
     * @brief Checks if the "--__" pattern is made
     * @return true if won. False otherwise
     */
    bool biais_inverseWin();

    /**
     * @brief Checks if the player won horizontally
     * @return true if won. False otherwise
     */
    bool horizontalOrVerticalWin();

    /**
     * Checks if the player won with the diagonals.
     * @return true if won. False otherwise
     */
    bool diagonalOrReverseDiagonalWin();

    /**
     * @param [in] coordinates a vector of pairs of ints.
     * @return true if 4 given pions (according to their coordinates) have a common characteristics. False otherwise
     */
    bool checkPionsWith4Coordinates(const std::vector<std::pair<int, int>>& coordinates);

    /**
     * @param [in] offsets array of 8 offsets applicated to 8 coordinates
     * @return true if the pattern is made. False otherwise
     */
    bool winMotifTetris(int offsets[8]);

    /**
     * @brief says if the coordinates are out of the grid or not
     * @param coordinates a vector of pairs of ints.
     * @return true if some of the coordinates are out of the grid. false otherwise
     */
    bool outOfGrid(const std::vector<std::pair<int, int>>& coordinates);
};


#endif //MORPION_GRILLE_H
