//
// Created by Nathan ARMANET on 2019-03-11.
//

#include <iostream>
#include "IA.h"
#include <limits>

void IA::remplirArbre(Grille g, int dept, int deptFin, Pion ** tabPion, Pion * pionDepart = nullptr) {
    this->grid = g;
    this->children.clear();

    if (!this->grid.full() && dept < deptFin) {
        Grille tmp = g;
        IA * child;

        for (unsigned int i = 0; i < tmp.getDimX(); ++i) {
            for (unsigned int j = 0; j < tmp.getDimY(); ++j) {
                if (tmp.getCase(i, j).getPion() == nullptr) {
                    if (dept == 0 && pionDepart != nullptr) {
                        tmp.getCase(i, j).setPion(pionDepart);
                        child = new IA();
                        child->ind_x = i;
                        child->ind_y = j;
                        for (unsigned int k = 0; k < 16; ++k) {
                            if (tabPion[k]->equals(pionDepart)) {
                                child->ind_Pion = k;
                                tabPion[k] = nullptr;
                                child->remplirArbre(tmp, dept+1, deptFin, tabPion);
                                tabPion[k] = tmp.getCase(i, j).getPion();
                                children.push_back(*child);
                            }
                        }
                    } else {
                        for (unsigned int k = 0; k < 16; ++k) {
                            if (tabPion[k] != nullptr) {
                                tmp.getCase(i, j).setPion(tabPion[k]);
                                child = new IA();
                                child->ind_x = i;
                                child->ind_y = j;
                                child->ind_Pion = k;
                                tabPion[k] = nullptr;
                                child->remplirArbre(tmp, dept+1, deptFin, tabPion);
                                tabPion[k] = tmp.getCase(i, j).getPion();
                                children.push_back(*child);
                            }
                        }
                    }
                    tmp.getCase(i, j).setPion(nullptr);
                }
            }
        }
    }
}

int IA::alphaBeta(int & x, int & y, int alpha, int beta, unsigned int tour,
                  bool maximizingPlayer) {

    int tmp_value, bestValue;

    if (this->grid.win()) {
        /*
         * Cas ou un joueur a gagné une partie
         */
        x = this->ind_x;
        y = this->ind_y;

        bestValue = (tour%2 == 0) ? 40 : -40;

    } else if (this->grid.full()) {
        /*
         * Cas ou il y a match nul
         */
        x = this->ind_x;
        y = this->ind_y;

        bestValue = 0;
    }else if (this->children.empty()) {
        /*
         * Cas où on est sur une feuille
         */
        x = this->ind_x;
        y = this->ind_y;

        bestValue = this->grid.heuristicValue();

    } else {
        int tmp_x, tmp_y;
        if (maximizingPlayer) {
            bestValue = std::numeric_limits<int>::min();
            for(auto child : children) {
                tmp_value = child.alphaBeta(x, y, alpha, beta, tour+1, !maximizingPlayer);
                if (tmp_value > bestValue) {
                    tmp_x = x;
                    tmp_y = y;
                }
                alpha = std::max(alpha, bestValue);
                if (alpha >= beta) break;
            }
        } else {
            bestValue = std::numeric_limits<int>::max();
            for(auto child : children) {
                tmp_value = child.alphaBeta(x, y, alpha, beta, tour+1, !maximizingPlayer);
                if (tmp_value < bestValue) {
                    tmp_x = x;
                    tmp_y = y;
                }
                beta = std::min(beta, bestValue);
                if (alpha >= beta) break;
            }
        }
        x = tmp_x;
        y = tmp_y;
    }

    this->value = bestValue;

    return this->value;
}

int IA::selectPion(int & indPion, int alpha, int beta, unsigned int tour, bool maximizingPlayer) {

    int tmp_value, bestValue;

    if (this->grid.win()) {
        /*
         * Cas ou un joueur a gagné un apartie
         */
        indPion = this->ind_Pion;

        bestValue = (tour%2 == 0) ? 40 : -40;

    } else if (this->grid.full()) {
        /*
         * Cas ou il y a match nul
         */
        indPion = this->ind_Pion;

        bestValue = 0;
    }else if (this->children.empty()) {
        /*
         * Cas où on est sur une feuille
         */
        indPion = this->ind_Pion;
        indPion = this->ind_Pion;

        bestValue = this->grid.heuristicValue();

    } else if (maximizingPlayer) {
        bestValue = std::numeric_limits<int>::min();
        for(auto child : children) {
            tmp_value = child.selectPion(indPion, alpha, beta, tour+1, !maximizingPlayer);
            bestValue = std::max(bestValue, tmp_value);
            alpha = std::max(alpha, bestValue);
            if (alpha >= beta) break;
        }
    }else {
        bestValue = std::numeric_limits<int>::max();
        for(auto child : children) {
            tmp_value = child.selectPion(indPion, alpha, beta, tour+1, !maximizingPlayer);
            bestValue = std::min(bestValue, tmp_value);
            beta = std::min(beta, bestValue);
            if (alpha >= beta) break;
        }
    }

    this->value = bestValue;

    return this->value;
}
