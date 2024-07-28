#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <fstream>
#include <string>
#include "board.h"
#include "card.h"
#include "minion.h"
#include "textObserver.h"
#include "graphicObserver.h"

using namespace std;

int main( int argc, char * argv[] ) {

	string player1Deck = "cardFiles/default.deck";
    string player2Deck = "cardFiles/default.deck";
    string startCommandsFile = "";
    bool testing = false;
    bool initFileGiven = false;
    bool graphic = false;

    for (int i = 1; i < argc; ++i) {
        string argument = argv[i];
        if (argument == "-deck1") {
            if (i+1 < argc) {
                argument = argv[i + 1];
                i += 1;
                if (argument != "-deck2" && argument != "-init" && argument != "-testing" && argument != "-graphics") {
                    player1Deck = argument;
                }  
            }           
        } else if (argument == "-deck2") {
            if (i+1 < argc) {
                argument = argv[i + 1];
                i += 1;
                if (argument != "-deck1" && argument != "-init" && argument != "-testing" && argument != "-graphics") {
                    player2Deck = argument;
                }  
            }  
        } else if (argument == "-init") {
            initFileGiven = true;
            argument = argv[i + 1];
            i += 1;
            startCommandsFile = argument;
        } else if (argument == "-testing") {
            testing = true;
        } else if (argument == "-graphics") {
            graphic = true;
        }
    }

    vector<string> deck1; //full deck of cards
    vector<string> deck2;
    ifstream iff1{player1Deck}; 
    ifstream iff2{player2Deck};
    string cardName;
    while(getline(iff1, cardName)) {
        deck1.push_back(cardName);
    }
    while(getline(iff2, cardName)) {
        deck2.push_back(cardName);
    }

    if (!testing) {
        // use a time-based seed for the default seed value
        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        default_random_engine rng{seed};
        shuffle( deck1.begin(), deck1.end(), rng ); //shuffle the cards
        shuffle( deck2.begin(), deck2.end(), rng );
    } 

    string player1Name, player2Name;
    ifstream iff{startCommandsFile};
    
    if (initFileGiven) {
        getline(iff, player1Name);
        getline(iff, player2Name);
    } else {
        std::cout << "Enter the first player's name: " << endl;
        getline(cin, player1Name);
        std::cout << "Enter the second player's name: " << endl;
        getline(cin, player2Name);
    }

    Board *board = new Board(player1Name, player2Name, deck1, deck2);
    TextObserver *t = new TextObserver(board);
    GraphicObserver *g = nullptr;
    if (graphic) {
        g = new GraphicObserver(board);
    }
    

    string command;
    bool activePlayer = true; // true -> player 1 turn; false -> player 2 turn
    board->setGameStart(true);
    board->setActivePlayer(activePlayer);
    board->setTurns();
    string line;
    board->isTriggered();

    while (true) {
        if (board->checkPlayersLife()) {
            break;
        }
        if (initFileGiven) {
            if (!getline(iff, line)) {
                initFileGiven = false;
                getline(cin, line);
            }
        } else {
            getline(cin, line);
        }
        istringstream iss{line};
        iss >> command;
        if (command == "help") {
            std::cout << "Commands: help -- Display this message." << endl;
            std::cout << "          end -- End the current player’s turn." << endl;
            std::cout << "          quit -- End the game." << endl;
            std::cout << "          attack minion other-minion -- Orders minion to attack other-minion." << endl;
            std::cout << "          attack minion -- Orders minion to attack the opponent." << endl;
            std::cout << "          play card [target-player target-card] -- Play card, optionally targeting target-card owned by target-player." << endl;
            std::cout << "          use minion [target-player target-card] -- Use minion’s special ability, optionally targeting target-card owned by target-player." << endl;
            std::cout << "          inspect minion -- View a minion’s card and all enchantments on that minion." << endl;
            std::cout << "          hand -- Describe all cards in your hand." << endl;
            std::cout << "          board -- Describe all cards on the board." << endl;
        } else if (command == "end") {
            activePlayer = !activePlayer;
            board->setActivePlayer(activePlayer);
            board->setTurns();
            board->isTriggered();
        } else if (command == "quit") {
            break;
        } else if (command == "draw") {
            if (!testing) {
                continue;
            }
            board->draw();
        } else if (command == "discard") {
            if (!testing) {
                continue;
            }
            int i;
            iss >> i;
            board->discard(i-1);
        } else if (command == "attack") {
            int i, j;
            iss >> i;
            if (iss >> j) {
                board->attackMinion(i-1, j-1);
            } else {
                board->attackPlayer(i-1);
            }
        } else if (command == "play") {
            int i, p;
            char t;
            iss >> i;
            if (iss >> p >> t) {
                board->play(i-1, p, t);
            } else {
                board->play(i-1);
            }
        } else if (command == "use") {
            int i, p;
            char t;
            iss >> i;
            if (iss >> p >> t) {
                board->use(i-1, p, t);
            } else {
                board->use(i-1);
            }
        } else if (command == "inspect") {
            int i;
            iss >> i;
            board->inspectMinion(i-1);
        } else if (command == "hand") {
            board->displayHand();
        } else if (command == "board") {
            board->display();
        }
    }	
    delete t;
    if (graphic) {
        delete g;
    }
    delete board;

	return 0;
} // main
