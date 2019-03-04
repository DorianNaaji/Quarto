#include <iostream>
#include "Pion.h"

Pion::Pion() {
    this->couleur = false;
    this->forme = false;
    this->taille = false;
    this->trou = false;
}

Pion::Pion(bool f, bool ta, bool c, bool tr) {
    this->couleur = f;
    this->forme = ta;
    this->taille = c;
    this->trou = tr;
}

bool Pion::operator==(const Pion &rhs) const {
    return this->couleur == rhs.couleur
            && this->forme == rhs.forme
            && this->taille == rhs.taille
            && this->trou == rhs.trou;
}

bool Pion::operator!=(const Pion &rhs) const {
    return this->couleur != rhs.couleur
           || this->forme != rhs.forme
           || this->taille != rhs.taille
           || this->trou != rhs.trou;
}

void Pion::read() {
    std::cout<<couleur<<" | "<<forme<<" | "<<taille<<" | "<<trou<<std::endl;
}
