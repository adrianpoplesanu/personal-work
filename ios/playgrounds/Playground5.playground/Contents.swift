//A playground to rule them all

import UIKit

let a = [6, 7, 9, 4, 1, 3, 8, 5]
print(a)
print(a[2...5])
print(a[0...7])

//let name = [] // not working
let names = ["Brett", "Hillary", "Ray", "Eddy"]
for name in names {
    print ("name: \(name)")
}
print(names.sorted())

for name in names.reversed() {
    print ("name: \(name)")
}

let palindrom = "aaabbbaaa"
type(of: palindrom)
//print (palindrom.reversed()) // not working
