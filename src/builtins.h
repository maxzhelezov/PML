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
    //logic
    virtual PyObj * operator&&(PyObj *) = 0; 
    virtual PyObj * operator||(PyObj *) = 0; 
    virtual PyObj * operator!() = 0;
    virtual PyObj * operator>(PyObj *) = 0; 
    virtual PyObj * operator>=(PyObj *) = 0;
    virtual PyObj * operator==(PyObj *) = 0; 
    virtual PyObj * operator<=(PyObj *) = 0; 
    virtual PyObj * operator<(PyObj *) = 0; 
    virtual PyObj * operator!=(PyObj *) = 0;

    // math
    virtual PyObj * operator+(PyObj *) = 0; 
    virtual PyObj * power(PyObj *) = 0; 
    virtual PyObj * operator-(PyObj *) = 0; 
    virtual PyObj * true_div(PyObj *) = 0; 
    virtual PyObj * operator%(PyObj *) = 0;
    virtual PyObj * operator*(PyObj *) = 0; 
    
    virtual PyObj * str() = 0;
    virtual std::string repr() = 0;
    virtual bool truth() = 0;
    
    virtual ~PyObj(){};
};

class num: public PyObj{
    int data;
public:
    num(int);
    inline int get(){return data;};
    //logic
    virtual PyObj * operator&&(PyObj *);
    virtual PyObj * operator||(PyObj *); 
    virtual PyObj * operator!(); 
    virtual PyObj * operator>(PyObj *); 
    virtual PyObj * operator>=(PyObj *);
    virtual PyObj * operator==(PyObj *); 
    virtual PyObj * operator<=(PyObj *); 
    virtual PyObj * operator<(PyObj *); 
    virtual PyObj * operator!=(PyObj *);
    
    //math
    virtual PyObj * operator+(PyObj *); 
    virtual PyObj * operator-(PyObj *); 
    virtual PyObj * power(PyObj *); 
    virtual PyObj * operator*(PyObj *); 
    virtual PyObj * true_div(PyObj *); 
    virtual PyObj * operator%(PyObj *);
    
    virtual PyObj * str();
    virtual std::string repr();
    virtual bool truth();

    virtual ~num();
};

class fun: public PyObj{
    void (*f)(std::vector<PyObj *>);
public:
    fun(void (*f)(std::vector<PyObj *>));
    //logic
    virtual PyObj * operator&&(PyObj *){return 0;} 
    virtual PyObj * operator||(PyObj *){return 0;} 
    virtual PyObj * operator!(){return 0;}
    virtual PyObj * operator>(PyObj *){return 0;} 
    virtual PyObj * operator>=(PyObj *){return 0;}
    virtual PyObj * operator==(PyObj *){return 0;} 
    virtual PyObj * operator<=(PyObj *){return 0;} 
    virtual PyObj * operator<(PyObj *){return 0;} 
    virtual PyObj * operator!=(PyObj *){return 0;}
    
    //math
    virtual PyObj * operator+(PyObj *){return 0;}
    virtual PyObj * power(PyObj *){return 0;}
    virtual PyObj * true_div(PyObj *){return 0;} 
    virtual PyObj * operator%(PyObj *){return 0;}
    virtual PyObj * operator*(PyObj *){return 0;}
    virtual PyObj * operator-(PyObj *){return 0;} 
    
    void run(std::vector<PyObj *>); //вызвать функцию
    virtual PyObj * str();
    virtual std::string repr();
    virtual bool truth(){return 0;}

    virtual ~fun();
};


class string: public PyObj{
    std::string data;
public:
    string(std::string);
    inline std::string get(){return data;};
    //logic
    virtual PyObj * operator&&(PyObj *){return 0;} 
    virtual PyObj * operator||(PyObj *){return 0;} 
    virtual PyObj * operator!(){return 0;}
    virtual PyObj * operator>(PyObj *){return 0;} 
    virtual PyObj * operator>=(PyObj *){return 0;}
    virtual PyObj * operator==(PyObj *){return 0;} 
    virtual PyObj * operator<=(PyObj *){return 0;} 
    virtual PyObj * operator<(PyObj *){return 0;} 
    virtual PyObj * operator!=(PyObj *){return 0;}
    //math
    virtual PyObj * operator+(PyObj *); 
    virtual PyObj * power(PyObj *){return 0;} 
    virtual PyObj * operator-(PyObj *) {return 0;} 
    virtual PyObj * operator*(PyObj *); 
    virtual PyObj * true_div(PyObj *){return 0;} 
    virtual PyObj * operator%(PyObj *){return 0;}
    
    virtual PyObj * str();
    virtual std::string repr();
    virtual bool truth();
    
    virtual ~string();
};

class boolean: public PyObj{
    bool data;
public:
    boolean(bool);
    inline int get(){return data;};
    //logic
    virtual PyObj * operator&&(PyObj *);
    virtual PyObj * operator||(PyObj *);
    virtual PyObj * operator!();
    virtual PyObj * operator>(PyObj *);
    virtual PyObj * operator>=(PyObj *);
    virtual PyObj * operator==(PyObj *);
    virtual PyObj * operator<=(PyObj *);
    virtual PyObj * operator<(PyObj *);
    virtual PyObj * operator!=(PyObj *);
    
    //math
    virtual PyObj * operator+(PyObj *);
    virtual PyObj * operator-(PyObj *); 
    virtual PyObj * power(PyObj *);
    virtual PyObj * operator*(PyObj *); 
    virtual PyObj * true_div(PyObj *);
    virtual PyObj * operator%(PyObj *);
    
    virtual PyObj * str();
    virtual std::string repr();
    virtual bool truth();

    virtual ~boolean();
};




void builtins(std::map<std::string, PyObj*> &);

void print(std::vector<PyObj *>);

#endif
