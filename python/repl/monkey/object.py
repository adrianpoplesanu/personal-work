class Object(object):
    def Type(self):
        pass

    def Inspect(self):
        pass


class ObjectType(object):
    INTEGER_OBJ = "INTEGER"
    BOOLEAN_OBJ = "BOOLEAN"
    NULL_OBJ = "NULL"
    RETURN_VALUE_OBJ = "RETURN_VALUE"
    ERROR_OBJ = "ERROR"
    FUNCTION_OBJ = "FUNCTION"
    STRING_OBJ = "STRING"
    BUILTIN_OBJ = "BUILTIN"
    ARRAY_OBJ = "ARRAY"


class Integer(object):
    def __init__(self, Value=0):
        self.Value = Value

    def Inspect(self):
        # linia de mai jos printeaza exact tipul din Python asociat valorii stocate mai jos, si e <type 'int'> ceea ce e bine si cool
        #print type(self.Value)
        return "{0}".format(self.Value)

    def Type(self):
        return ObjectType.INTEGER_OBJ


class Boolean(object):
    def __init__(self, Value=False):
        self.Value = Value

    def Inspect(self):
        return "{0}".format(self.Value)

    def Type(self):
        return ObjectType.BOOLEAN_OBJ

class Null(object):
    def __init__(self):
        #self.Value = None
        pass

    def Inspect(self):
        return "null"

    def Type(self):
        return ObjectType.NULL_OBJ


class ReturnValue(object):
    def __init__(self, Value=None):
        self.Value = Value

    def Inspect(self):
        # la cum e returnul, ma gandesc ca Value e un olt obiect care are la randul lui o implementare pentru Inspect()
        # ce e interesat e ca Inspect() la toate celealte obiecte nu returneaza nimic, ci face doar print... hmmmm
        return self.Value.Inspect()

    def Type(self):
        return ObjectType.RETURN_VALUE_OBJ


class Error(object):
    def __init__(self, message=None):
        self.message = message

    def Inspect(self):
        print "ERROR: " + self.message # le-am pus pe amandoua pentru ca ReturnValue e diferit de toate celelate
        return "ERROR: " + self.message # ReturnValue returneaza ceva, celelalte doar printeaza ceva

    def Type(self):
        return ObjectType.ERROR_OBJ


class Function(object):
    def __init__(self, parameters=None, body=None, env=None):
        self.parameters = parameters
        self.body = body # block statement
        self.env = env # environment

    def Inspect(self):
        print 'FunctionObject'

    def Type(self):
        return ObjectType.FUNCTION_OBJ


class String(object):
    def __init__(self, value=None):
        self.value = value

    def Inspect(self):
        return '"{0}"'.format(self.value)

    def Type(self):
        return ObjectType.STRING_OBJ


class Builtin(object):
    def __init__(self, builtin_function):
        self.builtin_function = builtin_function

    def Inspect(self):
        print "built-in function"

    def Type(self):
        return ObjectType.BUILTIN_OBJ

class ArrayObject(object):
    def __init__(self, elements=None):
        self.elements = elements

    def Inspect(self):
        out = '['
        all_elements = []
        for element in self.elements:
            #print element
            all_elements.append(element.Inspect())
        out += ', '.join(all_elements)
        out += ']'
        return out

    def Type(self):
        return ObjectType.ARRAY_OBJ