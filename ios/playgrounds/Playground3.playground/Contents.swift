//Swift inout for "reference"-like argument passing

import UIKit

var name = "Brett"

func changeName(for name: inout String) {
    name = "Eddy"
}

print(name)
changeName(for: &name)
print(name)
