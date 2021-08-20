// ts2 p71 e2
#include <iostream>

template<typename T>
struct Nod {
    T info;
    Nod<T>* prev;
};

Nod<int>* varf;
int n;

template<typename T>
void push(Nod<T>* &varf, int i) {
    Nod<T>* c;
    if(!varf) {
        varf = new Nod<T>();
        varf->info = i;
        varf->prev = 0;
    } else {
        c = new Nod<T>();
        c->info = i;
        c->prev = varf;
        varf = c;
    }
}

template<typename T>
void pop(Nod<T>* &varf) {
    Nod<T>* c;
    if (!varf) std::cout << "stiva e vida\n";
    else {
        c = varf;
        std::cout << "am scos " << c->info << "\n";
        varf = varf->prev;
        delete c;
    }
}

int main(int argc, char *argv[]) {
    int man;
    std::cout << "n = "; std::cin >> n;
    push(varf, n);
    while(varf) {
        if (varf->info < 12) push(varf, varf->info + 2);
        else {
            man = varf->info;
            pop(varf);
            if (varf) varf->info = man - 1;
        }
    }
    std::cout << "f = " << man - 1 << "\n";
    return 0;
}
