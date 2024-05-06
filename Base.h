#pragma once

#include "polinome.h"

struct Bnode {
    Polinome pol;
    Bnode* next = nullptr;
    bool b = 0;
};

class Base
{
public:
    Bnode* L;
    int size = 0;

    void push(Polinome p);
    void pop(Bnode* &t);
    void clear();

    Base();
    Base(std::ifstream in);

    ~Base();

    Bnode* operator[](int n);

    void SaveToFile(std::ofstream out);
};

