#ifndef APPEND_H
#define APPEND_H

#include <unistd.h>
#include <string>
#include <stdio.h>
#include "Base.h"

using namespace std;

class Append : public Base {
private:
    Base* left;
    string right;
public:
    Append();
    void setLeft(Base* l);
    void setRight(string r);
    bool execute();
};

#endif