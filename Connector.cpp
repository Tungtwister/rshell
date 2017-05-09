#include "Connector.h"

Connector::Connector() 
{
    left = NULL;
    right = NULL;
}

Connector::Connector(Base* left, Base* right) 
{
    this->left = left;
    this->right = right;
}