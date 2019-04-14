//
// Created by Nathan ARMANET on 2019-02-25.
//

#include "Case.h"

Case::Case() {
    this->pion = nullptr;
}

Pion *Case::getPion() const {
    return pion;
}

void Case::setPion(Pion *p) {
    this->pion = p;
}
