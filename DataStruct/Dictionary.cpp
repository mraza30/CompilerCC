#include <string>
#include <iostream>
struct Dictionary
{
    std::string key;
    int value;
    Dictionary(std::string key, int value) : key(key), value(value){};
    void display() const
    {
        std::cout << key << ": " << value;
    }
};