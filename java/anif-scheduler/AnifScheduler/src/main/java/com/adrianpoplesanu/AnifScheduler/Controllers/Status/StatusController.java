package com.adrianpoplesanu.AnifScheduler.Controllers.Status;

import com.adrianpoplesanu.AnifScheduler.Models.Status.StatusModel;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class StatusController {
    /*@GetMapping("/")
    String index() {
        return "Buna dimineata";
    }*/

    @GetMapping("/status")
    StatusModel status() {
        return new StatusModel(200,"Everything looks fine!");
    }

    @GetMapping("/check2")
    StatusModel check2() {
        return new StatusModel(200,"Everything looks fine!");
    }
}
