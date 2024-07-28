#ifndef ENCHANTMENT_H
#define ENCHANTMENT_H

#include "decorator.h"
#include <string>
using namespace std;

class Enchantment : public Decorator {
    const string CARDTYPE = "enchantment";
    //int action = -1;
    //int activatedCost = -1;
    int newDefense = -10;
    public:
        Enchantment(MinionComponent *n, string cardName);
        ~Enchantment() override;
        int getAttack() const override;
        int getDefense() const override;
        void setAttack(int) override;
        void setDefense(int) override;
        int getAction() const override;
        void setAction(int) override;
        string getMCardDesc() const override {
            return next->getMCardDesc();
        }
        string getMCardName() const override {
            return next->getMCardName();
        }
        int getMCost() const override {
            return next->getMCost();
        }
        void apply(Player* active, Player* other) override;
        string getCardType() const override;
        char cardAt(int x, int y) const override;
        Minion * getMinion() override;
        int getActivateCost() const override;

        ActivatedAbility *getActivatedAbility() const override;
        void setNext(MinionComponent* next);
        void apply_target (Player* active,  Player* other, Card *&c)override;

};

#endif
