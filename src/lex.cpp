// Лексический этап 
#include "lex.h"
#include <cstdlib>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <algorithm>

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

string Ident::get_name () const { 
    return name; 
}
bool Ident::get_declare () const { 
    return declared; 
}
void Ident::put_declare () { 
    declared  = true; 
}
type_of_lex Ident::get_type () const { 
    return type; 
}
void Ident::put_type ( type_of_lex t ) { 
    type      = t; 
}
bool Ident::get_assign () const { 
    return assigned; 
}
void Ident::put_assign () { 
    assigned  = true; 
}
int  Ident::get_value () const { 
    return value; 
}
void Ident::put_value( int v ) { 
    value     = v; 
}
int put ( const string & buf ) {
    vector<Ident>::iterator k;
 // такой синтаксис в cpp20
    if ( ( k = find( TID.begin(), TID.end(), buf ) ) != TID.end () )
        return k - TID.begin();
    TID.push_back ( Ident(buf) );
    return TID.size () - 1;
}

Lex::Lex ( type_of_lex type , int value )
                : lex_type (type), lex_value (value)  { }

type_of_lex  Lex::get_type () const { 
    return lex_type; 
}

int Lex::get_value () const { 
    return lex_value; 
}
ostream & operator<< ( ostream &s, Lex l )
{
    cout<<"Type equals "<<Scanner::TT[l.get_type()]<<" , value equals "<<l.get_value();
    return s;
}

/*void lex_step ()
{
    ;
}
void test()
{
    
}
char gc()
{
    return 'a';
}*/
/*bool ischar(char c)
{
    switch (c)
    {
case 'a':case 'b': case 'c': case 'd': case 'e':
case 'f':case 'g': case 'h': case 'i': case 'j':
case 'k':case 'l': case 'm': case 'n': case 'o':
case 'p':case 'q': case 'r': case 's': case 't':
case 'u':case 'v': case 'w': case 'x': case 'y':
case 'z':
case 'а':case 'б':case 'в': case 'г': case 'д': case 'е':
case 'ж':case 'з':case 'и': case 'й': case 'к': case 'л':
//case 'а':case 'a':case 'b': case 'c': case 'd': case 'e':
//case 'а':case 'a':case 'b': case 'c': case 'd': case 'e':
//case 'а':case 'a':case 'b': case 'c': case 'd': case 'e':
//case 'а':case 'a':case 'b': case 'c': case 'd': case 'e':

return true;

default: return false;

    }
}*/
const char * Scanner::TD [22] = { 

    "NULL","=", "<", ">" ,"==", "<=" ,">=", "!=", "+" ,"-" ,"*", 
//   0      1    2    2+1   4    5     6     7     8    9    10  
    "/" ,"//" ,"%" ,"**","(" ,")" ,"[" ,"]" ,";" "," ,":" ,"."
//   11   12    13    14  15   16   17   18  19   20   21   22
};
const char * Scanner::TW [18]={ 
    "NULL" ,  "None" , "True" , "False", "global" ,
//   0         1        2        3        4
    "def", "return" , "while" ,  "for" , "continue" , "pass" , "break" 
//   5      6          7          8       9            10       11
    "if" ,"else",  "not" , "and" ,  "in" ,  "or" 
//   12    13       14      15       16      17

};
const char * Scanner::TT [POLIZ_FGO +1]={
//  Соответствующие лексемам слова, нужны для удобного вывода 
    "LEX_NULL", "LEX_TW", "LEX_NONE", "LEX_TRUE", "LEX_FALSE", "LEX_GLOBAL",
    "LEX_DEF", "LEX_RET", "LEX_WHILE", "LEX_FOR",  "LEX_CONT", "LEX_PASS", "LEX_BREAK",  
    "LEX_IF", "LEX_ELSE",  "LEX_NOT", "LEX_AND", "LEX_IN", "LEX_OR",                                 
    "LEX_TD",
    "LEX_ASSIGN", "LEX_LSS", "LEX_GTR", "LEX_EQ", "LEX_LEQ",  "LEX_GEQ", "LEX_NEQ",
    "LEX_PLUS", "LEX_MINUS", "LEX_TIMES", "LEX_SLASH", "LEX_DSLASH", "LEX_PERC", "LEX_POW",
    "LEX_RLBRACKET", "LEX_RRBRACKET", "LEX_SLBRACKET", "LEX_SRBRACKET",   
    "LEX_SEMICOLON", "LEX_COMMA", "LEX_COLON", "LEX_DOT",
    "LEX_NAME", "LEX_NUM", "LEX_STRING", "LEX_INDENT", "LEX_DEDENT", 
    "LEX_NEWLINE", "LEX_END",
    "POLIZ_LABEL", "POLIZ_ADDRESS", "POLIZ_GO", "POLIZ_FGO"                                                                                 
};
Scanner::Scanner( const char* prog)
{
    char_left=0;
    eof_flag=false;  
    lvl=0;
    fd=open(prog,O_RDONLY);
    if(fd==-1)
    {
        //throw Error();
    }

}
Scanner::~Scanner()
{
    close (fd);
}
int look ( const string buf, const char ** list ) {
    int i = 0;
    while ( list[i] ) {
        if ( buf == list[i] )
            return i;
        ++i;
    }
    return 0;
}
void Scanner::getc()
{
    static int char_scanned;
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
            //throw Error();
            throw 1;
            cerr<<"Oops"<<__FILE__<<__LINE__<<endl;
        }
        if(char_scanned==0)
        {
            eof_flag=true;
            c= EOF;
            return;
        }
        if(char_scanned<BUFSIZ)
        {
            eof_flag=true;
        }
    }
    else if(eof_flag&& char_left==0)
    {
        eof_flag=true;
        c= EOF;
        cerr<<" char is EOF"<<c<<endl;
        return;
    }
    c=this->buf[char_scanned-char_left];
    
    cerr<<" char is "<<c<<endl;
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
bool isspace(char c)
{
    switch (c)
    {
        case '\r':case ' ': case '\t': //case '3': case '4':
        //case '5':case '6': case '7': case '8': case '9':
        return true;
        default:return false;
    }
}

