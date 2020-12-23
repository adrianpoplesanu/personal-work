var Randomizer = /** @class */ (function () {
    function Randomizer() {
    }
    Randomizer.prototype.get_random_number = function () {
        return 77;
    };
    return Randomizer;
}());
var randomizer = new Randomizer();
var a = randomizer.get_random_number();
console.log(a);
