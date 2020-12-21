const greetModule = require('./build/Release/greet.node');

console.log('exports : ', greetModule);
console.log('greetModule.greetHello() : ', greetModule.greetHello());

console.log('exports : ', greetModule);
console.log('greetModule.find5() : ', greetModule.find5());
