// header
// Лексический этап 
#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <string>



enum type_of_lex {
//  Программные лексемы - члены таблицы TD
    LEX_NULL, LEX_TW, LEX_NONE, LEX_TRUE, LEX_FALSE, LEX_GLOBAL,
//  0         1       2         3         4          5
    LEX_DEF, LEX_RET, LEX_WHILE, LEX_FOR,  LEX_CONT, LEX_PASS, LEX_BREAK,  
//  6        7        8          9         10        11        12
    LEX_IF, LEX_ELSE,  LEX_NOT, LEX_AND, LEX_IN, LEX_OR,
//  13      14         15       16       17      18


// Члены таблицы TD                                   
    LEX_TD,
//  19
    LEX_ASSIGN, LEX_LSS, LEX_GTR, LEX_EQ, LEX_LEQ,  LEX_GEQ, LEX_NEQ,
//  20          21       22       23      24        25       26
    LEX_PLUS, LEX_MINUS, LEX_TIMES, LEX_SLASH, LEX_DSLASH, LEX_PERC, LEX_POW,
//  27        28         29         30         31          32        33
// Первый символ S == square, R == round , второй == left / right DONE
    LEX_RLBRACKET, LEX_RRBRACKET, LEX_SLBRACKET, LEX_SRBRACKET,   
//  34             35             36             37
    LEX_SEMICOLON, LEX_COMMA, LEX_COLON, LEX_DOT,
//  38             39         40         41


//  Атомы
    LEX_NAME, LEX_NUM, LEX_STRING, LEX_INDENT, LEX_DEDENT, LEX_NEWLINE, LEX_END,       
//  41        42       43          44        45        46
                                                                                        
    POLIZ_LABEL,                                                                                /*47*/
    POLIZ_ADDRESS,                                                                              /*48*/
    POLIZ_GO,                                                                                   /*49*/
    POLIZ_FGO                                                                                   /*50*/
};



class Ident
{
    std::string name;
    type_of_lex type;
    int value;
    bool declared;
    bool assigned;
public:
    Ident();
    bool operator== ( const std::string& s );
    Ident ( const std::string n ) ;
    std::string get_name () const ;
    bool get_declare () const ;
    void put_declare () ;
    type_of_lex get_type () const ;
    void put_type ( type_of_lex t ) ;
    bool get_assign () const ;
    void put_assign () ;
    int  get_value () const ;
    void put_value ( int v ) ;

};



class Lex 
{
    type_of_lex   lex_type;
    int           lex_value;
public:
    Lex ( type_of_lex type = LEX_NULL, int value = 0 );
    type_of_lex  get_type () const ;
    int get_value () const ;
    friend std::ostream & operator<< ( std::ostream &s, Lex l );
};



class Scanner
{
private:
    enum state {H, NAME, STRING, NUMBER, COMM, COMP, DIV, MULP, NEQ, DEL, IND};
    int lvl;
    int fd;
    int char_left;
    
    char c;
    char buf[BUFSIZ];
    bool eof_flag;
    
    void getc();
    
public :
    int char_in_str;
    int lines;
    class my_exception 
    {
        public:
        enum errtype {lex,synt} ;
        int line;
        int sym;
        std::string error_message;
        errtype error_type;
        my_exception(int line,int cs,
                std::string error_message1, errtype error_type);
    };
    static const char * TD [23];
    static const char * TW [18];
    static const char * TT [POLIZ_FGO +1];
    Scanner( const char *prog);
    Lex get_lex();
    ~Scanner();
    friend std::ostream & operator<< ( std::ostream &s, my_exception e );
};