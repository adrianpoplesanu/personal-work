package com.adrianpoplesanu.SudokuWebSolver.Service;

import com.adrianpoplesanu.SudokuWebSolver.Utils.SudokuSolver;
import org.springframework.stereotype.Service;

@Service
public class SudokuSolverService {
    private SudokuSolver sudokuSolver;

    public SudokuSolverService() {
        sudokuSolver = new SudokuSolver();
    }

    public int[][] solve(int[][] board) {
        return sudokuSolver.solve(board);
    }
}
