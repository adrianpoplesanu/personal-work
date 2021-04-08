class Object(object):
    def Type(self):
        pass

    def Inspect(self):
        pass


class ObjectType(object):
    INTEGER_OBJ = "INTEGER"
    BOOLEAN_OBJ = "BOOLEAN"


class Integer(object):
    def __init__(self):
        self.Value = '47'

    def Inspect(self):
        print "{0}".format(self.Value)

    def Type(self):
        return ObjectType.INTEGER_OBJ


class Boollean(object):
    def __init__(self):
        self.Value = 'false'

    def Inspect(self):
        print "{0}".format(self.Value)

    def Type(self):
        return ObjectType.BOOLEAN_OBJ