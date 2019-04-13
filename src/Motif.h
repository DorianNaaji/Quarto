/**
 * @file Motif.h
 * @author ARMANET Nathan, NAAJI Dorian
 * @version 1.0
 * @date 10/04/2019
 */

#ifndef QUARTO_MOTIF_H
#define QUARTO_MOTIF_H

/**
 * @brief liste des motifs posibles
 */
enum Motif
{
    NONE = -1,
    BATON = 0, // ----
    L_NORMAL = 1, // |___
    L_INVERSE = 2, // ___|
    BLOC = 3, // []
    BIAIS_NORMAL = 4, // __--
    T = 5, // -|-
    BIAIS_INVERSE = 6 // --__
};

#endif //QUARTO_MOTIF_H
