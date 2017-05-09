#ifndef AND_H
#define AND_H

#include "Connector.h"
#include "Base.h"

class And : public Connector
{
    public:
        And();
        And(Base* left, Base* right);
        void setLeft(Base* left);
        void setRight(Base* right);
        bool execute();
};

#endif