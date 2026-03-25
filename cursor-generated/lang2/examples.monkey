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

class Dog {
    fn init(name, age) {
        this.name = name;
        this.age = age;
    }
    fn bark() {
        puts("Woof! My name is " + this.name);
    }
    fn describe() {
        puts(this.name + " is a good dog");
    }
}

let rex = new Dog("Rex", 5);
rex.bark();
rex.describe();
puts(rex.name);
