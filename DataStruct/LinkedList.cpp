#include "Node.cpp"
#include <iostream>
class LinkedList
{
private:
    Node *head = nullptr;
    Node *tail = nullptr;

public:
    Node *create_node(const Dictionary *const data) const
    {
        Node *new_node = new Node();
        new_node->data = data;
        new_node->left = new_node->right = nullptr;
        return new_node;
    }
    void push_front(const Dictionary *const data)
    {
        Node *new_node = create_node(data);
        if (!head)
        {
            head = tail = new_node;
        }
        else
        {
            head->left = new_node;
            new_node->right = head;
            head = new_node;
        }
    }
    void push_back(const Dictionary *const data)
    {
        Node *new_node = create_node(data);
        if (!head)
        {
            head = tail = new_node;
        }
        else
        {
            tail->right = new_node;
            new_node->left = tail;
            tail = new_node;
        }
    }
    bool ifExist(std::string const &key) const
    {
        Node *temp = head;
        while (temp)
        {
            if (key == temp->data->key)
                return true;
            temp = temp->right;
        }
        return false;
    }
    int getValue(std::string const &key) const
    {
        Node *temp = head;
        while (temp)
        {
            if (key == temp->data->key)
                return temp->data->value;
            temp = temp->right;
        }
        return -1;
    }
    void display() const
    {
        Node *temp = head;
        while (temp)
        {
            std::cout << temp->data->key << ":" << temp->data->value << " -> ";
            temp = temp->right;
        }
    }
};