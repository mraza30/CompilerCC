#include <cstring>
#include <string>
struct Dictionary
{
    std::string key;
    int value;
    Dictionary(std::string const &key, const int &value) : key(key), value(value){};
};