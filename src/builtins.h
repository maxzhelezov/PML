//Модуль для стандартных встроенных функций
#ifndef __BUILTINS__HEADER
#define __BUILTINS__HEADER

#include <string>
#include <map>
#include <stack>
#include <vector>

// Абстрактный класс питон-объекта
class PyObj{

public:
    virtual PyObj * operator+(PyObj *) = 0; 
    virtual PyObj * power(PyObj *) = 0; 
    virtual PyObj * operator-(PyObj *) = 0; 
    virtual PyObj * true_div(PyObj *) = 0; 
    virtual PyObj * operator%(PyObj *) = 0;
    virtual PyObj * operator*(PyObj *) = 0; 
    virtual PyObj * str() = 0;

    virtual ~PyObj(){};
};

class num: public PyObj{
    int data;
public:
    num(int);
    inline int get(){return data;};
    virtual PyObj * operator+(PyObj *); 
    virtual PyObj * operator-(PyObj *); 
    virtual PyObj * power(PyObj *); 
    virtual PyObj * operator*(PyObj *); 
    virtual PyObj * true_div(PyObj *); 
    virtual PyObj * operator%(PyObj *);
    virtual PyObj * str();

    virtual ~num();
};

class fun: public PyObj{
    void (*f)(std::vector<PyObj *>);
public:
    fun(void (*f)(std::vector<PyObj *>));
    virtual PyObj * operator+(PyObj *){return 0;}
    virtual PyObj * power(PyObj *){return 0;}
    virtual PyObj * true_div(PyObj *){return 0;} 
    virtual PyObj * operator%(PyObj *){return 0;}
    virtual PyObj * operator*(PyObj *){return 0;}
    virtual PyObj * operator-(PyObj *){return 0;} 
    void run(std::vector<PyObj *>); //вызвать функцию
    virtual PyObj * str();

    virtual ~fun();
};

class name: public PyObj{
    std::string data;
public:
    name(std::string);
    inline std::string get(){return data;};
    virtual PyObj * operator+(PyObj *) {return 0;} 
    virtual PyObj * power(PyObj *){return 0;} 
    virtual PyObj * operator-(PyObj *){return 0;} 
    virtual PyObj * true_div(PyObj *){return 0;} 
    virtual PyObj * operator%(PyObj *){return 0;}
    virtual PyObj * operator*(PyObj *){return 0;} 
    virtual PyObj * str();

    virtual ~name();
};

class string: public PyObj{
    std::string data;
public:
    string(std::string);
    inline std::string get(){return data;};
    virtual PyObj * operator+(PyObj *); 
    virtual PyObj * power(PyObj *){return 0;} 
    virtual PyObj * operator-(PyObj *) {return 0;} 
    virtual PyObj * operator*(PyObj *); 
    virtual PyObj * str();
    virtual PyObj * true_div(PyObj *){return 0;} 
    virtual PyObj * operator%(PyObj *){return 0;}
    
    virtual ~string();
};


void builtins(std::map<std::string, PyObj*> &);

void print(std::vector<PyObj *>);

#endif
