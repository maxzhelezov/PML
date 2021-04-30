// Синтаксический и семантический этапы 
#include "synt.h"
void Parser::gl()
{
    curlex=get_lex();
    curtype=curlex.get_type();
}

// initializer указывается через argv, file указывается в строке filename
// Если single input, то ввод - stdin ( 0 )
Parser::Parser  (string initializer, const char * filename) :Scanner(filename)
{
    if(initializer=="file")
    {
        //Получи первую лексему 
        gl();
        file_input();
    }
    else if( initializer=="single")
    {
        //Получи первую лексему
        gl();
        while(curtype!=LEX_END)
        {
            // Здесь будет работа с экзекуцией после новой строки
            while (curtype==LEX_NEWLINE)
                gl();
            single_input();
            while (curtype==LEX_NEWLINE)
                gl();
        }
        cout<<TT[(int)curtype];
    }
    else
        throw Scanner::my_exception(__LINE__,__FILE__,
                    "Wrong initializer",
                    Scanner::my_exception::synt);
} 

// compound начинается с while| for| def| if
// остальное, кроме newline - simple_stmt
// Семантика такова, что single input реализует ввод по одной строке,т.е
// После считывания строки идёт возврат
void Parser::single_input()
{
        
    switch (curtype)
    {
        case LEX_IF: case LEX_WHILE: case  LEX_FOR: case LEX_DEF:
            compound_stmt(); 
            if(curtype!=LEX_NEWLINE)
                throw Scanner::my_exception(__LINE__,__FILE__,
                        "Single input : no newline after compound statement",
                                Scanner::my_exception::synt);
                //throw "Single input : no newline after compound statement";
            gl();
            return;

        default:
            simple_stmt();
            return;
    } 
} 
void Parser::file_input()
{
    while ( curtype!=LEX_END)
    {
        while (curtype==LEX_NEWLINE)
            gl();
        stmt();
        while (curtype==LEX_NEWLINE)
            gl();
    }
    
} 
// compound stmt начинаектся с if||while||for||def
// Иначе simple_stmt
void Parser::stmt ()
{
    switch (curtype)
    {
        case LEX_IF: case LEX_WHILE: case  LEX_FOR: case LEX_DEF:
            compound_stmt(); 
            return;
        default:
            simple_stmt();
            return;
    } 
} 
void Parser::simple_stmt ()
{
    small_stmt();
    if (curtype!=LEX_NEWLINE )
    {
        throw Scanner::my_exception(__LINE__,__FILE__,
                        "simple_stmt : no newline",
                                Scanner::my_exception::synt);
        //throw "simple_stmt : no newline";
    }
    gl();
} 
// flow : break| cont |ret
// pass_stmt| global_stmt
void Parser::small_stmt ()
{
    switch (curtype)
    {
        case LEX_BREAK: case LEX_CONT: case  LEX_RET: 
            flow_stmt(); 
            return;
        case LEX_PASS:
//pass block

            return;
        case LEX_GLOBAL:
            global_stmt();
            return;
        default:
            expr_stmt ();
            return;
    } 
} 
void Parser::expr_stmt ()
{
    test();
    if( curtype==LEX_ASSIGN)
    {
        gl();
        test();
    }
} 
void Parser::flow_stmt ()
{
    switch (curtype)
    {
        // break and cont block
        case LEX_BREAK: 
        case LEX_CONT: 
        gl();
        return;

//Стоит ли ?
        case  LEX_RET: 
            testlist();
            return;
        default:
            throw Scanner::my_exception(__LINE__,__FILE__,
                        "flow_stmt",
                                Scanner::my_exception::synt);
            //throw "flow_stmt";
            return;
    }
}  

