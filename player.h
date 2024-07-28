#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "card.h"
#include "minionComponent.h"
#include "decorator.h"
#include "minion.h"
#include "ritual.h"
#include "spell.h"
#include "enchantment.h"

using namespace std;

class Player{
    protected:
        string  name;
        int life;
        int magic;
        vector<Card*> hand;
        vector<Minion*> graveyard;
        vector<Card*> deck;
        vector<MinionComponent *> minionsPlayed;
        vector<Spell*> spellUsed;
        Ritual * ritualPlayed;
        bool startTurn;
        bool minionEnterPlay;
        bool minionLeavePlay;    
        bool oneTimeTriggerPS;
        bool oneTimeTriggerH;
        bool oneTimeTriggerDR;
    
    public:
        Player (string name);
        int getlife();
        void setlife(int new_life);
        int getmagic();
        void setmagic(int new_magic);
        void init_deck(vector<string> deck_string);
        void addtograveyard();
        void removetopgraveyard();
        char card_at(int player_num, int x, int y);
        Card* playCard (int index);
        void addCard ( );
        void removeCard (int index);
        ~Player();
        vector<Card *> getHand();
        vector<Minion *> getGraveyard();
        vector<Card *> getDeck(); 
        Ritual*& getRitualPlayed();
        vector<MinionComponent *> getMinionsPlayed();
        void add_minions_played(MinionComponent* minion);
        void removeMinion__played(MinionComponent* m );
        void add_ritual_played(Ritual* ritual);
        void add_minion_to_hand (Minion*& minion);
        void setStartTurn(bool turn);
        bool getStartTurn();
        bool getMinionEnterPlay();
        bool getMinionLeavePlay();
        void setMinionEnterPlay(bool enter);
        void setMinionLeavePlay(bool leave);
        void setStartAction();
        void add_minions_played_to_index(MinionComponent* minion, int i);
        void addMinionToGraveyard(Minion*);
        vector<MinionComponent *> &getMinionsPlayedReference();
        void deleteRitualPlayed();
        string getName();
        void setOneTimeTriggerPS(bool b);
        bool getOneTimeTriggerPS();
        void setOneTimeTriggerH(bool b);
        bool getOneTimeTriggerH();
        void setOneTimeTriggerDR(bool b);
        bool getOneTimeTriggerDR();
        void addMinionComponentToGraveyard(MinionComponent* &mc);
        void addSpellUsed(Spell* s);

};


#endif







