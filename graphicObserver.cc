#include "graphicObserver.h"
#include <iostream>
using namespace std;

GraphicObserver::GraphicObserver(Board *b) : b{b} {
    b->attach(this);
    xw = new Xwindow(1100, 600);;
}

GraphicObserver::~GraphicObserver() {
    b->detach(this); 
    delete xw;
}

void GraphicObserver::notify() {
    xw->drawString(50, 20, "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------");

    for (int window_i = 30, i = 0; i < 11; window_i+=10, ++i) {
        xw->drawString(50, window_i, "|");
        
        for (int window_j = 56, j = 0; j < 33; window_j+=6, ++j) {
            if (b->getPlayer1()->getRitualPlayed() != nullptr) {
                xw->drawString(window_j, window_i, std::string(1,b->getPlayer1()->getRitualPlayed()->cardAt(i, j)));
            } else {
                xw->drawString(window_j, window_i, std::string(1, CARD_TEMPLATE_BORDER[i][j]));
            }
        }
        
        for (int window_j = 254, j = 0; j < 33; window_j+=6, ++j) {
            xw->drawString(window_j, window_i, std::string(1, CARD_TEMPLATE_EMPTY[i][j]));
        }
        
        for (int window_j = 452, j = 0; j < 33; window_j+=6, ++j) {
            xw->drawString(window_j, window_i, std::string(1, b->getPlayer1()->card_at(1,i,j)));
        }
        
        for (int window_j = 650, j = 0; j < 33; window_j+=6, ++j) {
            xw->drawString(window_j, window_i, std::string(1, CARD_TEMPLATE_EMPTY[i][j]));
        }
        
        for (int window_j = 848, j = 0; j < 33; window_j+=6, ++j) { //   ADD GRAVEYARD
            if (b->getPlayer1()->getGraveyard().size() > 0) {
                xw->drawString(window_j, window_i, std::string(1,b->getPlayer1()->getGraveyard().back()->cardAt(i, j)));
            } else {
                xw->drawString(window_j, window_i, std::string(1, CARD_TEMPLATE_BORDER[i][j]));
            }
        }
        
        xw->drawString(1046, window_i, "|");
    }


    for (int window_i = 140, i = 0; i < 11; window_i+=10, ++i) {
        xw->drawString(50, window_i, "|");
        for (long unsigned int k = 0; k < 5; ++k) {
            for (int window_j = 56 + (k*198), j = 0; j < 33; window_j+=6, ++j) {
                if (b->getPlayer1()->getMinionsPlayed().size() > k) {
                    xw->drawString(window_j, window_i, std::string(1, b->getPlayer1()->getMinionsPlayed()[k]->cardAtMinion(i, j)));
                } else {
                    xw->drawString(window_j, window_i, std::string(1, CARD_TEMPLATE_BORDER[i][j]));
                }
            }
        }
        xw->drawString(1046, window_i, "|");
    }

    for (long unsigned int i = 0, window_i = 250; i < CENTRE_GRAPHIC.size(); ++i, window_i+= 10) {
        for (long unsigned int j = 0, window_j = 50; j < CENTRE_GRAPHIC[i].size(); ++j, window_j+=6) {
            xw->drawString(window_j, window_i, std::string(1, CENTRE_GRAPHIC[i][j]));
        }
    }

    for (int window_i = 350, i = 0; i < 11; window_i+=10, ++i) {
        xw->drawString(50, window_i, "|");
        for (long unsigned int k = 0; k < 5; ++k) {
            for (int window_j = 56 + (k*198), j = 0; j < 33; window_j+=6, ++j) {
                if (b->getPlayer2()->getMinionsPlayed().size() > k) {
                    xw->drawString(window_j, window_i, std::string(1, b->getPlayer2()->getMinionsPlayed()[k]->cardAtMinion(i, j)));
                } else {
                    xw->drawString(window_j, window_i, std::string(1, CARD_TEMPLATE_BORDER[i][j]));
                }
            }
        }
        xw->drawString(1046, window_i, "|");
    }

    for (int window_i = 460, i = 0; i < 11; window_i+=10, ++i) {
        xw->drawString(50, window_i, "|");
        for (int window_j = 56, j = 0; j < 33; window_j+=6, ++j) {
            if (b->getPlayer2()->getRitualPlayed() != nullptr) {
                xw->drawString(window_j, window_i, std::string(1,b->getPlayer2()->getRitualPlayed()->cardAt(i, j)));
            } else {
                xw->drawString(window_j, window_i, std::string(1, CARD_TEMPLATE_BORDER[i][j]));
            }
        }
        for (int window_j = 254, j = 0; j < 33; window_j+=6, ++j) {
            xw->drawString(window_j, window_i, std::string(1, CARD_TEMPLATE_EMPTY[i][j]));
        }
        
        for (int window_j = 452, j = 0; j < 33; window_j+=6, ++j) {
            xw->drawString(window_j, window_i, std::string(1, b->getPlayer2()->card_at(1,i,j)));
        }
        
        for (int window_j = 650, j = 0; j < 33; window_j+=6, ++j) {
            xw->drawString(window_j, window_i, std::string(1, CARD_TEMPLATE_EMPTY[i][j]));
        }
        
        for (int window_j = 848, j = 0; j < 33; window_j+=6, ++j) { //   ADD GRAVEYARD
            if (b->getPlayer2()->getGraveyard().size() > 0) {
                xw->drawString(window_j, window_i, std::string(1,b->getPlayer2()->getGraveyard().back()->cardAt(i, j)));
            } else {
                xw->drawString(window_j, window_i, std::string(1, CARD_TEMPLATE_BORDER[i][j]));
            }
        }
        
        xw->drawString(1046, window_i, "|");
    }

    xw->drawString(50, 570, "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------"); 
}
