#include "minion.h"
#include "ascii_graphics.h"

Minion::Minion(string cardName) : MinionComponent{cardName}, aa{nullptr} {
    action = 0;
    if (cardName == "Air Elemental") {
        cost = 0;
        attack = 1;
        defense = 1;
    } else if (cardName == "Earth Elemental") {
        cost = 3;
        attack = 4;
        defense = 4;
    } else if (cardName == "Bone Golem") {
        cost = 2;
        attack = 1;
        defense = 3;
        cardDesc = "Gain +1/+1 whenever a minion leaves play.";
    } else if (cardName == "Fire Elemental") {
        cost = 2;
        attack = 2;
        defense = 2;
        cardDesc = "Whenever an opponent's minion enters play, deal 1 damage to it.";
    } else if (cardName == "Potion Seller") {
        cost = 2;
        attack = 1;
        defense = 3;
        cardDesc = "At the end of your turn, all your minions gain +0/+1.";
    } else if (cardName == "Novice Pyromancer") {
        cost = 1;
        attack = 0;
        defense = 1;
        cardDesc = "Deal 1 damage to target minion";
        aa = new ActivatedAbility{cardName};
    } else if (cardName == "Apprentice Summoner") {
        cost = 1;
        attack = 1;
        defense = 1;
        cardDesc = "Summon a 1/1 air elemental";
        aa = new ActivatedAbility{cardName};
    } else if (cardName == "Master Summoner") {
        cost = 3;
        attack = 2;
        defense = 3;
        cardDesc = "Summon up to three 1/1 air elementals";
        aa = new ActivatedAbility{cardName};
    } 
}

Minion::Minion(const Minion &m): MinionComponent{m.cardName} {
    action = m.action;
    cost = m.cost;
    attack = m.attack;
    defense = m.defense;
    cardDesc = m.cardDesc;
    if (m.aa) {
        aa = new ActivatedAbility{cardName};
    } else {
        aa = nullptr;
    }
    
}


void Minion::apply(Player* active, Player* other) { //Triggered abilities
    std::vector<MinionComponent *> minions = other->getMinionsPlayed();
    if (cardName == "Bone Golem") {
        //attack defense all gain one
        attack += 1;
        defense += 1;
    } else if (cardName == "Fire Elemental") {
        //deal one damage when opponent's minion enters play
        if (minions.size() > 0) {
            minions[minions.size() - 1]->setDefense(minions[minions.size() - 1]->getDefense() - 1);
        }
        
    } else if (cardName == "Potion Seller") {
        //add the end of your turn, all your minions get defense + 1
        for (auto m : minions) {
            m->setDefense(m->getDefense() + 1);
        }
    }  
}

void Minion::apply_target (Player* active,  Player* other, Card *&card) {// cards with activated abilities
    //no apply_target has been used for minion
}

ActivatedAbility* Minion::getActivatedAbility() const{
    return aa;
}


string Minion::getCardType() const{
    return CARDTYPE;
}

int Minion::getCardCost() {
    return cost;
}

int Minion::getAttack() const {return attack;}

int Minion::getDefense () const {return defense;}

void Minion::setAttack(int attack) {
    this->attack = attack;
}
void Minion::setDefense(int defense) {
    this->defense = defense;
}

int Minion::getAction() const {return action; }
void Minion::setAction(int action) {this->action = action;}

int Minion::getActivateCost() const {
    if (!aa) return 0;
    return aa->getActivateCost();
}

Minion::~Minion (){
    delete aa;
}

MinionComponent* Minion::getNext() {
    return nullptr;
}

Minion * Minion::getMinion() {
    return this;
}