void Parser::global_stmt()
{
    if(curtype!=LEX_GLOBAL)
        throw Scanner::my_exception(__LINE__,__FILE__,
                        "global_stmt : curlex not global",
                                Scanner::my_exception::synt);
        //throw "global_stmt : curlex not global";
    gl();
    if(curtype==LEX_NAME)
    {
        gl();
    }
    else
    {
        throw Scanner::my_exception(__LINE__,__FILE__,
                        "global_stmt : curlex not name",
                                Scanner::my_exception::synt);
        //throw "global_stmt : curlex not name";
    }
    while (curtype==LEX_COMMA)
    {
        gl();
        if(curtype==LEX_NAME)
        {   
            gl();
        }
        else
        {
            throw Scanner::my_exception(__LINE__,__FILE__,
                        "global_stmt : no name after comma",
                                Scanner::my_exception::synt);
            //throw "global_stmt : no name after comma";
        }
    }
    
} 
void Parser::compound_stmt ()
{
    switch ( curtype)
    {

    case LEX_IF     : if_stmt();    return;
    case LEX_WHILE  : while_stmt(); return;
    case LEX_FOR    : for_stmt();   return;
    case LEX_DEF    : funcdef();    return;
    default         : throw Scanner::my_exception(__LINE__,__FILE__,
                                "compound_stmt wrong lexem ",
                                Scanner::my_exception::synt);
                    //throw "compound_stmt";
    }
} 

