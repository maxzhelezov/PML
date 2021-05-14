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

num::~num(){
};

name::name(std::string in)
{
    data = in;
}

PyObj * name::str(){
    return new string(data);
}

name::~name(){
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

fun::~fun(){
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


