#include "builtins.h"
#include <typeinfo>
#include <string>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <cmath>
#include "lex.h"

#define UN(x) (void)(x) 

static std::string itoa(int in){
    std::stringstream stream;
    stream << in;
    return stream.str();
}

num::num(int x): data(x)
{}

PyObj * num::operator&&(PyObj * in){
    if (typeid(*in) == typeid(num)){
        num * temp = dynamic_cast<num * >(in);
        return new num(this->data & temp -> get());
    }
    return 0;
}

PyObj * num::operator||(PyObj * in){
    if (typeid(*in) == typeid(num)){
        num * temp = dynamic_cast<num * >(in);
        return new num(this->data | temp -> get());
    }
    return 0;
}

PyObj * num::operator!(){
        return new num(!this->data);
}


PyObj * num::operator>(PyObj * in){
    if (typeid(*in) == typeid(num)){
        num * temp = dynamic_cast<num * >(in);
        return new boolean(this->data > temp -> get());
    }
    return 0;
}

PyObj * num::operator>=(PyObj * in){
    if (typeid(*in) == typeid(num)){
        num * temp = dynamic_cast<num * >(in);
        return new boolean(this->data >= temp -> get());
    }
    return 0;
}

PyObj * num::operator==(PyObj * in){
    if (typeid(*in) == typeid(num)){
        num * temp = dynamic_cast<num * >(in);
        return new boolean(this->data == temp -> get());
    }
    return 0;
}

PyObj * num::operator<(PyObj * in){
    if (typeid(*in) == typeid(num)){
        num * temp = dynamic_cast<num * >(in);
        return new boolean(this->data < temp -> get());
    }
    return 0;
}

PyObj * num::operator<=(PyObj * in){
    if (typeid(*in) == typeid(num)){
        num * temp = dynamic_cast<num * >(in);
        return new boolean(this->data <= temp -> get());
    }
    return 0;
}

PyObj * num::operator!=(PyObj * in){
    if (typeid(*in) == typeid(num)){
        num * temp = dynamic_cast<num * >(in);
        return new boolean(this->data != temp -> get());
    }
    return 0;
}

PyObj * num::operator+(PyObj * in){
    if (typeid(*in) == typeid(num)){
        num * temp = dynamic_cast<num * >(in);
        return new num(this->data + temp -> get());
    }
    return 0;
}

PyObj * num::operator*(PyObj * in){
    if (typeid(*in) == typeid(num)){
        num * temp = dynamic_cast<num * >(in);
        return new num(this->data * temp -> get());
    }
    return 0;
}

PyObj * num::power(PyObj * in){
    if (typeid(*in) == typeid(num)){
        num * temp = dynamic_cast<num * >(in);
        return new num(pow(this->data,temp -> get()));
    }
    return 0;
}

PyObj * num::operator-(PyObj * in){
    if (typeid(*in) == typeid(num)){
        num * temp = dynamic_cast<num * >(in);
        return new num(this->data - temp -> get());
    }
    return 0;
}

PyObj * num::true_div(PyObj * in){
    if (typeid(*in) == typeid(num)){
        num * temp = dynamic_cast<num * >(in);
        return new num(this->data / temp -> get());
    }
    return 0;
}

PyObj * num::operator%(PyObj * in){
    if (typeid(*in) == typeid(num)){
        num * temp = dynamic_cast<num * >(in);
        return new num(this->data % temp -> get());
    }
    return 0;
}


PyObj * num::str(){
    std::stringstream stream;
    stream << data;
    return new string(stream.str());
}

int num::to_int(){
    return data;
}


std::string num::repr(){
    return std::string("int");
}

bool num::truth(){
    return bool(data);
}



num::~num(){
};

string::string(std::string in)
{
    data = in;
}

PyObj * string::operator+(PyObj * in)
{
    if (typeid(*in) == typeid(string)){
        string * temp = dynamic_cast<string * >(in);
        return new string(this->data + temp -> get());
    }
    return 0;
}

PyObj * string::operator*(PyObj * in)
{
    int i, val;
    std::string temp_str;
    if (typeid(*in) == typeid(num)){
        num * temp = dynamic_cast<num * >(in);
        val = temp -> get();
        if (val <= 0)
            return new string("");
        else
            for(i = 0; i < val; i++)
                temp_str = this -> data + temp_str;
        return new string(temp_str);
    }
    return 0;
}

PyObj * string::str(){
    return new string(data);
}

int string::to_int(){
    return atoi(data.c_str());
}


std::string string::repr(){
    return std::string("string");
}

bool string::truth(){
    return data == std::string("");
}


string::~string(){
};


fun::fun(PyObj * (*f)(std::vector<PyObj *>))
{
    this -> f =  f;
}

PyObj * fun::str(){
    return new string("<function>");
}


PyObj * fun::run(std::vector<PyObj *> args){
    return f(args);
}

std::string fun::repr(){
    return std::string("function");
}


fun::~fun(){
};

boolean::boolean(bool in){
    data = in;
}

