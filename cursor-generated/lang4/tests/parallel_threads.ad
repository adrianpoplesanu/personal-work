let fib = fn(n) {
    if (n < 2) { n } else { fib(n - 1) + fib(n - 2) }
};
let t1 = spawn(fib, 24);
let t2 = spawn(fib, 24);
puts(join(t1) + join(t2));
