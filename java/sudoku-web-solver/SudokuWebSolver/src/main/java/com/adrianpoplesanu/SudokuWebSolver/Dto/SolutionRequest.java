package com.adrianpoplesanu.SudokuWebSolver.Dto;

import com.fasterxml.jackson.annotation.JsonProperty;

import java.io.Serializable;

public class SolutionRequest {
    int board[][];

    public int[][] getBoard() {
        return board;
    }

    public void setBoard(int[][] board) {
        this.board = board;
    }
    /*private String board;

    public String getBoard() {
        return board;
    }

    public void setBoard(String board) {
        this.board = board;
    }*/
}
