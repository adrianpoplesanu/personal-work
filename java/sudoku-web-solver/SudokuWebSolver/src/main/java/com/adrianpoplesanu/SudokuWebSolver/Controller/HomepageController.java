package com.adrianpoplesanu.SudokuWebSolver.Controller;

import com.adrianpoplesanu.SudokuWebSolver.Dto.SolutionRequest;
import com.adrianpoplesanu.SudokuWebSolver.Dto.SolutionResponse;
import com.adrianpoplesanu.SudokuWebSolver.Utils.SudokuSolver;
import org.springframework.http.MediaType;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.ResponseBody;

import javax.servlet.http.HttpServletRequest;

@Controller
@RequestMapping(value = "/")
public class HomepageController {
    @RequestMapping(method = RequestMethod.GET)
    @ResponseBody
    public String index() {
        //SudokuSolver s;
        //Hahaha hahaha;
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
    //public SolutionResponse solve2(HttpServletRequest request) {
        //System.out.println(solutionRequest.getBoard());
        //SudokuSolver sudokuSolver = new SudokuSolver();
        //int[][] solution = sudokuSolver.testSolver();
        //return new SolutionResponse(solution);
        return new SolutionResponse(solutionRequest.getBoard());
    }
}
