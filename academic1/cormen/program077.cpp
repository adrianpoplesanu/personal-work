/*
   exercise: 077
   page: 440
   description: greedy algorithm on a weighted matroid
   command: echo 7 4 70 2 60 4 50 3 40 1 30 4 20 6 10 | ./program077
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

// Each task i is one unit of time, due by time d[i], and costs penalty w[i] if late.
// A set of tasks is an independent set of the scheduling matroid when every task in it
// can finish by its deadline. GREEDY then returns a maximum-penalty independent set:
// the early tasks of an optimal schedule.
void read(int d[50], int w[50], int &n) {
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> d[i] >> w[i];
    }
}

void sort_by_weight(int order[50], int w[50], int n) {
    for (int i = 1; i <= n; i++) {
        order[i] = i;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (w[order[i]] < w[order[j]]) {
                std::swap(order[i], order[j]);
            }
        }
    }
}

// N_t(A) is the number of tasks in A whose deadline is t or earlier.
// A is independent iff N_t(A) <= t for every t = 1, ..., n.
bool independent(int d[50], int early[50], int n) {
    int count[50] = {0};
    for (int i = 1; i <= n; i++) {
        if (early[i]) {
            count[d[i]]++;
        }
    }
    int nt = 0;
    for (int t = 1; t <= n; t++) {
        nt += count[t];
        if (nt > t) {
            return false;
        }
    }
    return true;
}

// CLRS GREEDY(M, w). order[] is M.S sorted into monotonically decreasing weight.
void greedy(int d[50], int order[50], int n, int early[50]) {
    for (int i = 1; i <= n; i++) {
        early[i] = 0;
    }
    for (int k = 1; k <= n; k++) {
        int x = order[k];
        early[x] = 1;
        if (!independent(d, early, n)) {
            early[x] = 0;
        }
    }
}

// Early tasks in order of nondecreasing deadline, then the late tasks.
// The printed penalty is the total weight of the late tasks.
void canonical_schedule(int d[50], int w[50], int order[50], int early[50], int n,
                        int schedule[50], int &penalty) {
    int m = 0;
    for (int i = 1; i <= n; i++) {
        if (early[i]) {
            m++;
            schedule[m] = i;
        }
    }
    for (int i = 1; i <= m; i++) {
        for (int j = i + 1; j <= m; j++) {
            if (d[schedule[i]] > d[schedule[j]] ||
                (d[schedule[i]] == d[schedule[j]] && schedule[i] > schedule[j])) {
                std::swap(schedule[i], schedule[j]);
            }
        }
    }

    penalty = 0;
    for (int k = 1; k <= n; k++) {
        int x = order[k];
        if (!early[x]) {
            m++;
            schedule[m] = x;
            penalty += w[x];
        }
    }
}

void print_schedule(int schedule[50], int n, int penalty) {
    for (int i = 1; i <= n; i++) {
        if (i > 1) {
            std::cout << " ";
        }
        std::cout << schedule[i];
    }
    std::cout << "\n" << penalty << "\n";
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int d[50], w[50], order[50], early[50], schedule[50], n, penalty;
    read(d, w, n);
    sort_by_weight(order, w, n);
    greedy(d, order, n, early);
    canonical_schedule(d, w, order, early, n, schedule, penalty);
    print_schedule(schedule, n, penalty);

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}
