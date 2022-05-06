package com.adrianpoplesanu.AOPTester4;

import org.aspectj.lang.JoinPoint;
import org.aspectj.lang.annotation.Aspect;
import org.aspectj.lang.annotation.Before;
import org.springframework.stereotype.Component;

@Aspect
@Component
public class UselessAspect {
    @Before("execution(* Worker.work(..))")
    void soNothing(JoinPoint joinPoint) {
        System.out.println("before call Worker.work()");
    }
}
