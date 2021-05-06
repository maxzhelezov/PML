// header
// Лексический этап 
#include <iostream>
#include <vector>
//#include <string>
#include <cstdio>
//#include <string>



enum type_of_lex {
//  Программные лексемы - члены таблицы TW
//  Важно, что их порядок совпадает с порядком строк в TW
    LEX_NULL, LEX_TW, LEX_NONE, LEX_TRUE, LEX_FALSE, LEX_GLOBAL,
//  0         1       2         3         4          5
    LEX_DEF, LEX_RET, LEX_WHILE, LEX_FOR,  LEX_CONT, LEX_PASS, LEX_BREAK,  
//  6        7        8          9         10        11        12
    LEX_IF, LEX_ELSE,  LEX_NOT, LEX_AND, LEX_IN, LEX_OR,
//  13      14         15       16       17      18


// Члены таблицы TD 
//  Важно, что их порядок совпадает с порядком строк в TD                           
    LEX_TD,
    LEX_ASSIGN, LEX_LSS, LEX_GTR, LEX_EQ, LEX_LEQ,  LEX_GEQ, LEX_NEQ,
    LEX_PLUS, LEX_MINUS, LEX_TIMES, LEX_SLASH, LEX_DSLASH, LEX_PERC, LEX_POW,
// Первый символ S == square, R == round , второй == left / right DONE
    LEX_RLBRACKET, LEX_RRBRACKET, LEX_SLBRACKET, LEX_SRBRACKET,   
    LEX_SEMICOLON, LEX_COMMA, LEX_COLON, LEX_DOT,

//  Атомы
    LEX_NAME, LEX_NUM, LEX_STRING, LEX_INDENT, LEX_DEDENT, LEX_NEWLINE, LEX_END,       
//  Необходимая для полиза часть.                                                                                 
    POLIZ_LABEL,                                                                                
    POLIZ_ADDRESS,                                                                              
    POLIZ_GO,                                                                                   
    POLIZ_FGO                                                                                   
};

//  Класс  Ident - нужен для создания таблицы идентификаторов 
//

class Ident
{
    std::string name; // имя
    type_of_lex type;
    int value;        // значение
    bool declared;    // факт  объявления
    bool assigned;    // факт  присвоения значения
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
    int           lex_line;
    int           lex_number;
    type_of_lex   lex_type;
    int           lex_value;
    
public:
    Lex (int line=0,int number=0 ,type_of_lex type = LEX_NULL, int value = 0 );
    type_of_lex  get_type () const ;
    int get_value () const ;
    int get_line() const;
    int get_number() const;
    friend std::ostream & operator<< ( std::ostream &s, Lex l );
};


class Scanner
{
private:
    // Тип состояния автомата
    enum state {H, NAME, STRING, NUMBER, COMM, COMP, DIV, MULP, NEQ, DEL, IND};
    int lvl;          // Переменная кол-ва отступов ident
    int fd;           // Дескриптор файла из которого читается программа   
    char c;           // Текущий символ
    int char_left;    // Кол-во символов в буфере
    char buf[BUFSIZ]; // Буфер
    bool eof_flag;    // Признак конца файла
// Метод, возвращающий символ из буфера, предварительно заполняющий его.
    void getc();      
    
public :
    
    // Класс исключения
    class my_exception 
    {
        public:
        enum errtype {lex,synt,file} ;
        int line;    // Номер строки
        int sym;     // Номер символа в строке
        std::string error_message;
        errtype error_type;
        my_exception(int line,int cs,
                std::string error_message1, errtype error_type);
    };
    // Таблицы с строковым описанием 
    static const char * TD [23];  //
    static const char * TW [18];  // 
    static const char * TT [POLIZ_FGO+1]; //
    Scanner( const char *prog);
    // Метод, возвращающий лексему либо выдающий ошибку, если
    // нарушено правило автомата.
    Lex get_lex();          
    ~Scanner();
    friend std::ostream & operator<< ( std::ostream &s, my_exception e );
};