PyObj * boolean::operator&&(PyObj * in){
    if (typeid(*in) == typeid(boolean)){
        boolean * temp = dynamic_cast<boolean * >(in);
        return new boolean(this->data && temp -> get());
    }
    return 0;
}

PyObj * boolean::operator||(PyObj * in){
    if (typeid(*in) == typeid(boolean)){
        boolean * temp = dynamic_cast<boolean * >(in);
        return new boolean(this->data || temp -> get());
    }
    return 0;
}

PyObj * boolean::operator!(){
        return new boolean(!this->data);
}


PyObj * boolean::operator>(PyObj * in){
    if (typeid(*in) == typeid(boolean)){
        boolean * temp = dynamic_cast<boolean * >(in);
        return new boolean(this->data > temp -> get());
    }
    return 0;
}

PyObj * boolean::operator>=(PyObj * in){
    if (typeid(*in) == typeid(boolean)){
        boolean * temp = dynamic_cast<boolean * >(in);
        return new boolean(this->data >= temp -> get());
    }
    return 0;
}

PyObj * boolean::operator==(PyObj * in){
    if (typeid(*in) == typeid(boolean)){
        boolean * temp = dynamic_cast<boolean * >(in);
        return new boolean(this->data == temp -> get());
    }
    return 0;
}

PyObj * boolean::operator<(PyObj * in){
    if (typeid(*in) == typeid(boolean)){
        boolean * temp = dynamic_cast<boolean * >(in);
        return new boolean(this->data < temp -> get());
    }
    return 0;
}

PyObj * boolean::operator<=(PyObj * in){
    if (typeid(*in) == typeid(boolean)){
        boolean * temp = dynamic_cast<boolean * >(in);
        return new boolean(this->data <= temp -> get());
    }
    return 0;
}

PyObj * boolean::operator!=(PyObj * in){
    if (typeid(*in) == typeid(boolean)){
        boolean * temp = dynamic_cast<boolean * >(in);
        return new boolean(this->data != temp -> get());
    }
    return 0;
}

PyObj * boolean::operator+(PyObj * in){
    if (typeid(*in) == typeid(boolean)){
        boolean * temp = dynamic_cast<boolean * >(in);
        return new num(this->data + temp -> get());
    }
    return 0;
}

PyObj * boolean::operator*(PyObj * in){
    if (typeid(*in) == typeid(boolean)){
        boolean * temp = dynamic_cast<boolean * >(in);
        return new num(this->data * temp -> get());
    }
    return 0;
}

PyObj * boolean::power(PyObj * in){
    if (typeid(*in) == typeid(boolean)){
        boolean * temp = dynamic_cast<boolean * >(in);
        return new num(pow(this->data,temp -> get()));
    }
    return 0;
}

PyObj * boolean::operator-(PyObj * in){
    if (typeid(*in) == typeid(boolean)){
        boolean * temp = dynamic_cast<boolean * >(in);
        return new num(this->data - temp -> get());
    }
    return 0;
}

PyObj * boolean::true_div(PyObj * in){
    if (typeid(*in) == typeid(boolean)){
        boolean * temp = dynamic_cast<boolean * >(in);
        return new num(this->data / temp -> get());
    }
    return 0;
}

PyObj * boolean::operator%(PyObj * in){
    if (typeid(*in) == typeid(boolean)){
        boolean * temp = dynamic_cast<boolean * >(in);
        return new num(this->data % temp -> get());
    }
    return 0;
}


PyObj * boolean::str(){
    if (data)
        return new string(std::string("True"));
    else
        return new string(std::string("False"));
}

std::string boolean::repr(){
    return std::string("boolean");
}

int boolean::to_int(){
    return data;
}


bool boolean::truth(){
    return data;
}

boolean::~boolean(){
};



void builtins(std::map<std::string, PyObj *> & dict){
    dict[std::string("print")] = new fun(&print);
    dict[std::string("input")] = new fun(&input);
    dict[std::string("int")] = new fun(&to_int);
}

PyObj * print(std::vector<PyObj *> args){
    std::vector<PyObj *>::reverse_iterator it = args.rbegin();
    while(it != args.rend()){
        std::cout << dynamic_cast<string *>((*it) -> str())->get() << " ";
        it++;
    }
    std::cout << std::endl;
    return 0;
}

PyObj * input(std::vector<PyObj *> args){
    if (args.size() != 0)
        throw Scanner::my_exception(0,0,"Type Error: input() takes 0 arguments\
 (given " + itoa(args.size()) + ")" ,
                Scanner::my_exception::exec);
    std::string in;
    std::cin >> in;
    return new string(in);
}

PyObj * to_int(std::vector<PyObj *> args){
    if (args.size() != 1)
        throw Scanner::my_exception(0,0,"Type Error: int() takes 1 arguments\
 (given " + itoa(args.size()) + ")" ,
                Scanner::my_exception::exec);
    PyObj * in = args[0];
    return new num(in -> to_int());
}


