//: Playground4 - forced unwrapping

import UIKit

let str = "5"
let num = Int(str)
let num2 = 7
print(type(of: num))
print(type(of: num2))
let num3 = Int(str)!
print(type(of: num3))