#include "LinkedList.cpp"
class HashTable
{
private:
    const int size = 13;
    LinkedList *const hashArray = new LinkedList[size];

public:
    void add(const Dictionary *const data)
    {
        hashArray[hashFunction(data->key)].push_back(data);
    }
    int hashFunction(std::string const &key) const
    {
        int hash = 0;

        for (int i = 0; i < key.length(); i++)
        {
            hash += key[i];
            if (i == 2)
                break;
        }
        return abs(hash % size);
    }
    bool ifExist(std::string const &key) const
    {
        return hashArray[hashFunction(key)].ifExist(key);
    }
    int getValue(std::string const &key) const
    {
        int state = hashArray[hashFunction(key)].getValue(key);
        return state != -1 ? state : hashArray[hashFunction("O")].getValue("O");
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
