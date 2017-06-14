#ifndef LEFT_H
#define LEFT_H

#include <unistd.h>
#include <string>
#include <stdio.h>
#include "Base.h"

using namespace std;

class Left : public Base {
private:
    Base* left;
    string right;
public:
    Left();
    void setLeft(Base* l);
    void setRight(string r);
    bool execute();
};

#endif