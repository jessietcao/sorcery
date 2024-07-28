#ifndef SPELL_H
#define SPELL_H

#include "card.h"
#include <string>

class Spell : public Card {

    const string CARDTYPE = "spell";

    public:
        Spell(string cardName);
        ~Spell() noexcept override;
        char cardAt(int x, int y) const override;
        void apply(Player* active, Player* other) override;
        void apply_target (Player* active,  Player* affected, Card* &target) override;
        string getCardType() const override;
        int getCardCost() override; 
};


#endif