Lex Scanner::get_lex () {
    int space,  d,i, j;
    string  charbuf;
    Lex l; // Под снос
    state   curstate = H;
    do
    {
        getc();
        switch(curstate)
        {
            case H:
            {
                if (c=='\r'||c==' '||c=='\t')//DONE
                {
                    ;//nothing
                }
                else if(c=='\n')//DONE
                {
                    curstate=IND;
                }
                else if(c=='"')
                {
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
                    cout<< "Success"<<endl;
                    exit(0);
                }
                // Остались только char
                else 
                {
                    charbuf.push_back (c);
                    curstate=NAME;
                }
                break;

            }
            case STRING:
            {
                if ( c != '"' ) {
                    if(c=='\n'||c==EOF)
                    {
                        cerr<<" Lex mistake:"<< " String unexpected end of string ";
                        cerr<<endl<<__FILE__<<__LINE__<<endl;
                        exit(0);
                    }
                    charbuf.push_back (c); 
                }
                else
                {
                    cerr<<TT[LEX_STRING]<<"  "<<charbuf;
                    j   = put ( charbuf );
                    return Lex ( LEX_STRING, j );
                }
                break;
            }
            case NAME:
            {
                if ( isalpha (c) || isdigit (c) ) {
                    charbuf.push_back (c); 
                }
                else {
                    char_left++;
                    //cerr<<charbuf<<endl;
                    if ( (j = look ( charbuf, TW) ) ) 
                    {
                        cerr<<TT[(type_of_lex) ( j + (int) LEX_TW )];
                        return Lex ( (type_of_lex) (j+(int) LEX_TW), j );
                    }
                    else 
                    {
                        j   = put ( charbuf );
                        cerr<<TT[LEX_NAME];
                        return Lex (LEX_NAME, j );
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
                    char_left++; // Аналог ungetc в моей низкоуровневой буфферизации
                    cerr<<TT[LEX_NUM];
                    return Lex ( LEX_NUM, d );
                }
                break;
            }
            case COMM://DONE
            {
                while(c!='\n'&&c!=EOF)
                    getc();
                if(c==EOF)
                {
                    cout<< "Success"<<endl;
                    exit(0);
                }
                char_left++;
                curstate=H;
                break;
            }
            case COMP:
            {
                if(c== '=' )
                {
                    charbuf.push_back ( c );
                    j   = look( charbuf, TD );
                    cerr<<TT[(type_of_lex) ( j + (int) LEX_TD )];
                    return Lex ( (type_of_lex) ( j + (int) LEX_TD ), j );
                }
                else 
                {
                    char_left++;
                    j   = look ( charbuf, TD );
                    cerr<<TT[(type_of_lex) ( j + (int) LEX_TD )];
                    return Lex ( (type_of_lex) ( j + (int) LEX_TD ), j );
                }
                break;
            }
            case DIV://DONE
            {
                if(c== '/' )
                {
                    charbuf.push_back ( c );
                    j   = look( charbuf, TD );
                    cerr<<TT[(type_of_lex) ( j + (int) LEX_TD )];
                    return Lex ( (type_of_lex) ( j + (int) LEX_TD ), j );
                }
                else 
                {
                    char_left++;
                    j   = look ( charbuf, TD );
                    cerr<<TT[(type_of_lex) ( j + (int) LEX_TD )];
                    return Lex ( (type_of_lex) ( j + (int) LEX_TD ), j );
                }
            }
            case MULP://DONE
            {
                 if(c== '*' )
                {
                    charbuf.push_back ( c );
                    j   = look( charbuf, TD );
                    cerr<<TT[(type_of_lex) ( j + (int) LEX_TD )];
                    return Lex ( (type_of_lex) ( j + (int) LEX_TD ), j );
                }
                else 
                {
                    char_left++;
                    j   = look ( charbuf, TD );
                    cerr<<TT[(type_of_lex) ( j + (int) LEX_TD )];
                    return Lex ( (type_of_lex) ( j + (int) LEX_TD ), j );
                }
                break;
            }
            case NEQ://DONE
            {
                if(c == '=' )
                {
                    charbuf.push_back ( c );
                    j   = look( charbuf, TD );
                    cerr<<TT[(type_of_lex) ( j + (int) LEX_TD )];
                    return Lex ( (type_of_lex) ( j + (int) LEX_TD ), j );
                }
                else
                {
                    cerr<<" Lex mistake:"<< " No = after ! ";
                    cerr<<endl<<__FILE__<<__LINE__<<endl;
                    exit(0);
                    //
                }
                break;
            }
            case DEL: //DONE
            {
                char_left++;
                j   = look( charbuf, TD );
                cerr<<TT[(type_of_lex) ( j + (int) LEX_TD )];
                return Lex ( (type_of_lex) ( j + (int) LEX_TD ), j );
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
                        if(c!=' ')
                        {
                            cerr<<" Wrong INDENT size , "<<i+1<<" spaces only ";
                            cerr<<endl<<__FILE__<<__LINE__<<endl;
                            exit(0);
                        }
                    }
                    getc();
                }
                char_left++; // Аналог ungetc в моей низкоуровневой буфферизации
                if (curlvl==lvl+1)
                {
                    cerr<<TT[LEX_INDENT];
                    lvl++;
                    return Lex(LEX_INDENT);
                }
                else if (curlvl==lvl-1)
                {
                    cerr<<TT[LEX_DEDENT];
                    lvl--;
                    return Lex(LEX_DEDENT);;
                }
                else if(curlvl==lvl)
                {
                    //getc();
                    if(c==EOF)
                    {
                        cout<< "Success"<<endl;
                        exit(0);
                    }
                    cerr<<TT[LEX_NEWLINE];
                    return Lex(LEX_NEWLINE);
                }
                else
                {
                    cerr<<" Wrong number of indents: current level is ";
                    cerr<<curlvl<<" actual level is "<<lvl<<endl;
                    cerr<<endl<<__FILE__<<__LINE__<<endl;
                    exit(0);
                }
                if(c==EOF)
                {
                    cout<< "Success"<<endl;
                    exit(0);
                }
                break;
            } //end of IND
        } // end of switch
    } //end of while
    while(1) ;
}

