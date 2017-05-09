#ifndef AND_H
#define AND_H

class And : public Connector
{
    private:
        Base* left;
        Base* right;
    public:
        And();
        And(Base* left, Base* right);
        void setLeft(Base* left);
        void setRight(Base* right);
        bool execute();
};

#endif