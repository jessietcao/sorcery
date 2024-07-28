#include "textObserver.h"
#include "ascii_graphics.h"
#include <iostream>
using namespace std;


TextObserver::TextObserver(Board *b) : b{b} {
    b->attach(this);
}

TextObserver::~TextObserver() {b->detach(this);}

void TextObserver::notify() {
    std::cout << "--------------------------------------------------------";
    std::cout << "-----------------------------------------------------------------";
    std::cout << "----------------------------------------------" << endl;
    

    for (int i = 0; i < 11; ++i) {
        std::cout << "|";
        for (int j = 0; j < 33; ++j) {
            if (b->getPlayer1()->getRitualPlayed() != nullptr) {
                std::cout << b->getPlayer1()->getRitualPlayed()->cardAt(i, j);
            } else {
                std::cout << CARD_TEMPLATE_BORDER[i][j];
            }
        }
        for (int j = 0; j < 33; ++j) {
            std::cout << CARD_TEMPLATE_EMPTY[i][j];
        }
        for (int j = 0; j < 33; ++j) {
            std::cout << b->getPlayer1()->card_at(1,i,j);
        }
        for (int j = 0; j < 33; ++j) {
            std::cout << CARD_TEMPLATE_EMPTY[i][j];
        }
        for (int j = 0; j < 33; ++j) { //   ADD GRAVEYARD
            if (b->getPlayer1()->getGraveyard().size() > 0) {
                std::cout << b->getPlayer1()->getGraveyard().back()->cardAt(i, j);
            } else {
                std::cout << CARD_TEMPLATE_BORDER[i][j];
            }
        }
        std::cout << "|" << endl;
    }

    for (int i = 0; i < 11; ++i) {
        std::cout << "|";
        for (long unsigned int k = 0; k < 5; ++k) {
            for (int j = 0; j < 33; ++j) {
                if (b->getPlayer1()->getMinionsPlayed().size() > k) {
                    std::cout << b->getPlayer1()->getMinionsPlayed()[k]->cardAtMinion(i, j);
                } else {
                    std::cout << CARD_TEMPLATE_BORDER[i][j];
                }
            }
        }
        std::cout << "|" << endl;
    }

    for (long unsigned int i = 0; i < CENTRE_GRAPHIC.size(); ++i) {
        for (long unsigned int j = 0; j < CENTRE_GRAPHIC[i].size(); ++j) {
            std::cout << CENTRE_GRAPHIC[i][j];
        }
        std::cout << endl;
    }

    for (int i = 0; i < 11; ++i) {
        std::cout << "|";
        for (long unsigned int k = 0; k < 5; ++k) {
            for (int j = 0; j < 33; ++j) {
                if (b->getPlayer2()->getMinionsPlayed().size() > k) {
                    std::cout << b->getPlayer2()->getMinionsPlayed()[k]->cardAtMinion(i, j);
                } else {
                    std::cout << CARD_TEMPLATE_BORDER[i][j];
                }
            }
        }
        std::cout << "|" << endl;
    }

    for (int i = 0; i < 11; ++i) {
        std::cout << "|";
        for (int j = 0; j < 33; ++j) {
            if (b->getPlayer2()->getRitualPlayed() != nullptr) {
                std::cout << b->getPlayer2()->getRitualPlayed()->cardAt(i, j);
            } else {
                std::cout << CARD_TEMPLATE_BORDER[i][j];
            }
        }
        for (int j = 0; j < 33; ++j) {
            std::cout << CARD_TEMPLATE_EMPTY[i][j];
        }
        for (int j = 0; j < 33; ++j) {
            std::cout << b->getPlayer2()->card_at(2,i,j);
        }
        for (int j = 0; j < 33; ++j) {
            std::cout << CARD_TEMPLATE_EMPTY[i][j];
        }
        for (int j = 0; j < 33; ++j) {
            if (b->getPlayer2()->getGraveyard().size() > 0) {
                std::cout << b->getPlayer2()->getGraveyard().back()->cardAt(i, j);
            } else {
                std::cout << CARD_TEMPLATE_BORDER[i][j];
            }
        }
        std::cout << "|" << endl;
    }

    std::cout << "--------------------------------------------------------";
    std::cout << "-----------------------------------------------------------------";
    std::cout << "----------------------------------------------" << endl;

}

