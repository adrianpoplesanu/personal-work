//Swift inout for "reference"-like argument passing

import UIKit

var name = "Brett"

func changeName(for name: inout String) {
    name = "Eddy"
}

print(name)
changeName(for: &name)
print(name)


var a = 5
var b = 7

func swap(number a: inout Int, with b: inout Int) {
    let c = a
    a = b
    b = c
}

print(a, b)
swap(number: &a, with: &b)
print(a, b)