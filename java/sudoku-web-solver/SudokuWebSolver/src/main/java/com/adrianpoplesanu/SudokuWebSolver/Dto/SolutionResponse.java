package com.adrianpoplesanu.SudokuWebSolver.Dto;

public class SolutionResponse {
    int solution[][];

    public SolutionResponse(int[][] solution) {
        this.solution = solution;
    }

    public int[][] getSolution() {
        return solution;
    }

    public void setSolution(int[][] solution) {
        this.solution = solution;
    }
}
