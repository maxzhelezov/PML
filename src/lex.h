// header
// Лексический этап 
#include <iostream>
#include <vector>

using namespace std;
//#include <string>
enum type_of_lex {
//  Программные лексемы
    LEX_NULL, LEX_NEWLINE, LEX_END, LEX_INDENT, LEX_DEDENT,
//  0         1            2        1+2         4
    LEX_PASS, LEX_BREAK, LEX_CONT, LEX_RET, LEX_GLOBAL, LEX_DEF, 
//  5         6          7         8        9           10

//  Условный оператор и Циклы
    LEX_IF, LEX_ELSE, LEX_WHILE, LEX_FOR,
//  11      12        13         14

//  Логические операции 
    LEX_IN, LEX_AND, LEX_NOT, LEX_OR,   
//  15      16         17       18       
     
// Различные разделители и скобки   DONE                                    
    LEX_SEMICOLON, LEX_COMMA, LEX_COLON, LEX_DOT,
//  19             20         21         22
// Первый символ S == square, R == round , второй == left / right DONE
    LEX_RLBRACKET, LEX_RRBRACKET, LEX_SLBRACKET, LEX_SRBRACKET,   
//  23             24             25             26

// Лексемы математических операций ( сравнение, сложение и т.п.)
    LEX_EQ, LEX_LSS, LEX_GTR, LEX_LEQ, LEX_NEQ, LEX_GEQ, LEX_ASSIGN,
//  27      28       29       30       31       32       33

    LEX_PLUS, LEX_MINUS, LEX_TIMES, LEX_SLASH, LEX_DSLASH, LEX_PERC, LEX_POW,
//  34        35         36         37         38          39        40

//  Атомы
    LEX_NAME, LEX_NUM, LEX_STRING, LEX_NONE, LEX_TRUE, LEX_FALSE,        
//  41        42       43          44        45        46
                                                                                        
    POLIZ_LABEL,                                                                                /*47*/
    POLIZ_ADDRESS,                                                                              /*48*/
    POLIZ_GO,                                                                                   /*49*/
    POLIZ_FGO                                                                                   /*50*/
};

class Ident
{
    string name;
    type_of_lex type;
    int value;
    bool declared;
    bool assigned;
public:
    Ident();
    bool operator== ( const string& s );
    Ident ( const string n ) ;
    string get_name () const ;
    bool get_declare () const ;
    void put_declare () ;
    type_of_lex get_type () const ;
    void put_type ( type_of_lex t ) ;
    bool get_assign () const ;
    void put_assign () ;
    int  get_value () const ;
    void put_value ( int v ) ;

};


vector<Ident> TID;
 


/*class TID
{
    vector <Ident> Table;
public:
    int operator += ( const string & buf ) {
    vector<Ident>::iterator k;
 
   // if ( ( k = find ( TID.begin (), TID.end (), buf ) ) != TID.end () )
   //     return k - TID.begin();
   // TID.push_back ( Ident(buf) );
   // return TID.size () - 1;
}
};
*/

class Lex 
{
    type_of_lex   lex_type;
    int           lex_value;
public:
    Lex ( type_of_lex type = LEX_NULL, int value = 0 );
    type_of_lex  get_type () const ;
    int get_value () const ;
    friend ostream & operator<< ( ostream &s, Lex l );
};

class Scanner
{
    enum state {H, NAME, STRING, NUMBER, COMM, COMP, DIV, MULP, NEQ, DEL, IND,SPC};
    int lvl;
    int fd;
    int char_left;
    char c;
    char buf[BUFSIZ];
    bool eof_flag;
    void getc();
   // int find (const string str,)
    
public :
    static const char * TD [21];
    static const char * TW [18];
    static const char * TT [POLIZ_FGO +1];
    Scanner( const char *prog);
    Lex get_lex();
    ~Scanner();
};