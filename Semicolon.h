#ifndef SEMICOLON_H
#define SEMICOLON_H

class Semicolon : public Connector
{
    private:
        Base* left;
        Base* right;
    public:
        Semicolon();
        Semicolon(Base* left, Base* right);
        void setLeft(Base* left);
        void setRight(Base* right);
        bool execute();
};

#endif