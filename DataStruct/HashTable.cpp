#include "LinkedList.cpp"
class HashTable
{
private:
    const int size = 13;
    LinkedList *hashArray = new LinkedList[size];

public:
    void add(Dictionary *data)
    {
        int index = hashFunction(data);
        hashArray[index].push_back(data);
    }
    bool ifExist(Dictionary *data) const
    {
        int index = hashFunction(data);
        return hashArray[index].ifExist(data);
    }
    int hashFunction(Dictionary *data) const
    {
        int hash = 0;

        for (int i = 0; i < data->key.length(); i++)
        {
            hash += data->key[i];
            if (i == 2)
                break;
        }
        return hash % size;
    }
    void display() const
    {
        for (int i = 0; i < size; i++)
        {
            hashArray[i].display();
            std::cout << std::endl;
        }
    }
    ~HashTable()
    {
        delete[] hashArray;
    }
};
