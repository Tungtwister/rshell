#ifndef PARENTHESES_H
#define PARENTHESES_H

class Parentheses : public Connector {
    private:
        Base* paren;
    public:
        Parentheses(Base*);
        bool execute();
};

#endif