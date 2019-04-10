

#ifndef MORPION_CASE_H
#define MORPION_CASE_H


#include <string>
#include <ostream>

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

    void read();

    const std::string & getLien_image() const;

    std::string toString();

    bool equals(Pion * pion);

    bool operator == (Pion * pion);

    bool getForme() const;

    bool getTaille() const;

    bool getCouleur() const;

    bool getTrou() const;
};


#endif //MORPION_CASE_H
