package com.adrianpoplesanu.sudoku;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class SudokuSolver {
    private int[][] board = new int[9][9];
    private int[][] solution = new int[9][9];
    private boolean foundSolution;

    private void readBoard() throws FileNotFoundException {
        Scanner scanner = new Scanner(new File("res/board.txt"));
        int i = 0, j;
        while(scanner.hasNextLine()) {
            String line = scanner.nextLine();
            if (line.contains("---")) {
                continue;
            }
            String[] portions = line.split(" ");
            j = 0;
            for (String portion : portions) {
                if (portion.equals("-")) board[i][j++] = 0;
                else if (portion.equals("|")) continue;
                else board[i][j++] = Integer.valueOf(portion);
            }
            i++;
        }
        scanner.close();
    }

    private void printBoard(int[][] a) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                System.out.print(a[i][j] + " ");
            }
            System.out.println();
        }
    }

    private void copyBoard() {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                solution[i][j] = board[i][j];
            }
        }
    }

    public void solve() {
        foundSolution = false;
        solve(0, 0);
    }

    private void solve(int i, int j) {
        if (j >= 9) {
            j = 0;
            i++;
        }
        if (i < 9 && j < 9) {
            if (board[i][j] == 0) {
                for (int k = 1; k <= 9; k++) {
                    solution[i][j] = k;
                    if (checkTempSolution(solution, i, j)) solve(i, j + 1);
                    if (foundSolution) return;
                }
            } else {
                solve(i,j + 1);
            }
            //if (foundSolution) return;
            if (board[i][j] == 0) solution[i][j] = 0;
        } else {
            foundSolution = true;
        }
    }

    private boolean checkTempSolution(int[][] solution, int i, int j) {
        for (int k = 0; k < 9; k++) if (k != j && solution[i][j] == solution[i][k]) return false;
        for (int k = 0; k < 9; k++) if (k != i && solution[i][j] == solution[k][j]) return false;
        if (squareCheck(solution, i, j, i / 3, j / 3)) return false;
        return true;
    }

    private boolean squareCheck(int[][] solution, int i, int j, int s1, int s2) {
        for (int k = s1 * 3; k < (s1 + 1) * 3; k++) {
            for (int l = s2 * 3; l < (s2 + 1) * 3; l++) {
                if (i != k && j != l && solution[i][j] == solution[k][l]) return true;
            }
        }
        return false;
    }

    public void printSolution() {
        if (foundSolution) {
            printBoard(solution);
        } else {
            System.out.println("no solution found");
        }
    }

    public static void main(String[] args) throws FileNotFoundException {
        SudokuSolver solver = new SudokuSolver();
        solver.readBoard();
        solver.copyBoard();
        solver.solve();
        solver.printSolution();
    }
}
