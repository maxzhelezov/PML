// Header 
// Синтаксический и семантический этапы
#include <iostream>
#include <vector>
#include <cstdio>
#include "lex.h"
extern vector<Ident> TID;
class Parser: public Scanner
{
    bool file_input_flag;
    public:
    Lex curlex;
    type_of_lex curtype;
    void gl();
    Parser(string initializer, const char * filename=NULL);
    // Вместо start используется конструктор
    // void start (); 
    void single_input(); 
    void file_input(); 
    void stmt (); 
    void simple_stmt (); 
    void small_stmt (); 
    void expr_stmt ();  
    void flow_stmt (); 
    void global_stmt(); 
    void compound_stmt (); 
    void funcdef(); 
    void parameters (); 
    void argslist (); 
    void if_stmt (); 
    void while_stmt(); 
    void for_stmt(); 
    void suite (); 
    void testlist (); 
    void exprlist (); 
    void test (); 
    void and_test(); 
    void not_test (); 
    void comparison (); 
    void arith_expr ();  
    void term ();  
    void factor (); 
    void power (); 
    void atom (); 
    void trailer();
    void subscriptlist(); 
    void subscript ();
    void sliceop(); 
};
