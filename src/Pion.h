

#ifndef MORPION_CASE_H
#define MORPION_CASE_H


#include <string>

class Pion {
private:

    bool forme;
    bool taille;
    bool couleur;
    bool trou;



public:

    Pion();

    Pion(bool f, bool ta, bool c, bool tr);

    bool operator ==(const Pion &rhs) const;

    bool operator !=(const Pion &rhs) const;

    void read();
};


#endif //MORPION_CASE_H
