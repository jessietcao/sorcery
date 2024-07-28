#ifndef MINION_H
#define MINION_H

#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <string>

#include "minionComponent.h"
#include "activatedAbility.h"

class Minion: public MinionComponent {
    ActivatedAbility *aa;
    int attack, defense, action;
    const string CARDTYPE = "minion";


    public:
    //Minion(string cardName, int life, int attack, int defense);
    Minion(string cardName);
    Minion(const Minion &m); //copy constructor
    virtual ~Minion() override; 

    //override card class
    //note minion does not have a cardAt, minionComponent takes care of that
    void apply(Player* active, Player* other) override;

    string getCardType() const override;
    int getCardCost() override; 

    //override the minion component
    int getAttack() const override;
    int getDefense() const override;
    void setAttack(int attack) override;
    void setDefense(int defense) override;

    int getAction() const override;
    void setAction(int) override; //<- At the start of the turn, all minions gain 1 action point, after minion is used, loses one action point

    MinionComponent* getNext() override;
    Minion* getMinion() override;
    int getActivateCost() const override;

    ActivatedAbility *getActivatedAbility() const override;
    void apply_target (Player* active,  Player* other, Card *&card) override;

    string getMCardDesc() const override {
            return cardDesc;
    }
    string getMCardName() const override {
            return cardName;
    }
    int getMCost() const override {
            return cost;
    }
    virtual void setNext(MinionComponent*) override {

    }

};

#endif
