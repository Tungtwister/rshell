#ifndef SEMICOLON_H
#define SEMICOLON_H

#include "Connector.h"
#include "Base.h"

class Semicolon : public Connector
{
    public:
        Semicolon();
        Semicolon(Base* left, Base* right);
        void setLeft(Base* left);
        void setRight(Base* right);
        bool execute();
};

#endif