/**
 * @file Pion.h
 * @author ARMANET Nathan, NAAJI Dorian
 * @version 1.0
 * @date 10/04/2019
 */

#ifndef MORPION_CASE_H
#define MORPION_CASE_H


#include <string>
#include <ostream>

class Pion {
private:

    /**
     * @brief forme du pion (rond ou carré)
     */
    bool forme;

    /**
     * @brief taille du pion (grand ou petit)
     */
    bool taille;

    /**
     * @brief couleur du pion (bleu ou rouge)
     */
    bool couleur;

    /**
     * @brief est-ce que le pion est plein ou troué
     */
    bool trou;

    /**
     * @brief lien vers l'image du pion
     */
    std::string lien_image;

public:

    /**
     * @brief constructeur par défaut de la classe
     */
    Pion();

    /**
     * @brief constructeur de la classe
     * @param [in] f forme du pion
     * @param [in] ta taille du pion
     * @param [in] c couleur du pion
     * @param [in] tr si le pion est troué ou non
     * @param [in] str lien vers l'image du pion
     */
    Pion(bool f, bool ta, bool c, bool tr, std::string str);

    /**
     * @brief getter de l'attribut forme
     * @return la forme du pion
     */
    bool getForme() const;

    /**
     * @brief getter de l'attribut taille
     * @return la taille du pion
     */
    bool getTaille() const;

    /**
     * @brief getter de l'attribut couleur
     * @return la couleur du pion
     */
    bool getCouleur() const;

    /**
     * @brief getter de l'attribut trou
     * @return si le pion est troué ou plein
     */
    bool getTrou() const;

    /**
     * @brief getter de l'attribut lien_image
     * @return le lien vers l'image du pion
     */
    const std::string & getLien_image() const;

    /**
     * @brief lis les valeurs du pion
     * @return les valeurs du pion
     */
    std::string toString();

    /**
     * @brief regarde si 2 pions ont au moins 1 attribut en commun
     * @param [in] pion pion à comparer
     * @return vrai si le pion courant (this) est égal au pion comapré (en paramètre)
     */
    bool equals(Pion * pion);

    /**
     * @brief regarde si 2 pions ont tous les attribut similaire
     * @param [in] pion pion à comparer
     * @return si les 2 pions ont tous les attribut similaire
     */
    bool operator == (Pion * pion);
};


#endif //MORPION_CASE_H
