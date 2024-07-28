#include "player.h"
#include "ascii_graphics.h"

using namespace std;

Player::Player ( string name) :  name {name} , life {20} , magic {3}, ritualPlayed{nullptr}, startTurn{false},
    minionEnterPlay{false}, minionLeavePlay{false}, oneTimeTriggerPS{false}, oneTimeTriggerH{false}, oneTimeTriggerDR{false} {
        
}

Player ::~Player() {

    for(auto card : hand) {
        delete card;
    }

    for (auto card: graveyard) {
        delete card;
    }

    for (auto card: deck) {
        delete card;
    }

    for (auto card: minionsPlayed){
        delete card;
    }

    for (auto card: spellUsed){
        delete card;
    }

    delete ritualPlayed;

}

void Player::setStartAction() {
    for (auto m: minionsPlayed) {
        m->setAction(1); //set each action to 1 at the start of the turn
    }
}

char Player::card_at(int player_num, int x, int y) {
    return display_player_card(player_num, name, life, magic)[x][y];
}

int Player::getlife() {
    return life;
}

void Player::setlife(int new_life) { 
    life = new_life;
}


int Player::getmagic(){
    return magic;

}

void Player::setmagic(int new_magic) {
    magic = new_magic;
}

void Player::addtograveyard() {
    vector<int> to_delete;
    for (size_t i = 0; i < minionsPlayed.size(); ++i) {
        if (minionsPlayed[i]->getDefense() <= 0) {
            minionsPlayed[i]->setAction(0);
            graveyard.push_back(minionsPlayed[i]->getMinion());
            to_delete.push_back(i);
            minionLeavePlay = true;
        }
    }
    for (auto it = to_delete.rbegin(); it != to_delete.rend(); ++it) {
        minionsPlayed.erase(minionsPlayed.begin() + *it);
    }
}

void Player::removetopgraveyard(){
    graveyard.pop_back();
}


void Player::addMinionToGraveyard(Minion* m) {
    m->setAction(0);
    graveyard.push_back(m);
    for (size_t i = 0; i < minionsPlayed.size(); ++i) {
        if (minionsPlayed[i]->getMinion() == m) {
            minionsPlayed.erase(minionsPlayed.begin() + i);
            minionLeavePlay = true;
        }
    }
}

void Player::addMinionComponentToGraveyard(MinionComponent* &mc) {
    mc->setAction(0);
    graveyard.push_back(mc->getMinion());
    for (size_t i = 0; i < minionsPlayed.size(); ++i) {
        if (minionsPlayed[i]->getMinion() == mc->getMinion()) {
            minionsPlayed.erase(minionsPlayed.begin() + i);
            MinionComponent *next;
            while (mc && mc->getNext()) {
                next = mc->getNext();
                mc->setNext(nullptr);
                delete mc;
                mc = next;
            }
            minionLeavePlay = true;
        }
    }
}


void Player::init_deck(vector<string> deck_string){
    vector<string> minion = {"Air Elemental", "Earth Elemental","Bone Golem", "Fire Elemental", "Potion Seller",
    "Novice Pyromancer" , "Apprentice Summoner", "Master Summoner" };

    vector<string> spell = {"Banish", "Unsummon" , "Recharge" , "Disenchant" , "Raise Dead", "Blizzard" };

    vector<string> enchantment = {"Giant Strength", "Enrage", "Haste", "Magic Fatigue", "Silence"};

    vector<string> ritual = {"Dark Ritual", "Aura of Power", "Standstill"};

    for (auto card_string : deck_string) {

        int found = 0;

        for (auto minion_card : minion ) {
            if (minion_card == card_string) {
                Card* minion_new = new Minion(minion_card);
                deck.push_back(minion_new);
                found = 1;
                break;
            }
        }

        if (found != 1) {
            for (auto spell_card : spell ) {
                if (spell_card == card_string) {
                    Card* spell_new = new Spell(spell_card);
                    deck.push_back(spell_new);
                    found = 1;
                    break;
                 
                 }
            }
        }
         

        if (found != 1) {
            for (auto enchantment_card : enchantment ) {
                if (enchantment_card == card_string) {
                    Card* enchantment_new = new Enchantment(nullptr, enchantment_card);
                    deck.push_back(enchantment_new);
                    found = 1;
                    break;
                }
            }
        }


        if (found != 1)  {
            for (auto ritual_card : ritual ) {
                if (ritual_card == card_string) {
                    Card* ritual_new = new Ritual(ritual_card);
                    deck.push_back(ritual_new);
                    found = 1;
                    break;
                }
            }
        }

    }

    for (int i = 0; i < 5; ++i){
        addCard();
    }
        
}

Card* Player::playCard(int index){
    return hand[index];
}

void Player::addCard(){
    if (hand.size() < 5) {
        hand.push_back(deck.back());
        deck.pop_back();
    }
}


void Player::removeCard (int index){
    hand.erase(hand.begin()+ index);
}


vector<Minion *> Player::getGraveyard() {
    return graveyard;
}

Ritual*& Player::getRitualPlayed() {return ritualPlayed;}

vector<MinionComponent *> Player::getMinionsPlayed() {return minionsPlayed;}
vector<MinionComponent *> &Player::getMinionsPlayedReference() {return minionsPlayed;}


vector<Card *> Player::getHand(){
    return hand;
}

vector<Card *> Player::getDeck(){
    return deck;
}

void Player::add_minions_played(MinionComponent* minion){
    minionsPlayed.push_back(minion); 
}

void Player::add_minions_played_to_index(MinionComponent* minion, int i){
    minionsPlayed.insert(minionsPlayed.begin() + i, minion);
}

void Player::removeMinion__played(MinionComponent* m){  
    for (auto it = minionsPlayed.begin(); it!= minionsPlayed.end(); ++it) {
        if (*it == m){
            minionsPlayed.erase(it);
            break;
        }
    }
}

void Player::add_ritual_played(Ritual* ritual) {
    if (ritualPlayed != nullptr) {
        delete ritualPlayed;
        ritualPlayed = nullptr;
    }
    ritualPlayed = ritual;
}

void Player::deleteRitualPlayed() {
    delete ritualPlayed;
    ritualPlayed = nullptr;
}

void Player::add_minion_to_hand(Minion*& minion) {
    hand.push_back(minion);
}

void Player::setStartTurn(bool turn) {
    startTurn = turn;
}

void Player::setMinionEnterPlay(bool enter){
    minionEnterPlay = enter;
}

void Player::setMinionLeavePlay(bool leave){
    minionLeavePlay = leave;
}

bool Player::getStartTurn() {
    return startTurn;
}

bool Player::getMinionEnterPlay() {
    return minionEnterPlay;
}
bool Player::getMinionLeavePlay() {
    return minionLeavePlay;
}

string Player::getName() {
    return name;
}

void Player::setOneTimeTriggerPS(bool b) {
    oneTimeTriggerPS = b;
}

bool Player::getOneTimeTriggerPS() {
    return oneTimeTriggerPS;
}

void Player::setOneTimeTriggerH(bool b) {
    oneTimeTriggerH = b;
}

bool Player::getOneTimeTriggerH() {
    return oneTimeTriggerH;
}

void Player::setOneTimeTriggerDR(bool b) {
    oneTimeTriggerDR = b;
}

bool Player::getOneTimeTriggerDR() {
    return oneTimeTriggerDR;
}

void Player::addSpellUsed(Spell* s) {
    spellUsed.push_back(s);
}
