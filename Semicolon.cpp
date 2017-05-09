#include "Semicolon.h"
#include "Connector.h"

// Constructors
Semicolon::Semicolon() : Connector() {}

Semicolon::Semicolon(Base* left, Base* right) : Connector(left, right) {
    this->left = left;
    this->right = right;
}

// set left
void Semicolon::setLeft(Base* left) {
    this->left = left;
}

// set right
void Semicolon::setRight(Base* right) {
    this->right = right;
}

// anything after the semicolon will execute no matter what
// will return true
bool Semicolon::execute() {
    left->execute();
    right->execute();
    
    return true;
}