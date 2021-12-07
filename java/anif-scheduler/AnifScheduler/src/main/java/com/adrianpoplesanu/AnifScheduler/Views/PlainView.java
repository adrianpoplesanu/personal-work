package com.adrianpoplesanu.AnifScheduler.Views;

import org.springframework.web.servlet.view.AbstractView;

import javax.servlet.ServletOutputStream;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.PrintWriter;
import java.util.Map;

public class PlainView extends AbstractView {
    @Override
    protected void renderMergedOutputModel(Map<String, Object> model, HttpServletRequest request, HttpServletResponse response) throws Exception {
        ServletOutputStream out = response.getOutputStream();
        out.println("<html><body><h1>Buna dimineata!</h1></body></html>");
    }
}
