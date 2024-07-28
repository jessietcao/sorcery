#ifndef TEXTOBSERVER_H
#define TEXTOBSERVER_H
#include "observer.h"
#include "board.h"
#include "subject.h"
#include <iostream>
using namespace std;

class TextObserver : public Observer {
    Board *b;
    public:
        TextObserver(Board *b);
        ~TextObserver();
        void notify();
};

#endif
