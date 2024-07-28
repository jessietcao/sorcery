#ifndef RITUAL_H
#define RITUAL_H

#include "card.h"
#include <string>

class Ritual : public Card {
    
    int activation_cost, no_of_charges;
    const string CARDTYPE = "ritual";

    public:
        Ritual (string cardName);
        ~Ritual() override;
        char cardAt(int x, int y) const override;
        bool isEnoughCharges();
        void apply(Player* active, Player* other) override;
        void apply_target (Player* active,  Player* affected, Card* &target) override;
        string getCardType() const override;
        int getCardCost() override; 
        void setCharge(int charge);
        void addCharges(int add);

};       

#endif
