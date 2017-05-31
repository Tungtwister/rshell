#include "And.h"
#include "Connector.h"
#include "Base.h"

// Constructors
And::And() : Connector() {}

And::And(Base* left, Base* right) : Connector(left, right) {
    this->left = left;
    this->right = right;
}

// set left
void And::setLeft(Base* left) {
    this->left = left;
}

// set right
void And::setRight(Base* right) {
    this->right = right;
}

// checks if the left and right side worked
// if worked then return true
// if didn't work then return false
bool And::execute() {
    if (left->execute()) {
        if (right->execute()) {
            return true;
        }
    // if (left->execute()) {
    //     right->execute();
    // }
        else {
            return false;
        }
    }
    return false;
    // return true;
}