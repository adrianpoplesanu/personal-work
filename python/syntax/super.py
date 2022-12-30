class Dog:
    age = 0

    def __init__(self, age):
        self.age = age

class Dex(Dog):
    name = "cezar"

    def __init__(self, name, age):
        self.name = name
        super(Dex, self).__init__(age)
        #Dog.__init__(self, age)

    def print_info(self):
        print (self.name)
        print (self.age)

dex = Dex("bebe dex", 12)
dex.print_info()
