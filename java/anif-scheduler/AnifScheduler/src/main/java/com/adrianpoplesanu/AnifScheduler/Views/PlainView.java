package com.adrianpoplesanu.AnifScheduler.Views;

import org.springframework.web.servlet.view.AbstractView;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.PrintWriter;
import java.util.Map;

public class PlainView extends AbstractView {
    @Override
    protected void renderMergedOutputModel(Map<String, Object> model, HttpServletRequest request, HttpServletResponse response) throws Exception {
        PrintWriter out = response.getWriter();
        //out.println("<!doctype html>");
        //out.println("<html><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\"></head><body><h1>Buna dimineata!</h1></body></html>");
        out.print("<html>Buna dimineata!</html>");
        out.flush();
    }
}
