const greetModule = require('./build/Release/greet.node');

console.log('exports : ', greetModule);
console.log('greetModule.greetHello() : ', greetModule.greetHello());

console.log('exports : ', greetModule);
console.log('greetModule.find5() : ', greetModule.find5());

console.log('greetModule.find5([1, 2, 1, 3, 1, 4], 1) : ', greetModule.find5([1, 2, 1, 3, 1, 4], 1));
console.log('greetModule.find6([1, 2, 1, 3, 1, 4], 1) : ', greetModule.find6([1, 2, 1, 3, 1, 4], 1));
