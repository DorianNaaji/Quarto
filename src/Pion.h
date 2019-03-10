

#ifndef MORPION_CASE_H
#define MORPION_CASE_H


#include <string>

class Pion {
private:

    bool forme;
    bool taille;
    bool couleur;
    bool trou;

    std::string lien_image;

public:

    Pion();

    Pion(bool f, bool ta, bool c, bool tr, std::string str);

    bool operator ==(const Pion &rhs) const;

    bool operator !=(const Pion &rhs) const;

    void read();

    const std::string &getLien_image() const;

    bool equals(Pion *pion);
};


#endif //MORPION_CASE_H
