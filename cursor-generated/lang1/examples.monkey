let name = "Monkey";
puts("Hello from " + name + "!");

let factorial = fn(n) {
    if (n < 2) { 1 } else { n * factorial(n - 1) }
};
puts(factorial(10));

let map = fn(arr, f) {
    if (len(arr) == 0) {
        []
    } else {
        push(map(rest(arr), f), f(first(arr)))
    }
};
let double = fn(x) { x * 2 };
let nums = [1, 2, 3, 4, 5];
puts(map(nums, double));

let adder = fn(x) { fn(y) { x + y } };
let addFive = adder(5);
puts(addFive(10));
