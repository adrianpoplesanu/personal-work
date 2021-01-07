package com.adrianpoplesanu.OnlineReservations3.Controllers;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.Reader;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class StatusController {

	@GetMapping("/check2.txt")
	public String check2() {
		return "check2.txt\nStatus: OK 200";
	}
	
	@GetMapping("/ls-la")
	public String ls_la() {
		String output;
		ProcessBuilder pb = new ProcessBuilder();
		pb.command("pwd");
		try {
			Process p = pb.start();
			//OutputStream os = p.getOutputStream();
			int exitCode = p.waitFor();
			BufferedReader reader = 
	                new BufferedReader(new InputStreamReader(p.getInputStream()));
			StringBuilder builder = new StringBuilder();
			String line = null;
			while ( (line = reader.readLine()) != null) {
				builder.append(line);
				//builder.append(System.getProperty("line.separator"));
				builder.append("\n");
			}
			String result = builder.toString();
			output = "aaa: " + result;
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			output = "bbb";
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			output = "ccc";
		}
		
		return output;
	}
	
}
