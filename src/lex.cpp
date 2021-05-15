// Лексический этап 
#include "lex.h"
#include <cstdlib>
#include <set>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <vector>
#include <algorithm>
using namespace std;

#define DBG 0

// Блок методов класса Ident 

Ident::Ident() { 
        declared = false; 
        assigned = false; 
}


bool Ident::operator==( const string& s ) { 
    return name == s; 
}

Ident::Ident ( const string n ) {
    name    = n;
    declared = false; 
    assigned = false;
}

// Getter'ы класса Ident

string Ident::get_name () const { 
    return name; 
}

bool Ident::get_declare () const { 
    return declared; 
}

bool Ident::get_assign () const { 
    return assigned; 
}

int  Ident::get_value () const { 
    return value; 
}

// Setter'ы класса Ident

type_of_lex Ident::get_type () const { 
    return type; 
}

void Ident::put_type ( type_of_lex t ) { 
    type      = t; 
}

void Ident::put_declare () { 
    declared  = true; 
}

void Ident::put_assign () { 
    assigned  = true; 
}

void Ident::put_value( int v ) { 
    value     = v; 
}

// Таблица идентификаторов
std::vector<Ident>       TID;
int put ( const string & buf ) {
    vector<Ident>::iterator k;
 // такой синтаксис в cpp20
    if ( ( k = find( TID.begin(), TID.end(), buf ) ) != TID.end () )
        return k - TID.begin();
    TID.push_back ( Ident(buf) );
    return TID.size () - 1;
}

std::string Lex::get_ident(){
    return TID[this -> get_value()].get_name();
}

// Таблица строк
vector<string> Strtbl;

int put_str ( const string & buf ) {
    vector<string>::iterator k;
 // такой синтаксис в cpp20
    if ( ( k = find( Strtbl.begin(), Strtbl.end(), buf ) ) != Strtbl.end () )
        return k - Strtbl.begin();
    Strtbl.push_back ( string(buf) );
    return Strtbl.size () - 1;
}

std::string Lex::get_string(){
    return Strtbl[this -> get_value()];
}





// Методы класса Lex
Lex::Lex ( int lines, int number ,type_of_lex type , int value ) : 
            lex_line(lines),lex_number(number),
            lex_type (type), lex_value (value)  
{ 

}

Lex::Lex(const Lex & in):
            lex_line(in.get_line()),lex_number(in.get_number()),
            lex_type (in.get_type()), lex_value (in.get_value())  
{

}

// Getter'ы класса Ident
type_of_lex  Lex::get_type () const { 
    return lex_type; 
}

int Lex::get_value () const { 
    return lex_value; 
}

int Lex::get_line() const{
    return lex_line;
}

int Lex::get_number() const{
    return lex_number;
}

// Вывод лексемы, нужен для вывода ошибок на более поздних этапах
ostream & operator<< ( ostream &s, Lex l )
{
    cout << "(" <<  Scanner::TT[l.get_type()] << "," << l.get_value() << ")";
    //cout<<"Type equals "<<Scanner::TT[l.get_type()];
    //cout<<" , value equals "<<l.get_value();
    return s;
}

// Класс exception - конструктор
Scanner::my_exception::my_exception (int line1, int sym1,
        string error_message1,errtype error_type1)
{
    line=line1;
    sym=sym1;
    error_type=error_type1; 
    error_message=error_message1;
}

// Класс exception - вывод в ostream
ostream & operator<< ( ostream &s, Scanner::my_exception e )
{
    switch(e.error_type)
    {
        case Scanner::my_exception::file:
        {
            s<<"Problem connected with file, not code."<<endl;
            s<<"Message: "<<e.error_message<<endl;
            break;
        }
        case Scanner::my_exception::lex:
        {
            s<<"Lex mistake at: "<<endl<<"Line: "<< e.line<<endl;
            s<<"Sym : "<<e.sym<<endl;
            s<<"Message: "<<e.error_message<<endl;
            break;
        }
        case Scanner::my_exception::synt:
        {
            s<<"Synt mistake at: "<<endl<<"Line: "<< e.line<<endl;
            s<<"Sym: "<<e.sym<<endl;
            s<<"Message: "<<e.error_message<<endl;
            break;
        }
        case Scanner::my_exception::exec:
        {
            s<<"Runtime error" << endl;
            s<<e.error_message<<endl;
            break;
        }
 }
    return s;
}

