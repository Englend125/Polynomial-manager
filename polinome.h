#pragma once

#include "data.h"
#include <QMessageBox>
#include <QString>
#include <QInputDialog>
#include <fstream>
#include <random>

struct node {
    node* next = nullptr;
    data d;
    bool b = 0;
    node() {
        next = nullptr;
        d = -1;
        b = 0;
    }
};

class Polinome
{
public:

    node* L;
    QMessageBox warning;
    int size = 0;

    Polinome();
    Polinome(const Polinome& other);

    void push(node* &t, data &mon);
    void pop(node* &t);
    void clear();
    void DelNull();

    void ShowWarning(std::string problem);
    std::string Get();
    bool Check(std::string& str);

    Polinome(std::string str);
    ~Polinome();

    int GetInPoint(std::vector<std::pair<int, int>> val);
    Polinome GetDef(char let, int n);
    std::vector<int> GetRoots();
    Polinome operator-();
    Polinome operator+(Polinome other);
    Polinome operator*(Polinome other);
    std::pair<Polinome, Polinome>operator/(Polinome other);
    void operator=(Polinome other);
    bool OneVCheck();

    bool operator==(Polinome other);

    std::string GetStr();
};
