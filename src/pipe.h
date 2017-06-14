#ifndef PIPE_H
#define PIPE_H

#include <unistd.h>
#include <string>
#include <stdio.h>
#include "Base.h"

using namespace std;

class Pipe : public Base {
private:
    Base* left;
    string right;
public:
    Pipe();
    void setLeft(Base* l);
    void setRight(string r);
    bool execute();
};

#endif
