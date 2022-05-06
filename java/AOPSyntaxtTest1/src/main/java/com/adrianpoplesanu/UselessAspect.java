package com.adrianpoplesanu;

import org.aspectj.lang.JoinPoint;
import org.aspectj.lang.ProceedingJoinPoint;
import org.aspectj.lang.annotation.Around;
import org.aspectj.lang.annotation.Aspect;
import org.aspectj.lang.annotation.Before;
import org.springframework.stereotype.Component;

@Aspect
@Component
public class UselessAspect {
    @Around("execution(* com.adrianpoplesanu.utils.UserService.hello(..))")
    private Object doNothing(ProceedingJoinPoint joinPoint) throws Throwable {
        // ...
        System.out.println("aaa");
        Object obj = joinPoint.proceed();
        System.out.println("bbb");
        return obj;
    }
}