// Три таблицы класса Scanner
const char * Scanner::TD [23] = { 

    "NULL","=", "<", ">" ,"==", "<=" ,">=", "!=", "+" ,"-" ,"*", 
    "/" ,"//" ,"%" ,"**","(" ,")" ,"[" ,"]" ,";", "," ,":" ,"."
};
const char * Scanner::TW [18]={ 
    "NULL" ,  "None" , "True" , "False", "global" ,
    "def", "return" , "while" ,  "for" , "continue" , "pass" , "break", 
    "if" ,"else",  "not" , "and" ,  "in" ,  "or" 

};
//  Соответствующие лексемам слова, нужны для удобного вывода
const char * Scanner::TT []={ 
    "LEX_NULL", "LEX_TW ", "LEX_NONE ", "LEX_TRUE ", "LEX_FALSE ", 
    "LEX_GLOBAL ", "LEX_DEF ", "LEX_RET ", "LEX_WHILE ", "LEX_FOR ",
    "LEX_CONT ", "LEX_PASS ", "LEX_BREAK ", "LEX_IF ", "LEX_ELSE ",
    "LEX_NOT ", "LEX_AND ", "LEX_IN ", "LEX_OR ", "LEX_TD ", "LEX_ASSIGN ",
    "LEX_LSS ", "LEX_GTR ", "LEX_EQ ", "LEX_LEQ ",  "LEX_GEQ ", "LEX_NEQ ",
    "LEX_PLUS ", "LEX_MINUS ", "LEX_TIMES ", "LEX_SLASH ", "LEX_DSLASH ",
    "LEX_PERC ", "LEX_POW ",
    "LEX_RLBRACKET ", "LEX_RRBRACKET ", "LEX_SLBRACKET ", "LEX_SRBRACKET ",   
    "LEX_SEMICOLON ", "LEX_COMMA ", "LEX_COLON ", "LEX_DOT ",
    "LEX_NAME ", "LEX_NUM ", "LEX_STRING ", "LEX_INDENT ", "LEX_DEDENT ", 
    "LEX_NEWLINE ", "LEX_END ",
    "POLIZ_LABEL ", "POLIZ_ADDRESS ", "POLIZ_GO " , "POLIZ_FGO ",
    "POLIZ_LOAD_LOC", "POLIZ_STORE_LOC" , "POLIZ_LOAD_GLOBAL" , "POLIZ_STORE_GLOBAL",
    "POLIZ_CALL",
};

// Конструктор  класса Scanner - открывает файл на чтение и выставляет флаги
// Если prog NULL, то stdin ( 0 )
Scanner::Scanner( const char* prog)
{
    char_left=0;
    eof_flag=false;  
    lvl=0;
    if( prog==NULL)
        fd=0;
    else
        fd=open(prog,O_RDONLY);
    if(fd==-1)
    {
        throw Scanner::my_exception(0,0,
                    "Can't open file",
                    Scanner::my_exception::file);
    }
}

// Деструктор - только закрывает файл
Scanner::~Scanner()
{
    close (fd);
}

// Метод поиска строки buf в List
// Нужен для определения лексемы по строке 
int look ( const string buf, const char ** list ) {
    int i = 0;
    while ( list[i] ) {
        if ( buf == list[i] )
            return i;
        ++i;
    }
    return 0;
}

// Метод getc :
// Заполняет низкоуровневый буффер и выдаёт символ из него.
void Scanner::getc()
{
    static int char_scanned;
    if(eof_flag)
    {
        c=EOF;
        return;
    }
    if(char_left==0 && eof_flag==false)
    {
        if (eof_flag)
        {
            c=EOF;
            return;
        } 
        char_left=read(fd,this->buf,BUFSIZ);
        char_scanned=char_left;
        if(char_scanned<0)
        {
            throw Scanner::my_exception(0,0,
                    "Problem when reading from file",
                    Scanner::my_exception::file);
        }
        if(char_scanned==0)
        {
            eof_flag=true;
            c= EOF;
            return;
        }
    }
    else if(eof_flag&& char_left==0)
    {
        eof_flag=true;
        c= EOF;
        return;
    }
    c=this->buf[char_scanned-char_left];
    char_left--;
}

