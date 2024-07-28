#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <string>
#include <vector>
#include "player.h"
#include "card.h"
#include "subject.h"
using namespace std;

class Board : public Subject {
        Player *player1;
        Player *player2;
        bool activePlayer; // true -> player 1 turn; false -> player 2 turn
        bool gameStart;

    public:
        Board(string name1, string name2, vector<string> deck1, vector<string> deck2);
        ~Board();
        void display();
        void displayHand();
        void inspectMinion(int minionIndex);
        void attackPlayer(int minionIndex);
        void attackMinion(int activeIndex, int inactiveIndex);
        void discard(int index);
        void play(int index);
        void play(int activeIndex, int player, char otherPlayerCard);
        void draw();
        void use(int minionIndex);
        void use(int minionIndex, int player, char otherPlayerCard);
        Player* getPlayer1();
        Player* getPlayer2();
        void setActivePlayer(bool ap);
        void setGameStart(bool g);
        void isTriggered();
        void setTurns();
        bool checkPlayersLife();
};



#endif
