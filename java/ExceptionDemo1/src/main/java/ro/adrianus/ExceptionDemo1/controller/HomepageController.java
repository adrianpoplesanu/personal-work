package ro.adrianus.ExceptionDemo1.controller;

import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.ExceptionHandler;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.ResponseBody;

@Controller
public class HomepageController {
    @ResponseBody
    @GetMapping("/")
    public String index() {
        return "buna dimineata #2";
    }

    @ResponseBody
    @GetMapping("/raise")
    public String raiseError() {
        if ( 1 < 5) {
            throw new RuntimeException("ala bala portocala");
        }
        return "nu s-a raise-uit";
    }

    // comentezi asta si vezi o eroare in browser
    // daca o lasi goala primesti un 200 dar nu se incarca nimic pe pagina
    // daca o lasi cum e acum atunci le primesti pe amandoua in consola
    @ExceptionHandler
    public void handleException(HttpServletRequest request,
                                HttpServletResponse response,
                                Exception e) {
        // ...
        //throw new RuntimeException("alta exceptie a fost ridicata");
    }
}
