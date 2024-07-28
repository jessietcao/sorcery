#include "spell.h"
#include "minion.h"
#include "ritual.h"
#include <iostream>
#include "ascii_graphics.h"

Spell::Spell (std::string cardName) : Card {cardName} {

    if (cardName == "Banish") {
        cost = 2;
        cardDesc = "Destroy target minion or ritual";
    }

    else if (cardName == "Unsummon") {
        cost = 1;
        cardDesc = "Return target minion to its owner's hand";
    }

    else if (cardName == "Recharge"){
        cost = 1;
        cardDesc  = "Your ritual gains 3 charges";
    }

    else if (cardName == "Disenchant") {
        cost = 1;
        cardDesc = "Destroy the top enchantment on target minion";
    }

    else if (cardName == "Raise Dead") {
        cost = 1;
        cardDesc = "Resurrect the top minion in your graveyard and set its. defence to 1";
    }

    else if (cardName == "Blizzard") {
        cost = 3 ;
        cardDesc = "Deal 2 damage to all minions";
    }

}

void Spell::apply(Player* active, Player* other) {

    if (cardName == "Recharge") {
        // this ritual gains 3 charges
        Ritual* ritual = active->getRitualPlayed();
        if (ritual) {
            ritual->addCharges(3);
        }

    }

    else if (cardName == "Raise Dead") {

        if (!active->getGraveyard().empty()){
            Minion* resurrected_minion = active->getGraveyard().back();
            active->removetopgraveyard();

            resurrected_minion->setDefense(1);
            active->add_minion_to_hand(resurrected_minion);
        }
    }

    else if (cardName == "Blizzard") {
        for (auto minion : active->getMinionsPlayed()) {
            minion ->setDefense(minion->getDefense() - 2);
        }

        for (auto minion : other->getMinionsPlayed() ) {
            minion -> setDefense (minion->getDefense() - 2);
        }
    }
}


void Spell::apply_target (Player* active,  Player* affected, Card* &target) {

    if (cardName == "Banish" ) {
        /// double check later
        
        if (target->getCardType() == "ritual") {
            affected->deleteRitualPlayed();
        } else  {
            /*
            Minion* converted_minion = static_cast <Minion*> (target);
            affected->addMinionToGraveyard(converted_minion);

            //Problem converting;
            MinionComponent *converted_mc = dynamic_cast<MinionComponent*>(target);
            Minion *newMinion = new Minion(*converted_minion->getMinion());
            delete converted_mc;
            target = newMinion;*/

            //Jessie's edit ------------------------------------------------
            


            MinionComponent* converted_minion = static_cast <MinionComponent*> (target);
            affected->addMinionComponentToGraveyard(converted_minion);
        }   

    } else if (cardName == "Disenchant") {
        MinionComponent *converted_minion = static_cast<MinionComponent*>(target);
        MinionComponent *next = converted_minion->getNext();

        if (next) {
            converted_minion->setNext(nullptr);
            delete converted_minion;
            target = next;
        }


    } else if (cardName == "Unsummon") {
        Minion *converted_minion = dynamic_cast<Minion*>(target);
        converted_minion->setAction(0);
        affected->add_minion_to_hand(converted_minion);
        affected->removeMinion__played(converted_minion);            
    }
}

char Spell::cardAt(int x, int y) const { //be careful when used from other class
                                //x and y start from 0, are relatvie to the card itself not the board
    return display_spell(cardName, cost, cardDesc)[x][y];
}



string Spell::getCardType() const{
    return CARDTYPE;
}

int Spell::getCardCost() {
    return cost;
}

Spell::~Spell(){

}
