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
const char * Scanner::TD [21] = { 

    "=", "<", ">" ,"==", "<=" ,">=", "!=", "+" ,"-" ,"*", 
//   0    1    2    2+1   4    5     6    7    8    9
    "/" ,"//" ,"%" ,"**","(" ,")" ,"[" ,"]" ,"," ":" ,"." ,"+"
//   10    11    12    13   14   15   16   17  18   19   20 
};
const char * Scanner::TW [18]={ 
    "NULL" , "return" , "None" , "continue" , "for" , "not" , "True" , "False",
//   0         1          2        4-1          4       5       6        7    
    "def", "while" , "and" , "global" , "in" , "if" , "or" ,"else", "pass" , 
//   8      9         10      11         12     13     14    15      16
    "break"
//   17
};
const char * Scanner::TT [51]={
//  Соответствующие лексемам слова, нужны для удобного вывода 
    "LEX_NULL", "LEX_NEWLINE", "LEX_END", "LEX_INDENT", "LEX_DEDENT",
    "LEX_PASS", "LEX_BREAK", "LEX_CONT", "LEX_RET", "LEX_GLOBAL", "LEX_DEF", 
    "LEX_IF", "LEX_ELSE", "LEX_WHILE", "LEX_FOR", "LEX_IN", "LEX_AND", 
    "LEX_NOT", "LEX_OR", "LEX_SEMICOLON", "LEX_COMMA", "LEX_COLON", "LEX_DOT", 
    "LEX_RLBRACKET", "LEX_RRBRACKET", "LEX_SLBRACKET", "LEX_SRBRACKET", 
    "LEX_EQ", "LEX_LSS", "LEX_GTR", "LEX_LEQ", "LEX_NEQ", "LEX_GEQ", 
    "LEX_ASSIGN","LEX_PLUS", "LEX_MINUS", "LEX_TIMES", "LEX_SLASH", 
    "LEX_DSLASH", "LEX_PERC", "LEX_POW","LEX_NAME", "LEX_NUM", "LEX_STRING", 
    "LEX_NONE", "LEX_TRUE", "LEX_FALSE",
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
        char_left=read(fd,buf,BUFSIZ);
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
    c=buf[char_scanned-char_left];
    
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
                if (c=='\r'||c==' '||c=='\t')
                {
                    ;//nothing
                }
                else if(c=='\n')
                {
                    curstate=IND;
                }
                else if(c=='"')
                {
                    curstate=STRING;
                }
                else if(c>='0'&&c<='9')
                    //  NUMBER
                {
                    d+=c-'0';
                    curstate=NUMBER;
                }
                else if(c=='#') //COMM
                {
                    curstate=COMM;
                }
                else if(c=='='||c=='<'||c=='>')//COMP
                {
                    charbuf.push_back (c);
                    curstate=COMP;
                }
                else if(c=='/') //DIV
                {
                    charbuf.push_back (c);
                    curstate=DIV;
                }
                //MULP,NEQ,DEL,IND
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
                    curstate=DEL;
                }
                //END
                else if(c==EOF)
                {
                    cout<< "Success"<<endl;
                    exit(0);
                }
                // Остались только char
                else
                {
                    curstate=NAME;
                }
                break;

            }
            case STRING:
            {
                /*if ( c == '}' ) {
                    CS  = H;
                }
                else if ( c == '@' || c == '{' )
                    throw c;
                break;*/
            }
            case NAME:
            {
                if ( isalpha (c) || isdigit (c) ) {
                    charbuf.push_back (c); 
                }
                else {
                    char_left--;
                    if ( (j = look ( buf, TW) ) ) {
                        return Lex ( (type_of_lex) j, j );
                        }
                        else {
                        j   = put ( buf );
                        return Lex ( LEX_NAME, j );
                    }
                }
                break;
            }
            case NUMBER:
            {
                if ( c>='0'&&c<='9') {
                    d = d * 10 + ( c - '0' );
                }
                else {
                    char_left++; // Аналог ungetc в моей низкоуровневой буфферизации
                    return Lex ( LEX_NUM, d );
                }
            }
            case COMM:
            {
                while(c!='\n'&&c!=EOF)
                    getc();
                if(c==EOF)
                {
                    cout<< "Success"<<endl;
                    exit(0);
                }
                curstate=IND;
            }
            case COMP:
            {
                if(c== '=' )
                {
                    charbuf.push_back ( c );
                    j   = look( buf, TD );
                    return Lex ( (type_of_lex) ( j + (int) LEX_SRBRACKET+2+1 ), j );
                }
                else 
                {
                    char_left++;
                    j   = look ( buf, TD );
                    return Lex ( (type_of_lex) ( j + (int) LEX_SRBRACKET+2 ), j );
                }
            }
            case DIV:
            {
                if(c=='/')
                {
                    return Lex(LEX_DSLASH);
                }
                else
                {
                    char_left++;
                    return Lex(LEX_SLASH);
                }
            }
            case MULP:
            {
                if(c=='*')
                {
                    return Lex(LEX_TIMES);
                }
                else
                {
                    char_left++;
                    return Lex(LEX_POW);
                }
            }
            case NEQ:
            {
                if(c=='=')
                {
                    cerr<<TT[LEX_NEQ];
                    return Lex(LEX_NEQ);
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
            case DEL:
            {
                char_left++;
                switch(c)
                    {
                        case '+':return Lex(LEX_PLUS);
                        case '-':return Lex(LEX_MINUS);
                        case '%':return Lex(LEX_PERC);
                        case '[':return Lex(LEX_SLBRACKET);
                        case ']':return Lex(LEX_SRBRACKET);
                        case '(':return Lex(LEX_RLBRACKET);
                        case ')':return Lex(LEX_RRBRACKET);
                        case '.':return Lex(LEX_DOT);
                        case ':':return Lex(LEX_COLON);
                        case ',':return Lex(LEX_COMMA);
                    }
            }
            /*case SPC:
            {
                if(c!=' ')
                {
                //Error();
                    cerr<<" Wrong INDENT size , "<<space<<" spaces only ";
                    cerr<<endl<<__FILE__<<__LINE__<<endl;
                    exit(0);
                }
                else if(++space==4)
                {
                    curstate=IND;
                    cerr<<" AAAAAAAAAAAAAAAAAAAAAAAAAA ";
                }
                // Если прочитали 4 пробела - перейдём на IND сразу
                else
                {
                    cerr<<"  -"<<space;
                    break;
                }
            }
            case IND:
            {
                cerr<<"Attention"<<endl;
                if(space==4)
                {
                    if (curlvl=lvl+1)
                    {
                        cerr<<TT[LEX_INDENT];
                        return l;
                    }
                    else if (curlvl=lvl-1)
                    {
                        cerr<<TT[LEX_DEDENT];
                        return l;
                    }
                    else if(curlvl==lvl)
                    {
                        curstate = H;
                        curlvl=0;
                    }
                    else
                    {
                        cerr<<" Wrong number of indents: current level is ";
                        cerr<<curlvl<<" actual level is "<<lvl<<endl;
                        cerr<<endl<<__FILE__<<__LINE__<<endl;
                        exit(0);
                    }
                    break;
                }
                if(c==' ')
                {
                    curstate=SPC;
                    space=1;
                    curlvl++;
                    break;
                }*/
            case IND:
            {
                int curlvl=0;
                while(c==' ')
                {
                    curlvl++;
                    for(i=0;i<1+2;i++)
                    {
                        getc();
                        if(c!=' ')
                        {
                            cerr<<" Wrong INDENT size , "<<space<<" spaces only ";
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
                    curstate = H;
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

int main ()
{
    Scanner a ("test.txt");
    int i;
    while (1)
    {
        cin >>i;
        a.get_lex();
    }
    Lex l(LEX_BREAK,0);
    cout<< l<<endl;


    cout<<"Hello\n";
}