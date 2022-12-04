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
            exit(1);
        }
        std::string word;
        int value = 0;
        while (file >> word)
        {
            keyword.add(new Dictionary(word, value));
            value++;
        }
        file.close();
    }

    void readDfa(std::string const &filename)
    {
        std::ifstream file(filename);
        if (!file.is_open())
        {
            std::cout << "Error opening file " << filename << std::endl;
            exit(1);
        }
        std::string line;
        unsigned int row = 0;
        while (std::getline(file, line))
        {
            unsigned int col = 0;
            std::vector<std::string> words;
            tokenize(line, "\t", words);
            for (auto &word : words)
            {
                if (row == 0)
                    sigma.add(new Dictionary(word, col));
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
        file.close();
    }

    void readInput(std::string const &filename)
    {
        std::ofstream token("token.txt");
        std::ofstream error("error.txt");
        std::ifstream input(filename);
        if (!input.is_open())
        {
            std::cout << "Error opening file " << filename << std::endl;
            exit(1);
        }
        std::string line;
        while (std::getline(input, line))
        {
            line.push_back('\n');

            std::queue<char> buffer;
            std::string word;

            unsigned int state = 0;
            for (int i = 0; i < line.length(); i++)
            {
                buffer.push(line[i]);
                getNextState(line[i], state);
                if (state == 16)
                {
                    getWord(buffer, word, state, i);
                    keyword.ifExist(word)
                        ? token << "<keyword, " << word << ">\n"
                        : token << "<identifier, " << word << ">\n";
                }
                else if (state == 18)
                {
                    getWord(buffer, word, state, i);
                    keyword.ifExist(word)
                        ? token << "<keyword, " << word << ">\n"
                        : error << "<error, " << word << ">\n";
                }
                else if (state == 17)
                {
                    getWord(buffer, word, state, i);
                    token << "<number, " << word << ">\n";
                }
                else if (state == 19)
                {
                    getWord(buffer, word, state, i, false);
                    token << "<operator, " << word << ">\n";
                }
                else if (state == 20)
                {
                    getWord(buffer, word, state, i);
                    token << "<operator, " << word << ">\n";
                }
                else if (state == 21)
                {
                    getWord(buffer, word, state, i, false);
                    token << "<punctuation, " << word << ">\n";
                }
                else if (state == 22)
                {
                    getWord(buffer, word, state, i);
                    token << "<punctuation, " << word << ">\n";
                }
                else if (state == 23)
                {
                    getWord(buffer, word, state, i, false);
                    if (!std::isspace(word[0]))
                        error << "<error, " << word << ">\n";
                }
                else if (state == 24)
                {
                    getWord(buffer, word, state, i);
                    if (!std::isspace(word[0]))
                        error << "<error, " << word << ">\n";
                }
                word.clear();
            }
        }
        input.close();
        token.close();
        error.close();
    }

    void getWord(std::queue<char> &Queue, std::string &word,
                 unsigned int &state, int &index, bool clear = true) const
    {
        int i = clear ? 1 : 0;
        int size = Queue.size();
        for (; i < size; i++)
        {
            word.push_back(Queue.front());
            Queue.pop();
        }
        if (clear)
        {
            Queue.pop();
            index--;
        }
        state = 0;
    }

    void getNextState(const char &Char, unsigned int &state) const
    {
        if (std::isalpha(Char))
        {
            state = dfa[state][sigma.getValue("L")];
        }
        else if (std::isdigit(Char))
        {
            state = dfa[state][sigma.getValue("N")];
        }
        else
        {
            int index = sigma.getValue(std::string(1, Char));
            state = dfa[state][index != -1 ? index : sigma.getValue("O")];
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

    void tokenize(std::string const &str, const char *delim,
                  std::vector<std::string> &out) const
    {
        char *token = strtok(const_cast<char *>(str.c_str()), delim);
        while (token != nullptr)
        {
            out.push_back(std::string(token));
            token = strtok(nullptr, delim);
        }
    }
};
