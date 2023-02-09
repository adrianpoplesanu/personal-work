package com.adrianpoplesanu.SpringBootFiltersApplication1.filter;

import jakarta.servlet.*;
import jakarta.servlet.http.HttpServletRequest;
import org.springframework.stereotype.Component;

import java.io.IOException;

@Component
public class RequestForwarderFilter implements Filter {
    @Override
    public void doFilter(ServletRequest servletRequest, ServletResponse servletResponse, FilterChain filterChain) throws IOException, ServletException {
        System.out.println("sunt intr-un filtru");

        if (servletRequest instanceof HttpServletRequest) {
            String url = ((HttpServletRequest)servletRequest).getRequestURL().toString();
            String path = ((HttpServletRequest)servletRequest).getServletPath();
            String queryString = ((HttpServletRequest)servletRequest).getQueryString();

            System.out.println(url);
            System.out.println(path);
            System.out.println(queryString);
            if (path.equals("/adi/endpoint1")) {
                // forward
                HttpServletRequest httpServletRequest = (HttpServletRequest)servletRequest;
                httpServletRequest.getServletContext().getRequestDispatcher("/adrian/endpoint2").forward(servletRequest, servletResponse);
            } else {
                filterChain.doFilter(servletRequest, servletResponse);
            }
        } else {
            filterChain.doFilter(servletRequest, servletResponse);
        }
    }
}
