#include "Base.h"
#include "Connector.h"
#include "Parentheses.h"

Parentheses::Parentheses(Base* paren) {
    this->paren = paren;
}

bool Parentheses::execute() {
    return paren->execute();
}