package com.adrianpoplesanu.ChartInterpreter.controller;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.multipart.MultipartFile;

import java.io.*;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.List;

@RestController
public class AnalyzeController {

    @PostMapping("/analyze-file")
    //@ResponseBody
    public List<String> analyzeFile(@RequestParam("file") MultipartFile file) throws IOException {
        InputStream inputStream = file.getInputStream();

        StringBuilder textBuilder = new StringBuilder();
        try (Reader reader = new BufferedReader(new InputStreamReader
                (inputStream, Charset.forName(StandardCharsets.UTF_8.name())))) {
            int c = 0;
            while ((c = reader.read()) != -1) {
                textBuilder.append((char) c);
            }
        }
        String content = textBuilder.toString();
        String values = "[";
        String labels = "[";

        String[] lines = content.split("\r?\n|\r");
        for (int i = 1; i < lines.length; i++) {
            if (i > 1) {
                values += ", ";
                labels += ", ";
            }
            String[] tokens = lines[i].split(",");
            values += tokens[1];
            labels += "\"" + tokens[0] + "\"";
        }

        values += "]";
        labels += "]";
        List<String> result = new ArrayList<>();
        result.add(values);
        result.add(labels);
        return result;
    }
}
