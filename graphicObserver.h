#ifndef GRAPHICOBSERVER_H
#define GRAPHICOBSERVER_H
#include "observer.h"
#include "board.h"
#include "window.h"

class GraphicObserver : public Observer {
    Board *b;
    Xwindow *xw;
    int pixel = 10;
    public:
        GraphicObserver(Board *b);
        ~GraphicObserver();
        void notify();

};

#endif
