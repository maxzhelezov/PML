// Функция main для взаимодействия с пользователем
#include <iostream>

#include "synt.h"
#include "exec.h"
#define MAX_NAME_LENGTH 1024


using namespace std;
int main (int argc,char * argv[])
{
    int i;
    string initializer;
    if (argc<2 || argc>3)
    {
        cerr<< "Wrong list of arguements ... \"file\" <filename> | \"single\""<<endl;
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
            Parser test(initializer,argv[2]);
            std::vector<Lex>::iterator pa = test.poliz.begin(); 
        cout<<endl<<"Programm has been successfully compiled"<<endl;
	    cout << "POLIZ:\n";
	    i = 0;
            while(pa != test.poliz.end()){
                std::cout << i << ":" << *pa++ << " ";
	    	i++;
	    }
            cout << endl;
            Executer t;
            t.execute(test.poliz);
        }
    }
    catch (Scanner::my_exception &e)
    {
        cerr<<endl<<endl<<e << endl;
        return 1;
    }
   
}
