#include "minionComponent.h"
#include "activatedAbility.h"

MinionComponent::MinionComponent(string cardName): Card{cardName}{}



void MinionComponent::useActivatedAbility(Player *active, Player *other) {
    ActivatedAbility *aa = getActivatedAbility();
    if (aa) {
        aa->apply(active, other);
    }
    
}

void MinionComponent::useActivatedAbility_target(Player *active, Player *other, MinionComponent *mc) {
    ActivatedAbility *aa = getActivatedAbility();
    if (aa) {
        aa->apply(active, other, mc);
    }
}

char MinionComponent::cardAt(int x, int y) const { //be careful when used from other class
                                            //x and y start from 0, are relatvie to the card itself not the board
    
    //Minions
    if (getMCardDesc() == "") return display_minion_no_ability(getMCardName(), getMCost(), getAttack(), getDefense())[x][y];
    if (getMCardName() == "Novice Pyromancer" || //cards with activated abilties
        getMCardName() == "Apprentice Summoner" ||
        getMCardName() == "Master Summoner") return display_minion_activated_ability(getMCardName(), getMCost(), getAttack(), getDefense(), getActivateCost(), getMCardDesc())[x][y]; 
    return display_minion_triggered_ability(getMCardName(), getMCost(), getAttack(), getDefense(), getMCardDesc())[x][y];
    
}

char MinionComponent::cardAtMinion(int x, int y) const { //be careful when used from other class
                                            //x and y start from 0, are relatvie to the card itself not the board
    
    //Minions
    if (getMCardDesc() == "") return display_minion_no_ability(getMCardName(), getMCost(), getAttack(), getDefense())[x][y];
    if (getMCardName() == "Novice Pyromancer" || //cards with activated abilties
        getMCardName() == "Apprentice Summoner" ||
        getMCardName() == "Master Summoner") return display_minion_activated_ability(getMCardName(), getMCost(), getAttack(), getDefense(), getActivateCost(), getMCardDesc())[x][y]; 
    return display_minion_triggered_ability(getMCardName(), getMCost(), getAttack(), getDefense(), getMCardDesc())[x][y];
    
}



MinionComponent::~MinionComponent() {

}
