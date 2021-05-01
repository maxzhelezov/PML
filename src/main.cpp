// Функция main для взаимодействия с пользователем
#include <iostream>

#include "synt.h"
#define MAX_NAME_LENGTH 1024


using namespace std;
int main (int argc,char * argv[])
{
    
    string initializer;
    if (argc<2 || argc>3)
    {
        cerr<< "Wrong list of arguements ... <file> \"filename\"| single"<<endl;
        return 0;
    }
    initializer=argv[1];
    try
    {
        if( argc==2 )
        {
            Parser ( initializer,NULL );
        }
        else if (argc==3)
        {
            Parser (initializer,argv[2]);
        }
    }
    catch (Scanner::my_exception &e)
    {
        cerr<<endl<<endl<<e;
        return 1;
    }
    cout<<endl<<"Programm has been successfully compiled"<<endl;
    //return 0;
    //cout<<Scanner::my_exception(1,"name","message",Scanner::my_exception::lex);









   /*
    Scanner a ("test.txt");
    while (1)
    {
        a.get_lex();
        cerr<<endl;
    }
    Lex l(LEX_BREAK,0);
    cout<< l<<endl;
    */
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