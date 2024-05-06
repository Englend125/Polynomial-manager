#include "polinome.h"

//basic polinome_list functions

void Polinome::DelNull() {
    if (size > 1) {
        node* q = L;

        while (q && q->next) {
            if (q->d.k == 0 && size > 1) {
                pop(q);
            }
            q = q->next;
        }
    }
}

void Polinome::push(node* &t, data& n) {
    if (t->b) {
        t->d = n;
        t->b = 0;
        node* nb = new node;
        nb->b = 1;
        t->next = nb;
        ++size;
        return;
    }
    if (n.Check(t->d)) {
        t->d += n;
        DelNull();
    } else if (t->d > n) {
        push(t->next, n);
    } else {
        node* q = new node;
        q->d = n;

        q->next = t;
        t = q;
        ++size;
    }
}

void Polinome::pop(node*& t) {
    node* q = t->next;

    t->d = t->next->d;
    t->b = t->next->b;
    t->next = t->next->next;

    delete q;
    --size;
}

void Polinome::clear() {
    while (!L->b) {
        pop(L);
    }
}

//Checker help functions

bool IsLet(char c) {
    return c >= 'a' && c <= 'z';
}

bool IsNum(char c) {
    return c >= '1' && c <= '9';
}

std::string GetProblem(int i) {
    std::string p = "In position ";
    p += std::to_string(i + 1);
    p += ' ';
    return p;
}

void Polinome::ShowWarning(std::string problem) {
    QString s = QString::fromStdString(problem);

    warning.setText(s);
    warning.setWindowTitle("Error");
    warning.setStyleSheet("QMainWindow {color: #011638}"
        "QWidget {background: #9055A2;}"
        "QLabel {color: #011638}"
        "QPushButton {background: #D499B9; color: #011638}"
    );
    warning.show();
}

bool Polinome::Check(std::string& str) {
    if (str == "0") return 1;

    for (int i = 0; i < str.size(); ++i) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] - 'A' + 'a';
        }
    }

    try {
        int i = 0;
        int cur = 0;

        if (str[i] == '-' || str[i] == '+') {
            ++i;
        }

        while (i < str.size()) {
            //goings from first simbol and simbol after '+', '-' or '*'
            if ((cur == 0 || cur == 4) && IsLet(str[i])) {
                cur = 1;
                ++i;
                continue;
            }
            else if ((cur == 0 || cur == 4) && IsNum(str[i])) {
                cur = 2;
                ++i;
                continue;
            }
            else if ((cur == 0 || cur == 4)) {
                std::string p = GetProblem(i);
                p += "expected a variable or number without leading zeros.";
                throw p;
            }

            //goings from letter
            if (cur == 1 && str[i] == '^') {
                cur = 3;
                ++i;
                continue;
            }
            else if (cur == 1 && (str[i] == '+' || str[i] == '-' || str[i] == '*')) {
                cur = 4;
                ++i;
                continue;
            }
            else if (cur == 1 && IsLet(str[i])) {
                ++i;
                continue;
            }
            else if (cur == 1) {
                std::string p = GetProblem(i);
                p += "expexted '+', '-', '^' or a variable";
                throw p;
            }

            //goings from number 
            if (cur == 2 && IsLet(str[i])) {
                cur = 1;
                ++i;
                continue;
            }
            else if (cur == 2 && (str[i] == '+' || str[i] == '-' || str[i] == '*')) {
                cur = 4;
                ++i;
                continue;
            }
            else if (cur == 2 && (IsNum(str[i]) || str[i] == '0')) {
                ++i;
                continue;
            }
            else if (cur == 2) {
                std::string p = GetProblem(i);
                p += "expected '+', '-', number or variable";
                throw p;
            }

            //going from ^
            if (cur == 3 && IsNum(str[i])) {
                cur = 2;
                ++i;
                continue;
            }
            else if (cur == 3) {
                std::string p = GetProblem(i);
                p += "expected number";
                throw p;
            }
        }

        if (cur == 1 || cur == 2) return 1;
        else {
            throw (std::string)"Something wrong in back";
        }

    }
    catch (const std::string& problem) {
        ShowWarning(problem);
        return 0;
    }

}

//constructors and distructor

int GetRand() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution rr;
    int a = 0;
    a += rr(gen) % 30;

    return a;
}

QString GetKek() {
    std::ifstream in("Keks.txt");

    std::string a;
    int line = GetRand();

    while (line) {
        std::getline(in, a);
        --line;
    }

    return QString::fromStdString(a);
}

std::string Polinome::Get() {
    QString str = QInputDialog::getText(nullptr, "Try again", GetKek());

    return str.toStdString();
}

Polinome::Polinome(std::string str) {

    node* b = new node;
    b->b = 1;
    L = b;

    while (!Check(str)) {
        str = Get();
    }

    int i = 0;
    while (i < str.size()) {
        std::string new_elem;
        new_elem += str[i];
        ++i;

        while (i < str.size() && str[i] != '+' && str[i] != '-') {
            new_elem += str[i];
            ++i;
        }

        data new_data(new_elem);
        push(L, new_data);
    }

    DelNull();
}

Polinome::Polinome() {
    node* b = new node;
    b->b = 1;
    L = b;
}

Polinome::Polinome(const Polinome& other) {

    node* b = new node;
    b->b = 1;
    L = b;

    node* q;
    q = other.L;
    while (!q->b) {
        push(L, q->d);
        q = q->next;
    }
}

Polinome::~Polinome() {
    clear();
    delete L;
}

//polinome functions

