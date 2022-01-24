package com.adrianpoplesanu.SudokuWebSolver.Utils;

public class SudokuSolver {
    private int board[][] = new int[9][9];
    private int solution[][] = new int[9][9];
    private boolean foundSolution;

    public SudokuSolver() {

    }

    private void setBoard(int board[][]) {
        this.board = board;
        copyBoard();
        foundSolution = false;
    }

    private void copyBoard() {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                solution[i][j] = board[i][j];
            }
        }
    }

    private void solve(int i, int j) {
        if (j >= 9) {
            i++;
            j = 0;
        }
        if (i < 9 && j < 9) {
            if (board[i][j] == 0) {
                for (int k = 1; k <= 9; k++) {
                    solution[i][j] = k;
                    if (checkTempSolution(i, j)) solve(i, j + 1);
                    if (foundSolution) return;
                }
                solution[i][j] = 0;
            } else {
                solve(i, j + 1);
            }
        } else {
            foundSolution = true;
        }
    }

    private boolean checkTempSolution(int i, int j) {
        for (int k = 0; k < 9; k++) if (i != k && solution[i][j] == solution[k][j]) return false;
        for (int k = 0; k < 9; k++) if (j != k && solution[i][j] == solution[i][k]) return false;
        if (checkSquare(i, j)) return false;
        return true;
    }

    private boolean checkSquare(int i, int j) {
        int s1 = i / 3;
        int s2 = j / 3;
        for (int k = s1 * 3; k < (s1 + 1) * 3; k++) {
            for (int l = s2 * 3; l < (s2 + 1) * 3; l++) {
                if (k != i && l != j && solution[k][l] == solution[i][j]) return true;
            }
        }
        return false;
    }

    public int[][] solve(int board[][]) {
        setBoard(board);
        solve(0, 0);
        return solution;
    }

    public void testSolver() {
        int[][] board = {
                {7, 2, 0, 0, 0, 1, 9, 5, 0},
                {0, 4, 0, 0, 0, 8, 7, 3, 2},
                {9, 0, 0, 2, 0, 0, 0, 6, 0},
                {0, 0, 1, 3, 2, 0, 5, 0, 0},
                {0, 0, 2, 0, 0, 0, 0, 1, 0},
                {3, 0, 5, 7, 0, 0, 8, 2, 6},
                {2, 1, 0, 5, 0, 7, 6, 4, 0},
                {0, 8, 4, 1, 3, 6, 0, 0, 0},
                {0, 3, 0, 4, 9, 2, 0, 8, 0}
        };
        int[][] result = solve(board);
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                System.out.print(result[i][j] + " ");
            }
            System.out.println();
        }
    }
}
