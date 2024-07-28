#ifndef ACTIVATEDABILITY_H
#define ACTIVATEDABILITY_H  


#include "player.h"


using namespace std;

class MinionComponent;
class ActivatedAbility {
    string cardName;
    int activateCost;
    bool abilityActivated;
    public:
        ActivatedAbility(string cardDesc);
        bool apply(Player *active, Player *inactive);
        bool apply(Player *activeP, Player *inactiveP, MinionComponent *mc);
        int getActivateCost();
};


#endif
