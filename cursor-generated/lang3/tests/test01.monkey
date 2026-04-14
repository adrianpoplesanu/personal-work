class Dog {
    fn init(n, a) {
        this.name = n;
        this.age = a;
    }

    fn inc() {
        this.age = this.age + 1;
    }

    fn dec() {
        this.age = this.age - 1;
    }

    fn changeName(n) {
        this.name = n;
    }

    fn bark() {
        puts("ham ham ham");
    }
};

let dog = new Dog("bebe dex", 16);

let thread1 = spawn(dog.inc);
join(thread1);
puts(dog.age);