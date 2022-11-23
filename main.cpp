#include "Scanner.cpp"
int main()
{
    Scanner s;
    s.readKeyword("keyword.txt");
    // s.displayKeyword();
    s.readDfa("dfa.txt");
    // s.displaySimga();
    s.readInput("input.txt");
}