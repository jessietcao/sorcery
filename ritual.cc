#include "ritual.h"
#include "player.h"

#include "ascii_graphics.h"


Ritual::Ritual (std::string cardName):Card{cardName}{

    if (cardName == "Dark Ritual") {
        cost = 0;
        no_of_charges = 5;
        activation_cost = 1;

        cardDesc = "At the start of your turn, gain 1 magic";
    }  

    else if (cardName == "Aura of Power") {

        cost = 1;
        no_of_charges = 4;
        activation_cost = 1;

        cardDesc = "Whenever a minion enters play under your control,it gains +1/+1";
    }

    else if (cardName == "Standstill") {
        cost = 3;
        no_of_charges = 4;
        activation_cost = 2;

        cardDesc = "Whenever a minion enters play, destroy it";

    }


}



char Ritual::cardAt(int x, int y) const {
  return  display_ritual(cardName, cost,activation_cost,cardDesc, no_of_charges)[x][y];
}


bool Ritual::isEnoughCharges(){
    return no_of_charges >= activation_cost;
}



void Ritual::apply(Player* active, Player* other) {
    
   if (isEnoughCharges()){
        if (cardName == "Dark Ritual"){
             int new_magic = active->getmagic();
             active->setmagic(new_magic + 1);

             no_of_charges = no_of_charges - activation_cost;

         }

         else if (cardName == "Aura of Power"){

          if (!(active->getMinionsPlayed()).empty()) {
          MinionComponent* minion = (active->getMinionsPlayed()).back();
            if (minion != nullptr) {
                minion->setAttack(minion->getAttack() + 1);
                minion->setDefense(minion->getDefense() + 1);

                no_of_charges = no_of_charges - activation_cost;                

            }
        } 

         }

        else if (cardName == "Standstill") {

            if (!(active->getMinionsPlayed()).empty()) {
            Minion* minion = dynamic_cast<Minion*>(active->getMinionsPlayed().back());
            if (minion != nullptr) {
                active->removeMinion__played(dynamic_cast<MinionComponent*>(minion));
                active->addMinionToGraveyard(minion);
                no_of_charges = no_of_charges - activation_cost;   
            }
        }
    }
    
}
}


 void Ritual::apply_target (Player* active,  Player* affected, Card* &target){


    


 }







string Ritual::getCardType() const{
    return CARDTYPE;
}
int   Ritual::getCardCost() {
    return cost;
}

Ritual::~Ritual(){


}

void Ritual::setCharge(int charge){
    no_of_charges = charge;
}

void Ritual::addCharges(int add){
    no_of_charges = no_of_charges + add ;
}
