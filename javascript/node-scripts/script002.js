// test if loop paranthesis expressions, see if they behave like in c++
var i, n = 0;
for(i = 0; n += ++i, i < 5; ) ;
console.log(n);
