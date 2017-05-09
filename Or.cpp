#include "Or.h"
#include "Connector.h"

// Constructors
Or::Or() : Connector() {}

Or::Or(Base* left, Base* right) : Connector(left, right) {
    this->left = left;
    this->right = right;
}

// set left
void Or::setLeft(Base* left) {
    this->left = left;
}

// set right
void Or::setRight(Base* right) {
    this->right = right;
}

// checks if the left side fails then the right side will execute
// if left side works then return false
// if left side fails then return true
bool Or::execute() {
    if (!(left->execute())) {
        if (right->execute()) {
            return true;
        }
        else {
            return false;
        }
    }
    return false;
}