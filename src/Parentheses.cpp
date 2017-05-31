#include "Connector.h"
#include "Parentheses.h"

Parentheses::Parentheses(Base* paren) {}

bool Parentheses::execute() {
    return paren->execute();
}