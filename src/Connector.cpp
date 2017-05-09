#include <iostream>
#include "Connector.h"
#include "Base.h"

using namespace std;

// Constructors
Connector::Connector() { }

Connector::Connector(Base* left, Base* right) 
{
    this->left = left;
    this->right = right;
}