class Object(object):
    def Type(self):
        pass

    def Inspect(self):
        pass


class ObjectType(object):
    INTEGER_OBJ = "INTEGER"
    BOOLEAN_OBJ = "BOOLEAN"
    NULL_OBJ = "NULL"


class Integer(object):
    def __init__(self, Value=0):
        self.Value = Value

    def Inspect(self):
        print type(self.Value)
        print "{0}".format(self.Value)

    def Type(self):
        return ObjectType.INTEGER_OBJ


class Boollean(object):
    def __init__(self, Value=False):
        self.Value = Value

    def Inspect(self):
        print "{0}".format(self.Value)

    def Type(self):
        return ObjectType.BOOLEAN_OBJ

class Null(object):
    def __init__(self):
        #self.Value = None
        pass

    def Inspect(self):
        print "null"

    def Type(slf):
        return ObjectType.NULL_OBJ