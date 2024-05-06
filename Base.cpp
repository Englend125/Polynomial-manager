#include "Base.h"

void Base::push(Polinome p) {
    Bnode* q = new Bnode;
    q->pol = p;
    
    q->next = L;
    L = q;
    ++size;
}

void Base::pop(Bnode* &t) {
    Bnode* q = t->next;

    t->pol = t->next->pol;
    t->b = t->next->b;
    t->next = t->next->next;

    delete q;
    --size;
}

void Base::clear() {
    while (!L->b) {
        pop(L);
    }
}

Base::Base() {
    Bnode* b = new Bnode;
    b->b = 1;
    L = b;
}

Base::Base(std::ifstream in) {
    Polinome b;
    push(b);
    size--;
    while (!in.eof()) {
        std::string new_p_;
        std::getline(in, new_p_);
        Polinome new_p(new_p_);
        push(new_p);
    }

    in.close();
}

Base::~Base() {
    clear();
    delete L;
}

void Base::SaveToFile(std::ofstream out) {
    Bnode* q = L;

    while (q != nullptr) {
        out << q->pol.GetStr() << '\n';
    }

    out.close();
}

Bnode* Base::operator[](int n) {
    Bnode* q = L;

    while (q != nullptr && n) {
        n--;
        q = q->next;
    }

    return q;
}