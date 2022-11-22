#include "Node.cpp"

class LinkedList
{
private:
    Node *head = nullptr;
    Node *tail = nullptr;

public:
    Node *create_node(Dictionary *data) const
    {
        Node *new_node = new Node();
        new_node->data = data;
        new_node->left = new_node->right = nullptr;
        return new_node;
    }
    void push_front(Dictionary *data)
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
    void push_back(Dictionary *data)
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
    bool ifExist(Dictionary *data) const
    {
        Node *temp = head;
        while (temp)
        {
            if (data->key == temp->data->key)
                return true;
        }
        return false;
    }
    bool ifExist(Dictionary *data) const
    {
        Node *temp = head;
        while (temp)
        {
            if (data->key == temp->data->key)
                return true;
        }
        return false;
    }
    void display() const
    {
        Node *temp = head;
        while (temp)
        {
            temp->data->display();
            std::cout << " => ";
            temp = temp->right;
        }
    }
};