// test if loop paranthesis expressions, see if they behave like in c++
var i = 0, n = 9102;
for(; i*=10,i+=n%10,n/=10,n > 0; ) ;
console.log(i);
