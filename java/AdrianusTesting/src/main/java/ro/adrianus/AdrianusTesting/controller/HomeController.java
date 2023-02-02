package ro.adrianus.AdrianusTesting.controller;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;

import java.util.Map;

@Controller
@RequestMapping("/")
public class HomeController {

    @GetMapping("/")
    @ResponseBody
    public String index(@RequestHeader Map<String, String> headers, @RequestParam(required=false) Map<String,String> qparams) {
        String result = "<div>Adrianus running with Springboot!</div>";
        result += "<div>--headers--</div>";
        for (Map.Entry<String, String> header : headers.entrySet()) {
            result += "<div>" + header.getKey() + ": " + header.getValue() + "</div>";
        }
        result += "<div>-/headers/-</div>";

        result += "<div>--qparams--</div>";
        for (Map.Entry<String, String> qparam : qparams.entrySet()) {
            result += "<div>" + qparam.getKey() + ": " + qparam.getValue() + "</div>";
        }
        result += "<div>-/qparams--</div>";
        return result;
    }
}
