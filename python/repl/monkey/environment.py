class Environment(object):
    store = {}

    def Get(self, name):
        check = name in self.store
        return self.store[name], check

    def Set(self, name, val):
        check = name in self.store
        self.store[name] = val
        return val, check

def NewEnvironment():
    return Environment()