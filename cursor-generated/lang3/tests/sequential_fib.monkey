let fib = fn(n) {
    if (n < 2) { n } else { fib(n - 1) + fib(n - 2) }
};
let t1 = fib(24);
let t2 = fib(24);
puts(t1 + t2);
