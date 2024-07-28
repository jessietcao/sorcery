#include "board.h"
#include "player.h"
#include "minionComponent.h"


Board::Board(string name1, string name2, vector<string> deck1, vector<string> deck2) {
    player1 = new Player(name1);
    player2 = new Player(name2);
    player1->init_deck(deck1);
    player2->init_deck(deck2);
}

Board::~Board() {
    delete player1;
    delete player2;
}

void Board::display() {
    notifyObservers();    
}

Player* Board::getPlayer1() {return player1;}
Player* Board::getPlayer2() {return player2;}

void Board::setActivePlayer(bool ap) {activePlayer = ap;}

void Board::displayHand() {
    Player *p;
    if (activePlayer) {
        p = player1;
    } else {
        p = player2;
    }

    int numCards = p->getHand().size();
    //cout << numCards << endl;
    
    for (int i = 0; i < 11; ++i) {
        for (int k = 0; k < numCards; ++k) {
            for (int j = 0; j < 33; ++j) {
                cout << p->getHand()[k]->cardAt(i, j);     
            }
        }
        cout << endl;
    }
}

void Board::inspectMinion(int minionIndex) {
    
    Player *p;
    if (activePlayer) {
        p = player1;
    } else {
        p = player2;
    }

    vector<MinionComponent*> list;
    MinionComponent* m = p->getMinionsPlayed()[minionIndex];

    
    for (int i = 0; i < 11; ++i) {
        for (int j = 0; j < 33; ++j) {
            cout << m->cardAtMinion(i,j);         
        }
        cout << endl;
    }

     while(m != nullptr) {
        list.push_back(m);
        m = m->getNext();
    }

    list.pop_back(); 

    int numRows;

    if((list.size() % 5) == 0) {
        numRows = list.size() / 5;
    } else {
        numRows = (list.size() / 5) + 1;
    }

    int numEnchantments = list.size();
    int counter = numEnchantments-1;

    for (int i = 0; i < numRows; ++i) {
        int num = (numEnchantments >= 5) ? 5 : numEnchantments;
        numEnchantments -= num;
        for (int j = 0; j < 11; ++j) {
            for (int k = 0; k < num; ++k) {
                for (int m = 0; m < 33; ++m) {
                    cout << list[counter]->cardAt(j, m);
                }
                counter -= 1;
            }
            counter += num;
            cout << endl;
        }
        counter -= num;
    }

}

void Board::attackPlayer(int minionIndex) {
    Player *currP;
    Player *oppP;
    if (activePlayer) {
        currP = player1;
        oppP = player2;
    } else {
        currP = player2;
        oppP = player1;
    }
    if (currP->getMinionsPlayed()[minionIndex]->getAction() > 0) {
        oppP->setlife(oppP->getlife() - (currP->getMinionsPlayed()[minionIndex])->getAttack());
        currP->getMinionsPlayed()[minionIndex]->setAction(currP->getMinionsPlayed()[minionIndex]->getAction() - 1);
    } else {
        cout << "Not enough action points" << endl;
    }
    
}

void Board::attackMinion(int activeIndex, int inactiveIndex) {
    Player *currP;
    Player *oppP;
    if (activePlayer) {
        currP = player1;
        oppP = player2;
    } else {
        currP = player2;
        oppP = player1;
    }
    MinionComponent *inactiveM = oppP->getMinionsPlayed()[inactiveIndex];
    MinionComponent *activeM = currP->getMinionsPlayed()[activeIndex];
    if (currP->getMinionsPlayed()[activeIndex]->getAction() > 0) {
        inactiveM->setDefense(inactiveM->getDefense() - activeM->getAttack());
        activeM->setDefense(activeM->getDefense() - inactiveM->getAttack());
        activeM->setAction(activeM->getAction() - 1);
        //cout << activeM->getAction() << endl;
    } else {
        cout << "Not enough action points" << endl;
    }
    player1->addtograveyard();
    player2->addtograveyard();
    isTriggered();
    player1->setMinionLeavePlay(false);
    player2->setMinionLeavePlay(false);
}

void Board::discard(int index) {
    Player *p;
    if (activePlayer) {
        p = player1;
    } else {
        p = player2;
    }
    p->removeCard(index);
}

