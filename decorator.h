#ifndef DECORATOR_H
#define DECORATOR_H

#include "minionComponent.h"
#include <string>

class Decorator: public MinionComponent {
    protected:
        MinionComponent *next;
    public:
        Decorator(MinionComponent *p, string cardName): MinionComponent{cardName}, next{p}{}
        ~Decorator() override {delete next;}
        virtual MinionComponent* getNext() override {
            return next;
        }
        virtual void setNext(MinionComponent* n) override {next = n;}
};


#endif
