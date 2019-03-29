//
// Created by Nathan ARMANET on 2019-02-25.
//

#ifndef QUARTO_CASE_H
#define QUARTO_CASE_H


#include "Pion.h"

class Case {
private:

    Pion * pion;

public:

    Case();

    Pion *getPion() const;

    void setPion(Pion *pion);

};


#endif //QUARTO_CASE_H
