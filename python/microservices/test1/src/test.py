class Elev(object):
    def __init__(self, name):
        self.name = name

    def __str__(self):
        return self.name


def greeting(name: str) -> str:
    return 'hello ' + name

e = Elev('adrianus')

print(greeting('aditz'))
print(greeting(str(e)))
