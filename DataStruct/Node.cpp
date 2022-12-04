#include "Dictionary.cpp"

struct Node
{
    const Dictionary *const data;
    Node *left;
    Node *right;
    Node(const Dictionary *const data) : data(data){};
};