bool isdigit(char c)
{
    switch (c)
    {
        case '0':case '1': case '2': case '3': case '4':
        case '5':case '6': case '7': case '8': case '9':
        return true;
        default:return false;
    }
}

// Метод, возвращающий лексему в соответствии с имеющимся автоматом.

Lex Scanner::get_lex () {
    int  d = 0,i, j,strlength;
    static int dedent_left=0;    // Кол-во набраных Dedent
/*
    Поясним необходимость данной переменной на следующем примере
    for i in 100:
        for j in 10:
            c++
    print(c)
    
    После c++ пришло 2 отступа вниз, это не ошибка. 
    Нужно вернуть 2 отступа. Разумеется при двух разных (последовательных) 
    обращениях к методу.
    Сделать это можно лишь при помощи данной переменной.
*/
    // Следующие 4 переменные нужны для объяснения ошибок пользователю 
    static int char_in_str=0;    // Номер символа в строке
    static int number     =0;    // Номер лексемы
    static int lines      =1;    // Номер строки
    static bool newline_flag=false;
    int  first_char;
    string  charbuf;     // Буфер для заполнения имени переменной.
    state   curstate ;
    if(dedent_left>0)
    {
        lvl--;
        dedent_left--;
        number++;
        cerr<<TT[LEX_DEDENT]<<"\t";
        return Lex(lines, (number-1)*4+1, LEX_DEDENT);
    }
    first_char=char_in_str+1;
    curstate = newline_flag?IND:H ;
    do
    {
        getc();
        char_in_str++;
        switch(curstate)
        {
            case H:
            {
                if (c=='\r'||c==' '||c=='\t')//DONE
                {
                    ;//nothing
                    if(c=='\t')
                    char_in_str+=3;
                }
                else if(c=='\n')//DONE
                {
                    newline_flag=true;
                    char_in_str=0;
                    first_char=0;
                    number=0;
                    lines++;
                    cerr<<TT[LEX_NEWLINE]<<"\t";
                    return Lex(lines, first_char, LEX_NEWLINE);
                }
                else if(c=='"')
                {
                    strlength=0;
                    curstate=STRING;
                }
                else if(isdigit(c)) //NUMBER //DONE
                {
                    d+=c-'0';
                    curstate=NUMBER;
                }
                else if(c=='#') //COMM //DONE
                {
                    curstate=COMM;
                }
                else if(c=='='||c=='<'||c=='>')//COMP //DONE
                {
                    charbuf.push_back (c);
                    curstate=COMP;
                }
                else if(c=='/') //DIV 
                {
                    charbuf.push_back (c);
                    curstate=DIV;
                }
                else if(c=='*') 
                {
                    charbuf.push_back (c);
                    curstate=MULP;
                }
                //NEQ
                else if(c=='!')
                {
                    charbuf.push_back (c);
                    curstate=NEQ;
                }
                //DEL
                else if(c=='+'||c=='-'||c=='%'||c=='['||c==']'||c=='('||
                            c==')'||c=='.'||c==':'||c==',')
                {
                    charbuf.push_back (c);
                    curstate=DEL;
                }
                //END
                else if(c==EOF) //DONE
                {
                    number++;
                    return Lex(lines,first_char,LEX_END);
                }
                // Остались только char
                else if( isalpha(c)||c=='_')
                {
                    charbuf.push_back (c);
                    curstate=NAME;
                }
                else
                    throw Scanner::my_exception(lines,char_in_str,
                                "Wrong char in lexem ",
                                Scanner::my_exception::lex);
                break;

            }
            case STRING:
            {
                if ( c != '"' ) {
                    if(c=='\n'||c==EOF)
                    {
                        throw Scanner::my_exception(lines,char_in_str,
                                "String : unexpected end of string",
                                Scanner::my_exception::lex);
                    }
                    strlength++;
                    charbuf.push_back (c); 
                }
                else
                {
                    if(strlength==0)
                    {
                        throw Scanner::my_exception(lines,char_in_str,
                                "String : empty string",
                                Scanner::my_exception::lex);
                    }
                    cerr<<TT[LEX_STRING]<<"\t"<<charbuf;
                    j   = put_str ( charbuf );
                    number++;
                    return Lex( lines,first_char ,LEX_STRING, j );
                }
                break;
            }
            case NAME:
            {
                if (isalpha (c) || isdigit (c) ||c=='_') {
                    charbuf.push_back (c); 
                }
                else {
                    // ~ungetc
                    char_left++;
                    char_in_str--;
                    if ( (j = look ( charbuf, TW) ) ) 
                    {
                        cerr<<TT[(type_of_lex) ( j + (int) LEX_TW )]<<"\t";
                        number++;
                        return Lex( lines,first_char ,(type_of_lex) (j+(int) LEX_TW), j );
                    }
                    else 
                    {
                        j   = put ( charbuf );
                        cerr<<TT[LEX_NAME]<<"\t";
                        number++;
                        return Lex( lines,first_char,LEX_NAME, j );
                    }
                }
                break;
            }
            case NUMBER:
            {
                if ( isdigit(c)) {
                    d = d * 10 + ( c - '0' );
                }
                else {
                    if(isalpha(c))
                        throw Scanner::my_exception(lines,char_in_str,
                            "Wrong lex identifier ",
                            Scanner::my_exception::lex);
                    // ~ungetc
                    char_left++; 
                    char_in_str--;
                    number++;
                    cerr<<TT[LEX_NUM]<<"\t";
                    return Lex( lines,first_char ,LEX_NUM, d );
                }
                break;
            }
            case COMM://DONE
            {
                while(c!='\n'&&c!=EOF)
                    getc();
                if(c==EOF)
                {
                    number++;
                    return Lex(lines,first_char,LEX_END);
                }
                else if (number > 0)// нужно вернуть /n //
                {//
                    newline_flag=true;//
                    char_in_str=0;//
                    number=0;//
                    lines++;//
                    cerr<<TT[LEX_NEWLINE]<<"\t";//
                    return Lex(lines,first_char, LEX_NEWLINE);//
                }//
                  // Иначе просто "Проглотить" строку
                curstate=IND;//
                break;//
                // return происходит в лиюом случае
            }//
            case COMP:
            {
                if(c== '=' )
                {
                    charbuf.push_back ( c );
                    j   = look( charbuf, TD );
                    cerr<<TT[(type_of_lex) ( j + (int) LEX_TD )]<<"\t";
                    number++;
                    return Lex( lines,first_char ,(type_of_lex) ( j + (int) LEX_TD ), j );
                }
                else 
                {
                    // ~ungetc
                    char_left++;
                    char_in_str--;
                    number++;
                    j   = look ( charbuf, TD );
                    cerr<<TT[(type_of_lex) ( j + (int) LEX_TD )]<<"\t";
                    return Lex( lines,first_char ,(type_of_lex) ( j + (int) LEX_TD ), j );
                }
                break;
            }
            case DIV://DONE
            {
                if(c== '/' )
                {
                    charbuf.push_back ( c );
                    j   = look( charbuf, TD );
                    number++;
                    cerr<<TT[(type_of_lex) ( j + (int) LEX_TD )]<<"\t";
                    return Lex( lines,first_char ,(type_of_lex) ( j + (int) LEX_TD ), j );
                }
                else 
                {
                    // ~ungetc
                    char_left++;
                    char_in_str--;
                    number++;
                    j   = look ( charbuf, TD );
                    cerr<<TT[(type_of_lex) ( j + (int) LEX_TD )]<<"\t";
                    return Lex( lines,first_char ,(type_of_lex) ( j + (int) LEX_TD ), j );
                }
            }
            case MULP://DONE
            {
                 if(c== '*' )
                {
                    charbuf.push_back ( c );
                    j   = look( charbuf, TD );
                    number++;
                    cerr<<TT[(type_of_lex) ( j + (int) LEX_TD )]<<"\t";
                    return Lex( lines,first_char, (type_of_lex) ( j + (int) LEX_TD ), j );
                }
                else 
                {
                    // ~ungetc
                    char_left++;
                    char_in_str--;
                    number++;
                    j   = look ( charbuf, TD );
                    cerr<<TT[(type_of_lex) ( j + (int) LEX_TD )];
                    return Lex( lines,first_char, (type_of_lex) ( j + (int) LEX_TD ), j );
                }
                break;
            }
            case NEQ://DONE
            {
                if(c == '=' )
                {
                    charbuf.push_back ( c );
                    j   = look( charbuf, TD );
                    number++;
                    cerr<<TT[(type_of_lex) ( j + (int) LEX_TD )]<<"\t";
                    return Lex( lines,first_char, (type_of_lex) ( j + (int) LEX_TD ), j );
                }
                else
                {
                    throw Scanner::my_exception(lines,char_in_str,
                                "No = after !",
                                Scanner::my_exception::lex);
                }
                break;
            }
            case DEL: //DONE
            {
                // ~ungetc
                char_left++;
                char_in_str--;
                number++;
                j   = look( charbuf, TD );
                cerr<<TT[(type_of_lex) ( j + (int) LEX_TD )]<<"\t";
                return Lex( lines,first_char ,(type_of_lex) ( j + (int) LEX_TD ), j );
                break;
            }
            case IND:
            {
                int curlvl=0;
                while(c==' ')
                {
                    curlvl++;
                    for(i=0;i<3;i++)
                    {
                        getc();
                        char_in_str++;
                        if(c!=' ')
                        {
                            if (c=='#')//
                            {//
                                while(c!='\n'&&c!=EOF)//
                                    getc();//
                                if(c==EOF)//
                                {//
                                    number++;//
                                    return Lex(lines,first_char,LEX_END);//
                                }//
                                curlvl=0;//
                                char_in_str=0;//
                                first_char=1;
                                number=0;//
                                lines++;//
                                c='#';  // 
                                break;  // 
                            }    ///
                            else //
                                throw Scanner::my_exception(lines,char_in_str,
                                "Wrong INDENT size",
                                Scanner::my_exception::lex);
                        }
                    }
                    if(c=='#')   //
                    {            //
                        getc();  //
                        break;   //
                    }            //
                    getc();
                    char_in_str++;
                }
                // ~ungetc
                char_left++; 
                char_in_str--;
                if(curlvl>lvl+1)
                {
                    throw Scanner::my_exception(lines,char_in_str,
                                "INDENT is too big",
                                Scanner::my_exception::lex);
                }
                if (curlvl==lvl+1)
                {
                    cerr<<TT[LEX_INDENT]<<"\t";
                    lvl++;
                    number++;
                    newline_flag=false;
                    return Lex(lines,(curlvl-1)*4+1,LEX_INDENT);
                }
                else if (curlvl<lvl)
                {
                    cerr<<TT[LEX_DEDENT]<<"\t";
                    lvl--;
                    number++;
                    dedent_left=lvl-curlvl;
                    newline_flag=false;
                    return Lex(lines,(number-1)*4+1,LEX_DEDENT);;
                }
                else if(newline_flag)
                {
                    if(c==EOF)
                    {

                        number++;
                        return Lex(lines,first_char,LEX_END);
                    }
                    curstate=H;
                    newline_flag=false;
                    first_char=char_in_str+1;
                    break;
                }
                else if(curlvl==lvl)
                {
                    curstate=H;
                    break;
                }
                else 
                {
                    string tempstr;
                    tempstr=" Wrong number of indents: current level is ";
                    /*tempstr=tempstr.append(std::to_string(curlvl));
                    tempstr=tempstr.append(" actual level is ");
                    tempstr=tempstr.append(std::to_string(lvl));*/
                    throw Scanner::my_exception(lines,char_in_str,
                                tempstr,
                                Scanner::my_exception::lex);
                    //cerr<<" Wrong number of indents: current level is ";
                    //cerr<<curlvl<<" actual level is "<<lvl<<endl;
                    //cerr<<endl<<char_in_str<<lines<<endl;
                    exit(0);
                }
                if(c==EOF)
                {

                    number++;
                    return Lex(lines, first_char,LEX_END);
                }
                break;
            } //end of IND
        } // end of switch
    } //end of while
    while(1) ;
}

