package com.adrianpoplesanu.AOPTester2.aspect;

import org.aspectj.lang.ProceedingJoinPoint;
import org.aspectj.lang.annotation.Around;
import org.aspectj.lang.annotation.Aspect;
import org.springframework.stereotype.Component;

@Aspect
@Component
public class UselessAspect {
    @Around("@annotation(DoNothing)")
    public Object doNothing(ProceedingJoinPoint joinPoint) throws Throwable {
        System.out.println("doing nothing");
        Object result = joinPoint.proceed();
        return result;
    }
}
