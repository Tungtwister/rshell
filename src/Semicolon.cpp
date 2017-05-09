#include "Semicolon.h"
#include "Connector.h"
#include "Base.h"

// Constructors
Semicolon::Semicolon() : Connector() {
    left = 0;
    right = 0;
}

Semicolon::Semicolon(Base* left, Base* right) : Connector(left,right) {
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
    // cout << "semicolon execute" << endl;
    left->execute();
    right->execute();
    
    return true;
}