void Parser::funcdef()
{
    if(curtype!=LEX_DEF)
        throw Scanner::my_exception(__LINE__,__FILE__,
                    "funcdef: no def",
                    Scanner::my_exception::synt);
            //throw "funcdef: no def";
    gl();
    if(curtype!=LEX_NAME)
        throw Scanner::my_exception(__LINE__,__FILE__,
                    "funcdef: no name",
                    Scanner::my_exception::synt);
        //throw "funcdef: no name";

    gl();
    parameters();
    if(curtype!=LEX_COLON)
        throw Scanner::my_exception(__LINE__,__FILE__,
                    "funcdef: no colon",
                    Scanner::my_exception::synt);
        //throw "funcdef: no colon";
    gl();
    suite();
} 
void Parser::parameters ()
{
    if(curtype!=LEX_RLBRACKET)
    throw Scanner::my_exception(__LINE__,__FILE__,
                    "parameters: no opening round bracket",
                    Scanner::my_exception::synt);
        //throw "parameters: no opening round bracket";
    gl();
    if(curtype==LEX_NAME)
        argslist(); //Реализован [argslist]
    if(curtype!=LEX_RRBRACKET)
    throw Scanner::my_exception(__LINE__,__FILE__,
                    "parameters: no closing round bracket",
                    Scanner::my_exception::synt);
        //throw "parameters: no closing round bracket";
    gl();
} 
void Parser::argslist ()
{
    if(curtype==LEX_NAME)
    {
        gl();
    }
    else
    {
        throw Scanner::my_exception(__LINE__,__FILE__,
                     "argslist : no name",
                    Scanner::my_exception::synt);
        //throw "argslist no name";
    }
    while (curtype==LEX_COMMA)
    {
        gl();
        if(curtype==LEX_NAME)
        {   
            gl();
        }
        else
        {
            throw Scanner::my_exception(__LINE__,__FILE__,
                    "argslist: comma not followed by name",
                    Scanner::my_exception::synt);
            //throw "argslist: comma not followed by name";
        }
    }
} 
void Parser::if_stmt ()
{
    if(curtype!=LEX_IF)
        throw Scanner::my_exception(__LINE__,__FILE__,
                    "if_stmt: no if",
                    Scanner::my_exception::synt);
        //throw "if_stmt: no if";
    gl();
    test();
    if(curtype!=LEX_COLON)
        throw Scanner::my_exception(__LINE__,__FILE__,
                    "if_stmt: no colon after if <test>",
                    Scanner::my_exception::synt);
        //throw "if_stmt: no colon after if test";
    gl();
    suite();
    
    if( curtype==LEX_ELSE)
    {
        gl();
        if(curtype!=LEX_COLON)
            throw Scanner::my_exception(__LINE__,__FILE__,
                    "if_stmt: no colon after else",
                    Scanner::my_exception::synt);
            //throw "if_stmt: no colon after else";
        gl();
        suite();
    }
    
} 
void Parser::while_stmt()
{
    if(curtype!=LEX_WHILE)
        throw Scanner::my_exception(__LINE__,__FILE__,
                    "while_stmt: no while_stmt",
                    Scanner::my_exception::synt);
        //throw "while_stmt: no while_stmt";
    gl();   
    test();
    if(curtype!=LEX_COLON)
        throw Scanner::my_exception(__LINE__,__FILE__,
                    "while_stmt: no colon after <test>",
                    Scanner::my_exception::synt);
        //throw "while_stmt: no colon after <test>";
    gl();
    suite();
} 
void Parser::for_stmt()
{
    if(curtype!=LEX_FOR)
        throw Scanner::my_exception(__LINE__,__FILE__,
                    "for_stmt: no while_stmt",
                    Scanner::my_exception::synt);
        //throw "for_stmt: no while_stmt";
    gl();   
    exprlist();
    if(curtype!=LEX_IN)
        throw Scanner::my_exception(__LINE__,__FILE__,
                    "for_stmt: no colon after test",
                    Scanner::my_exception::synt);
        //throw "for_stmt: no colon after test";
    gl();
    testlist();
    if(curtype!=LEX_COLON)
        throw Scanner::my_exception(__LINE__,__FILE__,
                    "for_stmt: no colon after testlist",
                    Scanner::my_exception::synt);
        //throw "for_stmt: no colon after testlist";
    gl();
    suite();
} 
// Если Indent, то та ветка, иначе simple_stmt ветка
void Parser::suite ()
{
    if( curtype==LEX_NEWLINE)
    {
        gl();
        if(curtype!=LEX_INDENT)
            throw Scanner::my_exception(__LINE__,__FILE__,
                    "suite : no indent after newline",
                    Scanner::my_exception::synt);
            //throw "suite : no indent after newline";    
        gl();
        stmt();
        // Никаких противоречий нет, ошибка будет поймана в любом случае
        while( curtype!=LEX_DEDENT)
            stmt();
        gl();
    }
    else
    {
        simple_stmt();
    }
} 
void Parser::testlist ()
{
    test();
    while (curtype==LEX_COMMA)
    {
        gl();
        test();
    }
} 
void Parser::exprlist ()
{
    arith_expr();
    while (curtype==LEX_COMMA)
    {
        gl();
        arith_expr();
    }
} 
void Parser::test ()
{
    and_test();
    while (curtype==LEX_OR)
    {
        gl();
        and_test();
    }
} 
void Parser::and_test()
{
    not_test();
    while (curtype==LEX_AND)
    {
        gl();
        not_test();
    }
} 
void Parser::not_test ()
{
    if( curtype==LEX_NOT)
    {
        gl();
        not_test();
    }
    else
        comparison();
} 
void Parser::comparison ()
{
    bool comparison_found;
    arith_expr();
    //Равносильно равенству одному из
// '>' | '<' | '==' | '>='| '<=' | '!=' | 'in' | 'not' | 'in'
    comparison_found=((int)curtype>=(int)LEX_LSS&&(int)curtype<=(int)LEX_NEQ)||
        ((int)curtype>=(int)LEX_NOT&&(int)curtype<=(int)LEX_OR);
    while(comparison_found)
    {
        // Считали символ - сравнение
        gl();
        arith_expr();
        // Снова проверка -тот ли символ
        comparison_found=((int)curtype>=LEX_LSS&&(int)curtype<=LEX_NEQ)||
            ((int)curtype>=LEX_NOT&&(int)curtype<=LEX_OR);
    }

}  
void Parser::arith_expr ()
{
    bool sign_found;
    term();
    sign_found=curtype==LEX_PLUS || curtype==LEX_MINUS;
    while(sign_found)
    {
        // Считали символ - знак
        gl();
        term();
        // Снова проверка - тот ли символ
        sign_found=curtype==LEX_PLUS || curtype==LEX_MINUS;
    }
} 

