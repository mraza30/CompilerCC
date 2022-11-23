#include "DataStruct/HashTable.cpp"
#include <fstream>
#include <vector>
#include <queue>
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
        std::ofstream token("token.txt");
        std::ofstream error("error.txt");
        std::ifstream input(filename);
        if (!input.is_open())
        {
            std::cout << "Error opening file " << filename << std::endl;
            exit(0);
        }
        std::string line;
        while (std::getline(input, line))
        {
            line.push_back('\n');

            std::queue<char> buffer;
            std::string word;

            int state = 0;
            for (int i = 0; i < line.length(); i++)
            {
                buffer.push(line[i]);
                getNextState(line[i], state);
                if (state == 16)
                {
                    getWord(buffer, word);
                    if (keyword.ifExist(word))
                    {
                        token << "<keyword, " << word << ">\n";
                    }
                    else
                    {
                        token << "<identifier, " << word << ">\n";
                    }
                    i--;
                    state = 0;
                    word.clear();
                }
                else if (state == 18)
                {
                    getWord(buffer, word);
                    if (keyword.ifExist(word))
                    {
                        token << "<keyword, " << word << ">\n";
                    }
                    else
                    {
                        error << "<error, " << word << ">\n";
                    }
                    i--;
                    state = 0;
                    word.clear();
                }
                else if (state == 17)
                {
                    getWord(buffer, word);
                    token << "<number, " << word << ">\n";
                    i--;
                    state = 0;
                    word.clear();
                }
                else if (state == 19)
                {
                    getWord(buffer, word, false);
                    token << "<operator, " << word << ">\n";
                    state = 0;
                    word.clear();
                }
                else if (state == 20)
                {
                    getWord(buffer, word);
                    token << "<operator, " << word << ">\n";
                    i--;
                    state = 0;
                    word.clear();
                }
                else if (state == 21)
                {
                    getWord(buffer, word, false);
                    token << "<punctuation, " << word << ">\n";
                    state = 0;
                    word.clear();
                }
                else if (state == 22)
                {
                    getWord(buffer, word);
                    token << "<punctuation, " << word << ">\n";
                    i--;
                    state = 0;
                    word.clear();
                }
                else if (state == 23)
                {
                    getWord(buffer, word, false);
                    if (!std::isspace(word[0]))
                        error << "<error, " << word << ">\n";
                    state = 0;
                    word.clear();
                }
                else if (state == 24)
                {
                    getWord(buffer, word);
                    if (!std::isspace(word[0]))
                        error << "<error, " << word << ">\n";
                    i--;
                    state = 0;
                    word.clear();
                }
            }
        }
    }

    void getWord(std::queue<char> &Queue, std::string &word, bool clear = true) const
    {
        int size = Queue.size();
        if (clear)
            size--;
        int i = 0;
        for (; i < size; i++)
        {
            word.push_back(Queue.front());
            Queue.pop();
        }
        if (clear)
            Queue.pop();
    }

    void getNextState(const char &Char, int &state) const
    {
        if (isLetter(Char))
        {
            state = dfa[state][sigma.getValue("L")];
        }
        else if (isNumber(Char))
        {
            state = dfa[state][sigma.getValue("N")];
        }
        else
        {
            state = dfa[state][sigma.getValue(std::string(1, Char))];
        }
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
