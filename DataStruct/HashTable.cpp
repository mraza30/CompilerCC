#include "LinkedList.cpp"
class HashTable
{
private:
    const int size = 13;
    LinkedList *const hashArray = new LinkedList[size];

public:
    void add(const Dictionary *const data)
    {
        int index = hashFunction(data->key);
        hashArray[index].push_back(data);
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
        int index = hashFunction(key);
        return hashArray[index].ifExist(key);
    }
    int getValue(std::string const &key) const
    {
        int index = hashFunction(key);
        return hashArray[index].getValue(key);
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
