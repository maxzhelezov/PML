// Функция main для взаимодействия с пользователем
#include <iostream>
#include "lex.cpp"
#include "synt.cpp"
#define MAX_NAME_LENGTH 1024


using namespace std;

int main()
{
    char filename [MAX_NAME_LENGTH];
    while (1)
    { 
        cin>>filename;
        try
        {
            lex_step();
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }

    }
}
