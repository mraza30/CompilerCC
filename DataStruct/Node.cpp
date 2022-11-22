#include "Dictionary.cpp"

struct Node
{
    Dictionary *data;
    Node *left;
    Node *right;
    ~Node()
    {
        delete data;
    }
};