//
// Created by Nathan ARMANET on 2019-03-11.
//

#include "IA.h"

void IA::remplirArbre(Grille g, int dept, int deptFin, std::vector<Pion> &tabPion, Pion * pionDepart = nullptr) {
    this->grid = g;
    this->children.clear();

    if (!this->grid.full() && dept < deptFin) {
        Grille tmp = g;
        IA * child;

        for (unsigned int i = 0; i < this->grid.getDimX(); ++i) {
            for (unsigned int j = 0; j < this->grid.getDimY(); ++j) {
                if (tmp.getCase(i, j).getPion() == nullptr) {
                    if (dept == 0 && pionDepart != nullptr) {
                        tmp.getCase(i, j).setPion(pionDepart);
                        child = new IA();
                        child->ind_x = i;
                        child->ind_y = j;
                        child->pion = *pionDepart;
                        for (int k = 0; k < tabPion.size(); ++k) {
                            if (tabPion[k] == pionDepart) {
                                tabPion.erase(tabPion.begin()+k);
                                child->remplirArbre(tmp, dept+1, deptFin, tabPion);
                                tabPion.insert(tabPion.begin()+k,child->pion);
                            }
                        }
                    } else {
                        for (int k = 0; k < tabPion.size(); ++k) {
                            tmp.getCase(i, j).setPion(&tabPion[k]);
                            child = new IA();
                            child->ind_x = i;
                            child->ind_y = j;
                            child->pion = tabPion[k];
                            tabPion.erase(tabPion.begin()+k);
                            child->remplirArbre(tmp, dept+1, deptFin, tabPion);
                            tabPion.insert(tabPion.begin()+k,child->pion);
                        }
                    }
                }
            }
        }
    }
}

int IA::alphaBeta(unsigned int &x, unsigned int &y, Pion & pion, int alpha, int beta, unsigned int tour,
                  bool maximizingPlayer) {

    std::string joueur;
    int value, bestValue;

    if (this->grid.win(joueur)) {
        /*
         * Cas ou un joueur a gagné un apartie
         */
        x = this->ind_x;
        y = this->ind_y;
        pion = this->pion;

        bestValue = (tour%2 == 0) ? 40 : -40;

    }else if (this->children.empty()) {
        /*
         * Cas où on est sur une feuille
         */
        x = this->ind_x;
        y = this->ind_y;
        pion = this->pion;

        bestValue = this->grid.heuristicValue();

    } else if (maximizingPlayer) {
        bestValue = std::numeric_limits<int>::min();
        for(auto child : children) {
            value = child.alphaBeta(x, y, pion, alpha, beta, tour+1, !maximizingPlayer);
            bestValue = std::max(bestValue, value);
            alpha = std::max(alpha, bestValue);
            if (alpha >= beta) break;
        }
    }else {
        bestValue = std::numeric_limits<int>::max();
        for(auto child : children) {
            value = child.alphaBeta(x, y, pion, alpha, beta, tour+1, !maximizingPlayer);
            bestValue = std::min(bestValue, value);
            beta = std::min(beta, bestValue);
            if (alpha >= beta) break;
        }
    }

    this->value = bestValue;

    return this->value;
}
