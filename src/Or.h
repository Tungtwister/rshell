#ifndef OR_H
#define OR_H

class Or : public Connector
{
    private:
        Base* left;
        Base* right;
    public:
        Or();
        Or(Base* left, Base* right);
        void setLeft(Base* left);
        void setRight(Base* right);
        bool execute();
};

#endif
