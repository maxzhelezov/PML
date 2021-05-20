#include "exec.h"
#include "lex.h"
#include <stack>
#include "builtins.h"
#include <map>
#include <typeinfo>

// Выводит ошибку о неверных методах у двух типов
static void err2(PyObj * a, PyObj *b, const char * meth_name){
    std::string out =  std::string("Objects ") + a -> repr() + 
        std::string(" and ") + b -> repr() + 
        std::string(" don't support method: ") + std::string(meth_name);
    throw Scanner::my_exception(0,0,out, Scanner::my_exception::exec);
}

// Выводит ошибку о неверных методах у двух типов
static void err(PyObj * a, const char * meth_name){
    std::string out =  std::string("Object ") + a -> repr() +  
        std::string(" doesn't support method: ") + std::string(meth_name);
    throw Scanner::my_exception(0,0,out, Scanner::my_exception::exec);
}


void Executer::execute(std::vector<Lex> poliz){
    std::stack<PyObj *> st;
    std::map<std::string, PyObj *> dict;
    Lex curlex;
    std::vector<PyObj *> args;
    fun * tempfun;
    PyObj * a, * b, * c;
    int size = poliz.size();
    int i = 0;
    builtins(dict);
    while (i < size){
        curlex = poliz[i];
        switch(curlex.get_type()){
            case LEX_NUM:
                st.push(new num(curlex.get_value()));
                break;

            case LEX_TRUE:
                st.push(new boolean(true));
                break;

            case LEX_STRING:
                st.push(new string(curlex.get_string()));
                break;

            case LEX_FALSE:
                st.push(new boolean(false));
                break;

            case LEX_AND:
                a = st.top(); st.pop();
                b = st.top(); st.pop();
                c = *b && a;
                if (c == 0)
                    err2(b,a,"binary and");
                st.push(c);
                break;

            case LEX_OR:
                a = st.top(); st.pop();
                b = st.top(); st.pop();
                c = *b || a;
                if (c == 0)
                    err2(b,a,"binary or");
                st.push(c);
                break;
            
            case LEX_LSS:
                a = st.top(); st.pop();
                b = st.top(); st.pop();
                c = *b < a;
                if (c == 0)
                    err2(b,a,"comparasion operator <");
                st.push(c);
                break;
            
             case LEX_GTR:
                a = st.top(); st.pop();
                b = st.top(); st.pop();
                c = *b > a;
                if (c == 0)
                    err2(b,a,"comparasion operator >");
                st.push(c);
                break;
            
             case LEX_LEQ:
                a = st.top(); st.pop();
                b = st.top(); st.pop();
                c = *b <= a;
                if (c == 0)
                    err2(b,a,"comparasion operator <=");
                st.push(c);
                break;
            
             case LEX_GEQ:
                a = st.top(); st.pop();
                b = st.top(); st.pop();
                c = *b >= a;
                if (c == 0)
                    err2(b,a,"comparasion operator >=");
                st.push(c);
                break;
            
             case LEX_EQ:
                a = st.top(); st.pop();
                b = st.top(); st.pop();
                c = *b == a;
                if (c == 0)
                    err2(b,a,"comparasion operator ==");
                st.push(c);
                break;
            
             case LEX_NEQ:
                a = st.top(); st.pop();
                b = st.top(); st.pop();
                c = *b != a;
                if (c == 0)
                    err2(b,a,"comparasion operator !=");
                st.push(c);
                break;
                
             case LEX_NOT:
                a = st.top(); st.pop();
                c = !(*a);
                if (c == 0)
                    err(a,"unary not");
                st.push(c);
                break;

            case LEX_MINUS:
                if (curlex.get_value() == 2){
                    a = st.top(); st.pop();
                    b = st.top(); st.pop();
                    c = *b - a;
                    if (c == 0)
                        err2(a,b,"binary minus");
                    st.push(c);
                }
                if (curlex.get_value() == 1){
                    a = st.top(); st.pop();
                    c = -(*a);
                    if (c == 0)
                        err(a, "unary minus");
                    st.push(c);
                }
                break;

            case LEX_PLUS:
                if (curlex.get_value() == 2){
                    a = st.top(); st.pop();
                    b = st.top(); st.pop();
                    c = *b + a;
                    if (c == 0)
                        err2(a,b,"binary plus");
                    st.push(c);
                }
                if (curlex.get_value() == 1){
                    a = st.top(); st.pop();
                    c = +(*a);
                    if (c == 0)
                        err(a,"unary plus");
                    st.push(c);
                }
                break;
        
            case LEX_SLASH:
                a = st.top(); st.pop();
                b = st.top(); st.pop();
                c = (*b) / a;
                if (c == 0)
                    err2(a,b,"binary division");
                st.push(c);
                break;

            case LEX_DSLASH:
                a = st.top(); st.pop();
                b = st.top(); st.pop();
                c = b -> true_div(a);
                if (c == 0)
                    err2(a,b,"binary floor division");
                st.push(c);
                break;

            case LEX_PERC:
                a = st.top(); st.pop();
                b = st.top(); st.pop();
                c = *b % a;
                if (c == 0)
                    err2(a,b,"binary modulo");
                st.push(c);
                break;

            case LEX_TIMES:
                a = st.top(); st.pop();
                b = st.top(); st.pop();
                c = *b * a;
                if (c == 0)
                    err2(a,b,"binary multiplication");
                st.push(c);
                break;

            case LEX_POW:
                a = st.top(); st.pop();
                b = st.top(); st.pop();
                c = b -> power(a);
                if (c == 0)
                    err2(a,b,"binary power");
                st.push(c);
                break;

            case POLIZ_STORE_LOC: 
                a = st.top(); st.pop();
                dict[curlex.get_ident()] = a; 
                break;
        
            case POLIZ_GO:
                i = curlex.get_value();
                continue; //пропускаем i++
                break;

            case POLIZ_FGO:
                a = st.top(); st.pop();
                if (a -> truth())
                    ;
                else{
                    i = curlex.get_value();
                    continue; //пропускаем i++
                }
                break;

            case POLIZ_LOAD_LOC: 
                a = dict[curlex.get_ident()]; 
                if (a == 0){
                    throw Scanner::my_exception(0,0,
                    "Name Error: name " + curlex.get_ident() + " is not defined",
                    Scanner::my_exception::exec);
                }

                st.push(a);
                break;

            case POLIZ_CALL:
                args.clear();
                for(int i = 0; i < curlex.get_value(); i++){
                    args.push_back(st.top());
                    st.pop();
                }
                tempfun = dynamic_cast<fun *>(st.top());
                st.pop();
                c = tempfun -> run(args);
                if (c != 0)
                    st.push(c);

            default:;
        }
        i++;
    }
}
