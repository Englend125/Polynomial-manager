#pragma once

#include <vector>
#include <string>

class data
{
public:

    bool IsNum(char c) {
        return (c >= '0' && c <= '9');
    }

    bool Let(char c) {
        return (c >= 'a' && c <= 'z');
    }

    int k;
    int step;
    std::vector<int> st;

    data();

    data(int k_);

    data(std::string s);

    data(const data& other);

    ~data() {
        st.clear();
    }

    int Check(data other);
    std::string GetStr();

    data GetDef(char let, int n);

    bool operator==(data other);
    bool empty();

    data operator+(data other);
    data operator*(data other);
    data operator/(data other);

    bool operator>(data other);

    void operator=(data other);
    void operator=(int num);
    void operator+=(data other);
};