void Polinome::operator=(Polinome other) {
    clear();
    node* q = other.L;

    while (!q->b) {
        data new_d = q->d;
        this->push(L, new_d);
        q = q->next;
    }
}

Polinome Polinome::operator-() {
    Polinome ans;
    ans = *this;
    
    node* q = ans.L;

    while (!q->b) {
        q->d.k *= -1;
        q = q->next;
    }

    return ans;
}

Polinome Polinome::operator+(Polinome other) {
    Polinome ans;

    node* q = L;

    while (!q->b) {
        ans.push(ans.L, q->d);
        q = q->next;
    }

    q = other.L;

    while (!q->b) {
        ans.push(ans.L, q->d);
        q = q->next;
    }

    ans.DelNull();

    return ans;
}

Polinome Polinome::operator*(Polinome other) {
    Polinome ans;

    node* q = other.L;

    while (!q->b) {
        node* r = L;
        while (!r->b) {
            data new_elem = q->d * r->d;
            ans.push(ans.L, new_elem);
            r = r->next;
        }
        q = q->next;
    }

    ans.DelNull();

    return ans;
}

bool Polinome::operator==(Polinome other) {
    node* q = L;
    node* m = other.L;

    while (!q->b && !m->b) {
        if (q->d == m->d) {
            q = q->next;
            m = m->next;
        } else {
            return 0;
        }
    }

    if (q->b && m->b) return 1;
    return 0;
}

std::pair<Polinome, Polinome> Polinome::operator/(Polinome other) {
    Polinome ans("0");
    Polinome ans_("0");

    if (GetStr() == "0") {
        return {ans, ans};
    }

    if (size < other.size || L->d.step < other.L->d.step) {
        return { ans, *this };
    }

    node* q = L;

    Polinome cur;

    while (cur.size < other.size) {
        cur.push(cur.L, q->d);
        q = q->next;
    }

    while (!q->b) {
        if (cur.L->d.k % other.L->d.k) {
            ans_.push(ans.L, cur.L->d);
            cur.pop(cur.L);

            cur.push(cur.L, q->d);
            q = q->next;
        } else {
            data d = cur.L->d / other.L->d;
            Polinome p(d.GetStr());
            ans.push(ans.L, d);

            cur = cur + (-other) * p;
            cur.DelNull();

            cur.push(cur.L, q->d);
            q = q->next;
        }
    }

    if (cur.L->d.k % other.L->d.k == 0) {
        data d = cur.L->d / other.L->d;
        Polinome p(d.GetStr());
        ans.push(ans.L, d);

        cur = cur + (-other) * p;
        cur.DelNull();
    }

    q = cur.L;

    while (!q->b) {
        ans_.push(ans_.L, q->d);
        q = q->next;
    }

    ans.DelNull();
    ans_.DelNull();

    return { ans, ans_ };
}

//Get in point functions

int step(int n, int x) {
    if (n < 0) {
        if (x % 2) return -step(-n, x);
        return step(-n, x);
    }
    if (x == 0) return 1;
    if (x % 2) return n * step(n, x - 1);
    return step(n * n, x / 2);
}

int Polinome::GetInPoint(std::vector<std::pair<int, int>> val) {
    int ans = 0;

    node* q = L;

    while (!q->b) {
        data cur = q->d;

        int cur_ans = cur.k;

        for (int i = 0; i < val.size(); ++i) {
            cur_ans *= step(val[i].second, cur.st[val[i].first]);
        }

        ans += cur_ans;
        q = q->next;
    }

    return ans;
}

Polinome Polinome::GetDef(char let, int n) {
    Polinome ans;

    node* q = L;
    while (!q->b) {
        data cur;
        cur = q->d.GetDef(let, n);
        ans.push(ans.L, cur);
        q = q->next;
    }

    ans.DelNull();

    return ans;
}

bool Polinome::OneVCheck() {
    try {
        node* q = L;
        int let = -1;
        while (!q->b) {
            data d;
            d = q->d;
            if (d.empty()) {
                q = q->next;
                continue;
            }

            for (int i = 0; i < 26; ++i) {
                if (d.st[i] && let == -1) {
                    let = i;
                }
                if (d.st[i] && i != let && let != -1) {
                    throw (std::string)"Polinome mast have one varivle";
                }
            }
            
            q = q->next;
        }


    } catch (std::string str) {
        ShowWarning(str);
        return 0;
    }

    return 1;
}

std::vector<int> Polinome::GetRoots() {
    node* q = L;

    int let = 0;

    for (int i = 0; i < 26; ++i) {
        if (q->d.st[i]) {
            let = i;
            break;
        }
    }

    while (!q->next->b) {
        q = q->next;
    }
    
    std::vector<int> ans;

    if (q->d.st[let]) {
        ans.push_back(0);
    }

    std::vector<int> for_check = { 1, -1 };

    int k = q->d.k;

    for (int i = 2; i * i < abs(k); ++i) {
        if (k % i == 0) {
            for_check.push_back(i);
            for_check.push_back(-i);
            for_check.push_back(k/i);
            for_check.push_back(-k/i);
        }
    }
    
    for (int i = 0; i < for_check.size(); ++i) {
        int val = GetInPoint({ {let, for_check[i]} });
        if (val == 0) {
            ans.push_back(for_check[i]);
        }
    }

    return ans;
}

std::string Polinome::GetStr() {
    node* q = L;
    std::string ans;

    while (!q->b) {
        std::string cur = q->d.GetStr();
        if (cur[0] != '-' && ans.size()) {
            ans += '+';
        }
        ans += cur;
        q = q->next;
    }

    return ans;
}