#include <iostream>
#include "Pion.h"

Pion::Pion() {
    this->couleur = false;
    this->forme = false;
    this->taille = false;
    this->trou = false;
    this->lien_image = "";
}

Pion::Pion(bool f, bool ta, bool c, bool tr, std::string str) {
    this->couleur = f;
    this->forme = ta;
    this->taille = c;
    this->trou = tr;
    this->lien_image = str;
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
    std::cout<<lien_image<<std::endl;
}

const std::string &Pion::getLien_image() const {
    return lien_image;
}
