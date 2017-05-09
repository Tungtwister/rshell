#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "Base.h"

class Connector : public Base
{
    private:
        Base* left;
        Base* right;
    public:
        Connector();
        Connector(Base* left, Base* right);
        virtual bool execute() = 0;
};

#endif
