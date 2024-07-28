#ifndef CARD_H
#define CARD_H

#include <string>

using namespace std;

class Player;

class Card {
    protected:
        string cardName;
        string cardDesc = "";
        int cost;
        const int CWIDTH = 33;
        const int CHEIGHT = 11;
    public: 
        Card(string cardName);
        virtual ~Card() = 0;
        virtual char cardAt(int, int) const = 0;
        virtual void apply(Player* active, Player* opposing) = 0;
        virtual void apply_target (Player* active,  Player* affected, Card* &target) = 0;
        virtual string getCardType() const = 0;
        virtual int getCardCost();
        string getCardName();
};

#endif
