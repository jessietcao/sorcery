
#include "card.h"


Card::Card(string cardName): cardName{cardName} {

}

int Card::getCardCost() {
    return cost;
}

string Card::getCardName() {
    return cardName;
}

Card::~Card() {

}
