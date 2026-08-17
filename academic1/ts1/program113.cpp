/*
   exercise: 113
   description: generate round-robin fixtures for n players
   command: echo 5 | ./program113
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

void rotatePlayers(int players[], int totalPlayers) {
    int lastPlayer = players[totalPlayers - 1];

    // Player 1 stays at index 0; all other players rotate one position.
    for (int i = totalPlayers - 1; i >= 2; i--) {
        players[i] = players[i - 1];
    }
    players[1] = lastPlayer;
}

void generateFixtures(int n) {
    int players[52];
    int totalPlayers = n;

    if (totalPlayers % 2 != 0) {
        totalPlayers++;
    }

    for (int i = 0; i < n; i++) {
        players[i] = i + 1;
    }
    if (totalPlayers > n) {
        players[totalPlayers - 1] = 0; // fictive player
    }

    for (int round = 1; round < totalPlayers; round++) {
        std::cout << "Round " << round << ":\n";

        for (int i = 0; i < totalPlayers / 2; i++) {
            int firstPlayer = players[i];
            int secondPlayer = players[totalPlayers - 1 - i];

            if (firstPlayer == 0) {
                std::cout << "  Player " << secondPlayer << " rests\n";
            } else if (secondPlayer == 0) {
                std::cout << "  Player " << firstPlayer << " rests\n";
            } else {
                std::cout << "  " << firstPlayer << " - " << secondPlayer << '\n';
            }
        }

        rotatePlayers(players, totalPlayers);
    }
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int n;
    std::cin >> n;
    generateFixtures(n);

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}
