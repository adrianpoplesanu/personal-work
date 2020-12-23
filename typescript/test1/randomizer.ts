class Randomizer {
    constructor() {
    }

    get_random_number() {
        return 77;
    }
}

let randomizer : Randomizer = new Randomizer()
let a = randomizer.get_random_number()
console.log(a);
