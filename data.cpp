#include "data.h"

data::data() {
    k = 0;
    step = 0;
    st.assign(27, 0);
}

data::data(int k_) {
    st.assign(27, 0);
    step = 0;
    k = k_;
}

data::data(std::string s) {
    st.assign(27, 0);

    std::string k_;

    int i = 0;
    while (i < s.size() && IsNum(s[i]) || s[i] == '-' || s[i] == '+') {
        k_ += s[i];
        ++i;
    }

    if (k_.size() <= 1) {
        if (k_[0] == '+' || k_.size() == 0) {
            k = 1;
        }
        else if (k_[0] == '-') {
            k = -1;
        }
        else {
            k = stoi(k_);
        }
    }
    else {
        k = stoi(k_);
    }

    step = 0;

    while (i < s.size()) {
        if (i + 1 <= s.size() && Let(s[i + 1]) || s[i] == s.back()) {
            ++st[s[i] - 'a'];
            ++i;
            ++step;
        }
        else {
            int let = s[i] - 'a';

            i += 2;

            std::string num;

            while (i < s.size() && IsNum(s[i])) {
                num += s[i];
                ++i;
            }

            st[let] += stoi(num);
            step += stoi(num);
        }
    }
}

data::data(const data& other) {
    k = other.k;
    step = other.step;
    st = other.st;
}

int data::Check(data other) {

    for (int i = 0; i < 26; ++i) {
        if (st[i] != other.st[i]) {
            return 0;
        }
    }

    return (k == other.k) + 1;
}

bool data::operator==(data other) {
    if (Check(other) == 2) return 1;
    return 0;
}

data data::operator+(data other) {
    other.k += k;
    return other;
}

void data::operator=(data other) {
    k = other.k;
    step = other.step;
    st = other.st;
    return;
}

void data::operator=(int num) {
    st.assign(27, 0);
    step = 0;
    k = num;
    return;
}

void data::operator+=(data other) {
    *this = *this + other;
    return;
}

data data::operator*(data other) {
    data ans;
    
    if (k == 0 || other.k == 0) {
        ans;
    }
    ans.k = k * other.k;
    ans.step = step + other.step;

    for (int i = 0; i < st.size(); ++i) {
        ans.st[i] = st[i] + other.st[i];
    }

    return ans;
}

data data::operator/(data other) {
    data ans = *this;

    ans.k /= other.k;
    int let = 0;

    for (int i = 0; i < 26; ++i) {
        if (st[i]) {
            let = i;
            break;
        }
    }

    ans.st[let] -= other.st[let];
    step -= other.st[let];

    return ans;
}

bool data::operator>(data other) {
    if (step > other.step) return 1;
    if (step < other.step) return 0;

    int i = 0;
    int j = 0;

    if (*this == other) return 0;
    if (Check(other) == 1) return k > other.k;

    while (st[i] == 0 && i < 26) ++i;
    while (other.st[j] == 0 && j < 26) ++j;

    while (i == j && st[i] == other.st[j]) {
        ++i;
        ++j;
    }

    if (i < j) return 1;
    if (i > j) return 0;
    return st[i] > other.st[j];

}

int fact(int x) {
    if (x <= 1) return 1;
    return x * fact(x - 1);
}

data data::GetDef(char let, int n) {
    if (n > st[let - 'a']) {
        data ans(0);
        return ans;
    } 

    data ans;
    ans = *this;

    if (n == st[let - 'a']) {
        ans.k *= fact(n);
        ans.st[let - 'a'] = 0;
        return ans;
    }

    ans.k *= fact(st[let - 'a']) / fact(st[let - 'a'] - n);
    ans.st[let - 'a'] -= n;

    return ans;
}

bool data::empty() {    
    for (int i = 0; i < 26; ++i) {
        if (st[i]) return 0;
    }
    return 1;
}

std::string data::GetStr() {
    std::string ans;

    if (empty()) return std::to_string(k);

    if (k == 0) return "0";
    if (k == -1) ans += '-';
    else if (k != 1) ans += std::to_string(k);

    for (int i = 0; i < 27; ++i) {
        if (st[i] == 1) {
            ans += 'a' + i;
        }
        else if (st[i] > 1) {
            ans += 'a' + i;
            ans += '^';
            ans += std::to_string(st[i]);
        }
    }

    return ans;
}