#ifndef MINIONCOMPONENT_H
#define MINIONCOMPONENT_H

#include "card.h"
#include "ascii_graphics.h"
#include <string>


using namespace std;

class ActivatedAbility;
class Minion;

class MinionComponent: public Card {
       //bool activatedAbilityON = true;
       //all enchantment cards only have triggered abilities right now, so only implement activatedabilityON when
       //when decide to have extra enchantment cards
    public:
        MinionComponent(string cardName);
        MinionComponent(const MinionComponent& other) : Card(other) {
        // Copy any MinionComponent-specific members here
        }
        virtual ~MinionComponent() = 0;
        virtual int getAttack() const = 0;
        virtual int getDefense() const = 0;
        virtual void setAttack(int attack) = 0;
        virtual void setDefense(int defense) = 0;
        virtual int getAction() const = 0;
        virtual void setAction(int) = 0;
        virtual MinionComponent* getNext() = 0;
        virtual void setNext(MinionComponent*) = 0;
        virtual Minion * getMinion() = 0;
        virtual int getActivateCost() const = 0;
        virtual void useActivatedAbility(Player *active, Player *other);
        virtual void useActivatedAbility_target(Player *active, Player *other, MinionComponent *mc);
        virtual ActivatedAbility *getActivatedAbility() const = 0;
        char cardAt(int x, int y) const override;
        virtual string getMCardDesc() const = 0;
        virtual string getMCardName() const = 0;
        virtual int getMCost() const = 0;
        char cardAtMinion(int x, int y) const;
};

#endif
