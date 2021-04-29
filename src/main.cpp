// Функция main для взаимодействия с пользователем
#include <iostream>
#include "lex.h"
#include "synt.cpp"
#define MAX_NAME_LENGTH 1024


using namespace std;
int main ()
{
    Scanner a ("test.txt");
    while (1)
    {
        a.get_lex();
        cerr<<endl;
    }
    Lex l(LEX_BREAK,0);
    cout<< l<<endl;


    cout<<"Hello\n";
}
/*
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
*/