void Board::play(int index) {
    Player *currP;
    Player *oppP;
    if (activePlayer) {
        currP = player1;
        oppP = player2;
    } else {
        currP = player2;
        oppP = player1;
    }

    if (currP->getmagic() >= currP->getHand()[index]->getCardCost()) {

        if (currP->getHand()[index]->getCardType() == "minion") {
            Minion* converted_minion = dynamic_cast <Minion*> (currP->getHand()[index]);
            currP->add_minions_played(converted_minion);
            // seetting minion entered to true;
            currP->setMinionEnterPlay(true);      
            isTriggered();
            //setting minion entered to false;
            currP->setMinionEnterPlay(false);
        } else if (currP->getHand()[index]->getCardType() == "ritual") {
            Ritual* convertedRitual = dynamic_cast <Ritual*> (currP->getHand()[index]);
            currP->add_ritual_played(convertedRitual);
        } else if (currP->getHand()[index]->getCardType() == "spell") {
            Spell* convertedSpell = dynamic_cast <Spell*> (currP->getHand()[index]);
            currP->addSpellUsed(convertedSpell);
        }
        currP->setmagic(currP->getmagic() - currP->getHand()[index]->getCardCost());
        if (currP->getHand()[index]->getCardType() == "spell") {
            currP->getHand()[index]->apply(currP, oppP);
        }
        currP->removeCard(index); 
    }
    player1->addtograveyard();
    player2->addtograveyard();
    isTriggered();
    player1->setMinionLeavePlay(false);
    player2->setMinionLeavePlay(false);

}

void Board::play(int activeIndex, int player, char otherPlayerCard) {

    Player *currP;
    if (activePlayer) {
        currP = player1;
    } else {
        currP = player2;
    }

    if (currP->getmagic() >= currP->getHand()[activeIndex]->getCardCost()) { 

        if (currP->getHand()[activeIndex]->getCardType() == "minion") {
            Minion* converted_minion = dynamic_cast <Minion*> (currP->getHand()[activeIndex]);
            currP->add_minions_played(converted_minion);
            // setting minion entered to true;
            currP->setMinionEnterPlay(true);        
            isTriggered();
            //setting minion entered to false;
            currP->setMinionEnterPlay(false);
        } else if (currP->getHand()[activeIndex]->getCardType() == "ritual") {
            Ritual* convertedRitual = dynamic_cast <Ritual*> (currP->getHand()[activeIndex]);
            currP->add_ritual_played(convertedRitual);
        } else if (currP->getHand()[activeIndex]->getCardType() == "spell") {
            Spell* convertedSpell = dynamic_cast <Spell*> (currP->getHand()[activeIndex]);
            currP->addSpellUsed(convertedSpell);
        } 
        

        int ithMinion;

        if (otherPlayerCard != 'r') {
            ithMinion = otherPlayerCard - '1';
        }

        if (player == 1) {
            if (otherPlayerCard == 'r') {
                Ritual* ritual_card = player1->getRitualPlayed();
                currP->getHand()[activeIndex]->apply_target(currP, player1, reinterpret_cast<Card*&>(ritual_card));
            } else {
                MinionComponent* minionCard = player1->getMinionsPlayed()[ithMinion];
                if (currP->getHand()[activeIndex]->getCardName() != "Banish" && currP->getHand()[activeIndex]->getCardName() != "Unsummon") {
                    currP->getHand()[activeIndex]->apply_target(currP, player1, reinterpret_cast<Card*&>(minionCard));
                    player1->removeMinion__played(player1->getMinionsPlayed()[ithMinion]);
                    player1->add_minions_played_to_index(minionCard, ithMinion);
                } else {
                    currP->getHand()[activeIndex]->apply_target(currP, player1, reinterpret_cast<Card*&>(minionCard));
                }
                
            }
        } else {
            if (otherPlayerCard == 'r') {
                Ritual* ritual_card = player2->getRitualPlayed();
                currP->getHand()[activeIndex]->apply_target(currP, player2, reinterpret_cast<Card*&>(ritual_card));
            } else {
                MinionComponent* minionCard = player2->getMinionsPlayed()[ithMinion];
                if (currP->getHand()[activeIndex]->getCardName() != "Banish" && 
                    currP->getHand()[activeIndex]->getCardName() != "Unsummon") {
                    currP->getHand()[activeIndex]->apply_target(currP, player2, reinterpret_cast<Card*&>(minionCard));
                    player2->removeMinion__played(player2->getMinionsPlayed()[ithMinion]);
                    player2->add_minions_played_to_index(minionCard, ithMinion);
                } else {
                    currP->getHand()[activeIndex]->apply_target(currP, player2, reinterpret_cast<Card*&>(minionCard));
                }
                
            }
        }

        currP->setmagic(currP->getmagic() - currP->getHand()[activeIndex]->getCardCost());
        currP->removeCard(activeIndex); 
    }
    player1->addtograveyard();
    player2->addtograveyard();
    isTriggered();
    player1->setMinionLeavePlay(false);
    player2->setMinionLeavePlay(false);

}

