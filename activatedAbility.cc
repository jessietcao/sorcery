#include "activatedAbility.h"
#include "minionComponent.h"


ActivatedAbility::ActivatedAbility(string cardName): cardName{cardName} {
    if (cardName == "Novice Pyromancer") {
        activateCost = 1;
    } else if (cardName == "Apprentice Summoner") {
        activateCost = 1;
    } else if (cardName == "Master Summoner") {
        activateCost = 2;
    } 
    abilityActivated = false;
}

bool ActivatedAbility::apply(Player *activeP, Player *inactiveP) {
    if (cardName == "Apprentice Summoner" && activeP->getMinionsPlayed().size() < 5){
            MinionComponent *mc = new Minion("Air Elemental");
            activeP->getMinionsPlayedReference().push_back(mc);
            return true;
    } else if (cardName == "Master Summoner" && activeP->getMinionsPlayed().size() < 5) {
        int count = 0; //number of air elementals, maximum 3
        for (int i = activeP->getMinionsPlayed().size(); i < 5 && count < 3; i++) {
            MinionComponent *mc = new Minion("Air Elemental");
            activeP->getMinionsPlayedReference().push_back(mc);
            count++;
        }
        return true;
    }
    return false;
}

bool ActivatedAbility::apply(Player *activeP, Player *inactiveP, MinionComponent *mc) { //INDICES ARE 0 1 2 3 4
    if (cardName == "Novice Pyromancer") {
        //DEAL 1 DAMAGE TO TARGET MINION 
        mc->setDefense(mc->getDefense() - 1);
        activeP->setmagic(activeP->getmagic() - activateCost); //inside the minion card, needs to subtract an action point
        return true;
    }
    return false;
}

int ActivatedAbility::getActivateCost() {
    return activateCost;
}


