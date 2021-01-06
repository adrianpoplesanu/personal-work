// ts2 p45 e2
#include <iostream>
using namespace std;

int generate_helmet() {
    return rand() % 28;
}

bool check_all_helmets(int helmets[28]) {
    for (int i = 0; i < 28; ++i) {
        if (helmets[i] == 0) return false;
    }
    return true;
}

float calculate_price(int helmets[28]) {
    float sum = 0;
    for (int i = 0; i < 28; ++i) {
        //cout << helmets[i] << "\n";
        sum += 0.25 * helmets[i];
    }
    return sum;
}

int main(int argc, char *argv[]) {
    srand(time(NULL));

    int helmets[28];
    for (int i = 0; i < 28; i++) helmets[i] = 0;

    while(!check_all_helmets(helmets)) {
        int helmet = generate_helmet();
        helmets[helmet]++;
    }
    cout << calculate_price(helmets) << "\n";
    return 0;
}
