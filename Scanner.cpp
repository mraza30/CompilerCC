#include "DataStruct/HashTable.cpp"
#include <cstring>
#include <fstream>
#include <vector>
class Scanner
{
private:
    HashTable keyword;
    HashTable sigma;
    std::vector<std::vector<int>> dfa;

public:
    void readKeyword(std::string const &filename)
    {
        std::ifstream file(filename);
        if (!file.is_open())
        {
            std::cout << "Error opening file " << filename << std::endl;
            exit(0);
        }
        std::string word;
        int value = 0;
        while (std::getline(file, word))
        {
            keyword.add(new Dictionary(word, value));
            value++;
        }
    }

    void readDfa(std::string const &filename)
    {
        std::ifstream file(filename);
        if (!file.is_open())
        {
            std::cout << "Error opening file " << filename << std::endl;
            exit(0);
        }
        std::string line;
        int row = 0;
        while (std::getline(file, line))
        {
            int col = 0;
            std::vector<std::string> words;
            tokenize(line, "\t", words);
            for (auto &word : words)
            {
                if (row == 0)
                {
                    sigma.add(new Dictionary(word, col));
                }
                else
                {
                    dfa.resize(row + 1);
                    dfa.at(row - 1).push_back(atoi(word.c_str()));
                    // std::cout << dfa.at(row - 1).at(col) << " ";
                }
                col++;
            }
            // std::cout << '\n';
            row++;
        }
    }

    void readInput(std::string const &filename)
    {
        std::ifstream input(filename);
        if (!input.is_open())
        {
            std::cout << "Error opening file " << filename << std::endl;
            exit(0);
        }
        std::string line;
        while (std::getline(input, line))
        {
        }
    }

    int getNextState(char const &Char, int const &State)
    {
    }

    void displaySimga() const
    {
        sigma.display();
    }
    void displayKeyword() const
    {
        keyword.display();
    }

    bool isNumber(char const &Char) const
    {
        char numbers[] = {"0123456789"};
        for (int i = 0; i < sizeof(numbers) / sizeof(numbers[0]); i++)
        {
            if (Char == numbers[i])
            {
                return true;
            }
        }
        return false;
    }
    bool isLetter(char const &Char) const
    {
        if ((Char >= 'A' && Char <= 'Z') || (Char >= 'a' && Char <= 'z'))
        {
            return true;
        }
        return false;
    }

    void tokenize(std::string const &str, const char *delim,
                  std::vector<std::string> &out)
    {
        char *token = strtok(const_cast<char *>(str.c_str()), delim);
        while (token != nullptr)
        {
            out.push_back(std::string(token));
            token = strtok(nullptr, delim);
        }
    }
};
