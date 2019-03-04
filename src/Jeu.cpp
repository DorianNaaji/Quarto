//
// Created by Nathan ARMANET on 2019-02-25.
//

#include "Jeu.h"
#include <math.h>
#include <iostream>

Jeu::Jeu() {
    this->g = new Grille;
    this->J1 = "J1";
    this->J2 = "J2";

    Pion * p;
    bool tab[4];
    int k;
    for (int i = 0; i < 16; i++) {
        k = i;
        for (int j = 3; j >=0 ; --j) {
            if (k >= pow(2, j)) {
                tab[j] = true;
                k -= (int)pow(2, j);
            } else {
                tab[j] = false;
            }
        }
        p = new Pion(tab[3], tab[2], tab[1], tab[0]);
        this->tabPion.push_back(*p);
    }
}

void Jeu::readListePion() {
    for (int i = 0; i < 16; ++i) {
        tabPion[i].read();
    }
}
