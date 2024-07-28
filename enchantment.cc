#include "enchantment.h"
#include "ascii_graphics.h"
#include <iostream>
using namespace std;

Enchantment::Enchantment(MinionComponent *p, string cardName): Decorator{p, cardName} {
    if (cardName == "Giant Strength") {
        cost = 1;
    } else if (cardName == "Enrage") {
        cost = 2;
    } else if (cardName == "Haste") {
        cost = 1;
        cardDesc = "Enchanted minion gains +1 action each turn";
    } else if (cardName == "Magic Fatigue") {
        cost = 0;
        cardDesc = "Enchanted minion's activated ability costs 2 more";
    } else if (cardName == "Silence") {
        cost = 1;
        cardDesc = "Enchanted minion cannot use abilities";
    }
    
}


char Enchantment::cardAt(int x, int y) const {
    if (cardName == "Enrage") return display_enchantment_attack_defence(cardName, cost, cardDesc, "*2", "*2")[x][y];

    if (cardName == "Giant Strength") return display_enchantment_attack_defence(cardName, cost, cardDesc, "+2", "+2")[x][y];
    return display_enchantment(cardName, cost, cardDesc)[x][y];
}

string Enchantment::getCardType() const{
    return CARDTYPE;
}

void Enchantment::setAttack(int attack) { //attack only increases in the game, so no need to update the base attack
    return next->setAttack(attack);
}

void Enchantment::setDefense(int defense) {
    if (newDefense != -10) { //if there is a new defense applied to the base defense
        newDefense = defense; //update new defense 
        if(newDefense < next->getDefense()) { //if the newDefense becomes smaller than the base defense
            newDefense = -10; //disable the new defense 
            next->setDefense(defense); //set the base defense to the new reduced value
        }
    } else {
        next->setDefense(defense); //otherwise, directly goes to next
    }
}

int Enchantment::getAttack() const{
    if (cardName == "Giant Strength") {
        return next->getAttack() + 2;
    } else if (cardName == "Enrage") {
        return next->getAttack() * 2;
    }

    return next->getAttack();
}

int Enchantment::getDefense() const {
    if (newDefense == -10){ //if this Enchantment doesn't change defense values, go to the next one
        return next->getDefense();
    }

    return newDefense;
}

int Enchantment::getAction() const {
    return next->getAction(); //default action points of minion
}

void Enchantment::setAction(int a) {
    return next->setAction(a);
}

Minion* Enchantment::getMinion() {
    return next->getMinion();
}

ActivatedAbility* Enchantment::getActivatedAbility() const {
    if (cardName == "Silence") return nullptr; //if cardName is silence, blocks MinionComponent from getting activatedAbility
    return next->getActivatedAbility();
}

void Enchantment::apply(Player* active, Player* other) {// triggered abilities
    if (cardName == "Haste") {
        next->setAction(next->getAction() + 1); //change the default # of action points
        next->apply(active, other); //other triggered abilities form minions
    } else if (cardName == "Silence") {
        //does nothing, blocks further trigger abilities
    } else {
        //otherwise, no triggered abilities granted from echantments, get abilities from the minions
        next->apply(active, other);
    }
    
}

void Enchantment::setNext(MinionComponent* next) {
            this->next = next;
}

void Enchantment::apply_target(Player* active, Player* other, Card *&c ){// attaching enchantment to card, only done once
    //c must be a MinionComponent
    MinionComponent* mc = dynamic_cast<MinionComponent*>(c);
    setNext(mc); //set c pointing the current card, set next as the former card
    c = this;

    if (cardName == "Giant Strength") {
        newDefense = next->getDefense() + 2; //attack can only increase in this game (so far), so no need to implement newAttack
    } else if (cardName == "Enrage") {
        newDefense = next->getDefense() * 2;
    } 
    
}


int Enchantment::getActivateCost() const { //magic fatigue's abilities affects
    if (cardName == "Magic Fatigue") return 2 + next->getActivateCost();
    return next->getActivateCost();
}


Enchantment::~Enchantment() {

}




