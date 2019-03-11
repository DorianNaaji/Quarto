

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

    bool equals(Pion *pion);

    bool operator !=(Pion * pion);

    void read();

    const std::string &getLien_image() const;
};


#endif //MORPION_CASE_H
