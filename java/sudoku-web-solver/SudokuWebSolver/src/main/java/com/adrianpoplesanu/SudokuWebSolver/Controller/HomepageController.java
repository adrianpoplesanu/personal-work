package com.adrianpoplesanu.SudokuWebSolver.Controller;

import com.adrianpoplesanu.SudokuWebSolver.Dto.SolutionRequest;
import com.adrianpoplesanu.SudokuWebSolver.Dto.SolutionResponse;
import com.adrianpoplesanu.SudokuWebSolver.Service.SudokuSolverService;
import com.adrianpoplesanu.SudokuWebSolver.Utils.SudokuSolver;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.ResponseBody;


@Controller
@RequestMapping(value = "/")
public class HomepageController {
    @Autowired
    private SudokuSolverService sudokuSolverService;

    @RequestMapping(method = RequestMethod.GET)
    @ResponseBody
    public String index() {
        SudokuSolver sudokuSolver = new SudokuSolver();
        sudokuSolver.testSolver();
        return "buna dimineata!";
    }

    @RequestMapping(value= "/solve", method = RequestMethod.POST)
    @ResponseBody
    public SolutionResponse solve() {
        SudokuSolver sudokuSolver = new SudokuSolver();
        int[][] solution = sudokuSolver.testSolver();
        return new SolutionResponse(solution);
    }

    @RequestMapping(value= "/solve/v2", method = RequestMethod.POST)
    @ResponseBody
    public SolutionResponse solve2(@RequestBody SolutionRequest solutionRequest) {
        int[][] board = solutionRequest.getBoard();
        int[][] solution = sudokuSolverService.solve(board);
        return new SolutionResponse(solution);
    }
}