void Parser::term ()
{
    bool mul_found;
    factor();
    mul_found=curtype==LEX_TIMES || curtype==LEX_DSLASH|| 
        curtype==LEX_SLASH|| curtype==LEX_PERC;
    while(mul_found)
    {
        // Считали символ - знак
        gl();
        factor();
        // Снова проверка - тот ли символ
        mul_found=curtype==LEX_TIMES || curtype==LEX_DSLASH|| 
        curtype==LEX_SLASH|| curtype==LEX_PERC;
    }
} 
void Parser::factor ()
{
    if(curtype==LEX_PLUS || curtype==LEX_MINUS)
    {
        //знак есть
        gl();
        factor();
    }
    else
    {
        power();
    }
} 
void Parser::power ()
{
    atom();
    trailer();
    if(curtype==LEX_POW)
    {
        gl();
        factor();
    }
} 
void Parser::atom ()
{
    switch (curtype)
    {
        case LEX_TRUE:  gl(); return;
        case LEX_NONE:  gl(); return;
        case LEX_FALSE: gl(); return;
        case LEX_NAME:  gl(); return;
        case LEX_NUM:   gl(); return;
        case LEX_STRING:gl(); return;
    case LEX_RLBRACKET:
    {
        gl();
        testlist(); //Реализовать [test]
        if(curtype!=LEX_RRBRACKET)
            throw Scanner::my_exception(__LINE__,__FILE__,
                    "atom : no closing round bracket",
                    Scanner::my_exception::synt);
            //throw "atom : no closing round bracket";
        gl();
        return;
    }   
    case LEX_SLBRACKET:
    {
        gl();
        testlist(); //Реализовать [test]
        if(curtype!=LEX_SRBRACKET)
            throw Scanner::my_exception(__LINE__,__FILE__,
                    "atom : no closing square bracket",
                    Scanner::my_exception::synt);
            //throw "atom : no closing square bracket";
        gl();
        return;
    }
    default:
        throw Scanner::my_exception(__LINE__,__FILE__,
                    "atom : no right lex ",
                    Scanner::my_exception::synt);
        //throw "atom : no right lex ";
    }
} 

void Parser::trailer()
{
switch (curtype)
    {
    case LEX_DOT: gl(); //NAME 
                    gl(); return;
    case LEX_RLBRACKET:
    {
        gl();
        // реализует ([testlist])
        if(curtype!=LEX_RRBRACKET)
            testlist();
        if(curtype!=LEX_RRBRACKET)
            throw Scanner::my_exception(__LINE__,__FILE__,
                    "atom : no right lex ",
                    Scanner::my_exception::synt);    
            //throw "atom : no closing round bracket";
        gl();
        return;
    }   
    case LEX_SLBRACKET:
    {
        gl();
        if(curtype!=LEX_SRBRACKET)
            subscriptlist();  
        if(curtype!=LEX_SRBRACKET)
            throw Scanner::my_exception(__LINE__,__FILE__,
                    "atom : no right lex ",
                    Scanner::my_exception::synt);
            //throw "atom : no closing square bracket";
        gl();
        return;
    }
    default:;
    }
}
void Parser::subscriptlist()
{
    subscript();
    if(curtype!=LEX_COMMA)
        throw Scanner::my_exception(__LINE__,__FILE__,
                    "subscriptlist: no comma",
                    Scanner::my_exception::synt);
        //throw "subscriptlist: no comma";
    gl();
    subscript();
} 
void Parser::subscript ()
{
    test();
    if(curtype==LEX_COLON)
    {
        gl();
        // Две следующие не обязательны
        test();
        sliceop();
    }    
}
void Parser::sliceop()
{
    if(curtype!=LEX_COMMA)
        throw Scanner::my_exception(__LINE__,__FILE__,
                    "subscriptlist: no comma",
                    Scanner::my_exception::synt);
        //throw "subscriptlist: no comma";
    gl();
    // не обязательна
    test();
    
}














