#include "builtins.h"
#include <typeinfo>
#include <string>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <cmath>

#define UN(x) (void)(x) 

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

PyObj * string::operator+(PyObj * in){UN(in); return 0;}
PyObj * string::operator*(PyObj * in){UN(in); return 0;}

PyObj * string::str(){
    return new string(data);
}

std::string string::repr(){
    return std::string("string");
}

bool string::truth(){
    return data == std::string("");
}


string::~string(){
};


fun::fun(void (*f)(std::vector<PyObj *>))
{
    this -> f =  f;
}

PyObj * fun::str(){
    return new string("<function>");
}


void fun::run(std::vector<PyObj *> args){
    f(args);
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

bool boolean::truth(){
    return data;
}

boolean::~boolean(){
};



void builtins(std::map<std::string, PyObj *> & dict){
    dict[std::string("print")] = new fun(&print);
}

void print(std::vector<PyObj *> args){
    std::vector<PyObj *>::reverse_iterator it = args.rbegin();
    while(it != args.rend()){
        std::cout << dynamic_cast<string *>((*it) -> str())->get() << " ";
        it++;
    }
    std::cout << std::endl;
}