void Board::draw() {
    Player *p;
    if (activePlayer) {
        p = player1;
    } else {
        p = player2;
    }
    p->addCard();
}

void Board::use(int minionIndex) { //used for minions' activated abilities
    Player *currP;
    Player *oppP;
    if (activePlayer) {
        currP = player1;
        oppP = player2;
    } else {
        currP = player2;
        oppP = player1;
    }

 //confirm from minions played or hand 
    int action = currP->getMinionsPlayed()[minionIndex]->getAction();
    if (!currP->getMinionsPlayed()[minionIndex]->getActivatedAbility()) {
        std::cout << "Selected card cannot use activated abilities" << endl;
    } else if (currP->getmagic() >= currP->getMinionsPlayed()[minionIndex]->getActivateCost() &&
        action > 0) {  
        currP->getMinionsPlayed()[minionIndex]->useActivatedAbility(currP, oppP); //use activated ability
        currP->setmagic(currP->getmagic() -  currP->getMinionsPlayed()[minionIndex]->getActivateCost());
        currP->getMinionsPlayed()[minionIndex]->setAction(currP->getMinionsPlayed()[minionIndex]->getAction() - 1);
    } else {
        cout << "Not enough action or magic points" << endl;
    }
    player1->addtograveyard();
    player2->addtograveyard();
    isTriggered();
    player1->setMinionLeavePlay(false);
    player2->setMinionLeavePlay(false);
}

void Board::use(int minionIndex, int player, char otherPlayerCard) { //minion's activated abilities with target
    
    Player *currP;
    if (activePlayer) {
        currP = player1;
    } else {
        currP = player2;
    }

    //confirm from hands or minions played

    if (!currP->getMinionsPlayed()[minionIndex]->getActivatedAbility()) {
        std::cout << "Selected card cannot use activated abilities" << endl;
    } else if (currP->getmagic() >= currP->getMinionsPlayed()[minionIndex]->getActivateCost() &&
            currP->getMinionsPlayed()[minionIndex]->getAction() > 0) { 

        int ithMinion;

        if (otherPlayerCard != 'r') {
           ithMinion = otherPlayerCard - '1';
        }

        if (player == 1) {
            if (otherPlayerCard == 'r') {
                Ritual* ritual_card = player1->getRitualPlayed();
                currP->getMinionsPlayed()[minionIndex]->apply_target(currP, player1, reinterpret_cast<Card*&>(ritual_card));
            } else {
                MinionComponent* minionCard = player1->getMinionsPlayed()[ithMinion];
                currP->getMinionsPlayed()[minionIndex]->useActivatedAbility_target(currP, player1, minionCard); //use activated ability
                player1->removeMinion__played(minionCard);
                player1->add_minions_played_to_index(minionCard, ithMinion);
            }
        } else {
            if (otherPlayerCard == 'r') {
                Ritual* ritual_card = player2->getRitualPlayed();
                currP->getMinionsPlayed()[minionIndex]->apply_target(currP, player2, reinterpret_cast<Card*&>(ritual_card));
            } else {
                MinionComponent* minionCard = player2->getMinionsPlayed()[ithMinion];
                currP->getMinionsPlayed()[minionIndex]->useActivatedAbility_target(currP, player2, minionCard);//use activated ability
                player2->removeMinion__played(minionCard);
                player2->add_minions_played_to_index(minionCard, ithMinion);
            }
        }

        currP->setmagic(currP->getmagic() -  currP->getMinionsPlayed()[minionIndex]->getActivateCost());
        currP->getMinionsPlayed()[minionIndex]->setAction(currP->getMinionsPlayed()[minionIndex]->getAction() - 1);

    }  else {
        cout << "Not enough action or magic points" << endl;
    }
    player1->addtograveyard();
    player2->addtograveyard();
    isTriggered();
    player1->setMinionLeavePlay(false);
    player2->setMinionLeavePlay(false);
    
}

void Board::setGameStart(bool g) {
    gameStart = g;
}

MinionComponent* checkHaste(MinionComponent* m) {
    while(m != nullptr) {
        if (m->getCardName() == "Haste") {
            return m;
        }
        m = m->getNext();
    }
    return nullptr;
}

