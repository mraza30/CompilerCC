#include "Node.cpp"
#include <iostream>
class LinkedList
{
private:
    Node *head = nullptr;
    Node *tail = nullptr;

public:
    Node *const create_node(const Dictionary *const data) const
    {
        Node *const new_node = new Node(data);
        new_node->left = new_node->right = nullptr;
        return new_node;
    }
    void push_front(const Dictionary *const data)
    {
        Node *const new_node = create_node(data);
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
        Node *const new_node = create_node(data);
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
        const Node *temp = head;
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
        const Node *temp = head;
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
        const Node *temp = head;
        while (temp)
        {
            std::cout << temp->data->key << ":" << temp->data->value << " -> ";
            temp = temp->right;
        }
    }
    ~LinkedList()
    {
        Node *current = head;
        while (current)
        {
            Node *next = current->right;
            delete current;
            current = next;
        }
        head = tail = nullptr;
    }
};