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
        return abs((key[0] + key.length()) % size);
    }
    bool ifExist(std::string const &key) const
    {
        return hashArray[hashFunction(key)].ifExist(key);
    }
    int getValue(std::string const &key) const
    {
        return hashArray[hashFunction(key)].getValue(key);
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
