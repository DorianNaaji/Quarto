/**
 * @file Case.h
 * @author ARMANET Nathan, NAAJI Dorian
 * @version 1.0
 * @date 10/04/2019
 */

#ifndef QUARTO_CASE_H
#define QUARTO_CASE_H


#include "Pion.h"

class Case {
private:

    /**
     * @brief Pion de la case
     */
    Pion * pion;

public:

    /**
     * @brief Constructeur par défaut le la classe
     */
    Case();

    /**
     * @brief getter de pion
     * @return le pion de la case
     */
    Pion *getPion() const;

    /**
     * @brief setter de pion
     * @param [in] pion pion a mettre dans la case
     */
    void setPion(Pion *pion);

};


#endif //QUARTO_CASE_H
