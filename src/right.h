#ifndef RIGHT_H
#define RIGHT_H

#include <unistd.h>
#include <string>
#include <stdio.h>
#include "Base.h"

using namespace std;

class Right : public Base {
private:
    Base* left;
    string right;
public:
    Right();
    void setLeft(Base* l);
    void setRight(string r);
    bool execute();
};

#endif