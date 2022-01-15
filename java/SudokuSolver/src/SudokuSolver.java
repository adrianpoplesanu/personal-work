public class SudokuSolver {
    private int[][] board = new int[9][9];
    private int[][] solution = new int[9][9];
    private boolean foundSolution;

    private void setBoard(int[][] board) {
        this.board = board;
        copyBoard();
        foundSolution = false;
    }

    private int[][] getSolution() {
        return solution;
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
        for (int k = 0; k < 9; k++) if (k != j && solution[i][k] == solution[i][j]) return false;
        for (int k = 0; k < 9; k++) if (k != i && solution[k][j] == solution[i][j]) return false;
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

    private void copyBoard() {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                solution[i][j] = board[i][j];
            }
        }
    }

    public int[][] solve(int[][] board) {
        setBoard(board);
        solve(0, 0);
        return getSolution();
    }

    public static void main(String[] args) {
        SudokuSolver sudokuSolver = new SudokuSolver();
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
        int[][] solution = sudokuSolver.solve(board);
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                System.out.print(solution[i][j] + " ");
            }
            System.out.println();
        }
    }
}
