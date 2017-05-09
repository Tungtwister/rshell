#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <iostream>
#include <cstdlib>

#include "Base.h"

using namespace std;

class Connector : public Base
{
    // protected for And class, Or class, and Semicolon class to use
    protected:
        Base* left;
        Base* right;
    public:
        Connector();
        Connector(Base* left, Base* right);
        virtual bool execute() = 0;
};

#endif