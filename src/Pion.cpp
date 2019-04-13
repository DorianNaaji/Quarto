#include <utility>

#include <iostream>
#include "Pion.h"
#include "assert.h"

Pion::Pion() {
    this->couleur = false;
    this->forme = false;
    this->taille = false;
    this->trou = false;
    this->lien_image = "";
}

Pion::Pion(bool taille, bool forme, bool couleur, bool trou, std::string str) {
    this->taille = taille;
    this->forme = forme;
    this->couleur = couleur;
    this->trou = trou;
    this->lien_image = std::move(str);
}

bool Pion::getForme() const
{
    assert(this);
    return this->forme;
}

bool Pion::getTaille() const
{
    assert(this);
    return this->taille;
}

bool Pion::getCouleur() const
{
    assert(this);
    return this->couleur;
}

bool Pion::getTrou() const
{
    assert(this);
    return this->trou;
}

const std::string &Pion::getLien_image() const {
    assert(this);
    return lien_image;
}

bool Pion::equals(Pion * pion)
{
    assert(this);
    if(pion != nullptr)
    {
        // bool a = this->couleur == pion->couleur;
        // bool b = this->forme == pion->forme;
        // bool c = this->taille == pion->taille;
        // bool d = this->trou == pion->trou;

        return( (this->couleur == pion->couleur)
                || (this->forme == pion->forme)
                || (this->taille == pion->taille)
                || (this->trou == pion->trou) );
    }
    return false;
}

bool Pion::operator==(Pion *pion) {
    assert(this);
    if(pion != nullptr)
    {
        // bool a = this->couleur == pion->couleur;
        // bool b = this->forme == pion->forme;
        // bool c = this->taille == pion->taille;
        // bool d = this->trou == pion->trou;

        return( (this->couleur == pion->couleur)
                && (this->forme == pion->forme)
                && (this->taille == pion->taille)
                && (this->trou == pion->trou) );
    }
    return false;
}

std::string Pion::toString()
{
   std::string res;
   if(this->couleur)
   {
       res += "Bleu, ";
   }
   else
   {
       res += "Rouge, ";
   }

   if(this->forme)
   {
       res += "Carré, ";
   }
   else
   {
       res += "Rond, ";
   }

   if(this->taille)
   {
       res += "Grand, ";
   }
   else
   {
       res += "Petit, ";
   }

   if(this->trou)
   {
       res += "Troué.";
   }
   else
   {
       res += "Non troué.";
   }
   return res;
}