void Board::isTriggered() {
    Player *currP;
    Player *oppP;
    if (activePlayer) {
        currP = player1;
        oppP = player2;
    } else {
        currP = player2;
        oppP = player1;
    }
    for (long unsigned int i = 0; i < currP->getMinionsPlayed().size(); ++i) {
        if (currP->getMinionsPlayed()[i]->getMinion()->getCardName() == "Bone Golem") {
            if (currP->getMinionLeavePlay() || oppP->getMinionLeavePlay()) {
                currP->getMinionsPlayed()[i]->apply(currP, oppP);
            }
        } else if (currP->getMinionsPlayed()[i]->getMinion()->getCardName() == "Fire Elemental") {
            if (oppP->getMinionEnterPlay()) {
                currP->getMinionsPlayed()[i]->apply(currP, oppP);
            }
        }
        if (currP->getStartTurn() && currP->getOneTimeTriggerH() == false) {
            MinionComponent* card = checkHaste(currP->getMinionsPlayed()[i]);
            if (card != nullptr) {
                card->apply(currP, oppP); 
                currP->setOneTimeTriggerH(true);
            }
        }
    }
    for (long unsigned int i = 0; i < oppP->getMinionsPlayed().size(); ++i) {
        if (oppP->getMinionsPlayed()[i]->getMinion()->getCardName() == "Bone Golem") {
            if (currP->getMinionLeavePlay() || oppP->getMinionLeavePlay()) {
                oppP->getMinionsPlayed()[i]->apply(currP, oppP);
            }
        } else if (oppP->getMinionsPlayed()[i]->getMinion()->getCardName() == "Fire Elemental") {
            if (currP->getMinionEnterPlay()) {
                oppP->getMinionsPlayed()[i]->apply(currP, oppP);
            }
        }
    }
    if (oppP->getOneTimeTriggerPS() == false) {
        for (long unsigned int i = 0; i < oppP->getMinionsPlayed().size(); ++i) {
            if (oppP->getMinionsPlayed()[i]->getMinion()->getCardName() == "Potion Seller") {
                if (!oppP->getStartTurn()) {
                    oppP->getMinionsPlayed()[i]->apply(currP, oppP);
                    oppP->setOneTimeTriggerPS(true);
                }
            }
        }
    }
    if (currP->getRitualPlayed() != nullptr) {
        if (currP->getRitualPlayed()->getCardName() == "Dark Ritual") {
            if (currP->getOneTimeTriggerDR() == false) {
                if (currP->getStartTurn()) {
                    currP->getRitualPlayed()->apply(currP, oppP);
                    currP->setOneTimeTriggerDR(true);
                }
            }
        } else if (currP->getRitualPlayed()->getCardName() == "Aura of Power") {
            if (currP->getMinionEnterPlay()) {
                currP->getRitualPlayed()->apply(currP, oppP);
            }
        } else if (currP->getRitualPlayed()->getCardName() == "Standstill") {
            if (currP->getMinionEnterPlay()) {
                currP->getRitualPlayed()->apply(currP, oppP);
            }
        }
    }
    if (oppP->getRitualPlayed() != nullptr) {
        if (oppP->getRitualPlayed()->getCardName() == "Standstill") {
            if (currP->getMinionEnterPlay()) {
                oppP->getRitualPlayed()->apply(currP, oppP);
            }
        }
    }
    
}

void Board::setTurns() {
    if (activePlayer) {
        player1->setStartTurn(true); 
        player2->setStartTurn(false);
    } else {
        player2->setStartTurn(true);
        player1->setStartTurn(false);
    }
    draw();
    Player *currP;
    Player *oppP;
    if (activePlayer) {
        currP = player1;
        oppP = player2;
    } else {
        currP = player2;
        oppP = player1;
    }

    if (!gameStart) {
        currP->setStartAction();
    }
    
    currP->setmagic(currP->getmagic() + 1);
    currP->setOneTimeTriggerDR(false);
    currP->setOneTimeTriggerH(false);
    currP->setOneTimeTriggerPS(false);
    oppP->setOneTimeTriggerDR(false);
    oppP->setOneTimeTriggerH(false);
    oppP->setOneTimeTriggerPS(false);
    currP->setMinionLeavePlay(false);
    oppP->setMinionLeavePlay(false);
    currP->setMinionEnterPlay(false);
    oppP->setMinionEnterPlay(false);
    if (gameStart) {
        setGameStart(false);
    } 
}


bool Board::checkPlayersLife() {
    if (player1->getlife() <= 0 || player2->getlife() <= 0) {
        return true;
    }
    return false;
}


