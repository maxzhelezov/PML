#include "exec.h"
#include "lex.h"
#include <stack>
#include "builtins.h"
#include <map>
#include <typeinfo>

void Executer::execute(std::vector<Lex> poliz){
    std::stack<PyObj *> st;
    std::map<std::string, PyObj *> dict;
    Lex curlex;
    std::vector<PyObj *> args;
    name * temp;
    fun * tempfun;
    PyObj * a, * b;
    int size = poliz.size();
    int i = 0;
    builtins(dict);
    while (i < size){
        curlex = poliz[i];
        switch(curlex.get_type()){
            case LEX_NAME:
                st.push(new name(curlex.get_ident()));
                break;
            case LEX_NUM:
                st.push(new num(curlex.get_value()));
                break;
            case LEX_MINUS:
                a = st.top(); st.pop();
                b = st.top(); st.pop();
                st.push(*b - a);
                break;
            case LEX_PLUS:
                a = st.top(); st.pop();
                b = st.top(); st.pop();
                st.push(*b + a);
                break;
            case LEX_DSLASH:
                a = st.top(); st.pop();
                b = st.top(); st.pop();
                st.push(b -> true_div(a));
                break;
            case LEX_PERC:
                a = st.top(); st.pop();
                b = st.top(); st.pop();
                st.push((*b) % a);
                break;
            case LEX_TIMES:
                a = st.top(); st.pop();
                b = st.top(); st.pop();
                st.push((*b) * a);
                break;
            case LEX_POW:
                a = st.top(); st.pop();
                b = st.top(); st.pop();
                st.push(b -> power(a));
                break;
            case POLIZ_STORE_LOC: 
                a = st.top(); st.pop();
                dict[curlex.get_ident()] = a; 
                break;
            case POLIZ_LOAD_LOC: 
                a = dict[curlex.get_ident()]; 
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
                tempfun -> run(args);
            default:;
        }
        i++;
    }
}
