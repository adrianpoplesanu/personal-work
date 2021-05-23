class Environment(object):
    store = {}
    outer = None
    def __init__(self):
        self.store = {}
        self.outer = None

    def Get(self, name):
        check = name in self.store
        if not check and self.outer:
            return self.outer.Get(name)
        if check:
            return self.store[name], check
        else:
            return None, check

    def Set(self, name, val):
        check = name in self.store
        self.store[name] = val
        return val, check

def NewEnvironment():
    return Environment()

def NewEnclosedEnvironment(outer):
    env = NewEnvironment()
    env.outer = outer;
    return env