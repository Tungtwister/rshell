#ifndef OR_H
#define OR_H

#include "Connector.h"
#include "Base.h"

class Or : public Connector
{
    public:
        Or();
        Or(Base* left, Base* right);
        void setLeft(Base* left);
        void setRight(Base* right);
        bool execute();
};

#endif