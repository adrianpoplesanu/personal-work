
class Person(object):
    def __init__(self, height):
        self.height = height

    def get_eid(self):
        raise NotImplementedError

    def test(self):
        print self.get_eid()

class Employee(Person):
    def __init__(self, name=None, age=None, eid=None, height=None):
        super(Employee, self).__init__(height)
        self.name = name
        self.age = age
        self.eid = eid

    def __str__(self):
        result = "<employee>"
        if self.name:
            result += '<name>' + self.name + '</name>'
        if self.age:
            result += '<age>' + str(self.age) + '</age>'
        if self.eid:
            result += '<eid>' + self.eid + '</eid>'
        if self.height:
            result += '<height>' + self.height + '</height>'
        result += "</employee>"
        return result

    def __eq__(self, cls):
        return self.age == cls.age

    def __lt__(self, cls):
        return self.age < cls.age

    def get_eid(self):
        if self.eid:
            return self.eid
        else:
            raise Exception("nu exista eid, userul nu se poate conecta la laptop")

    @staticmethod
    def test2():
        print 'test2'


alin = Employee("Alin Ivascu", age=28, eid='c2001234', height="123")
cati = Employee("Cati Chiriac", age=29, eid='c2001235', height="134")

#print alin
alin.test()

Employee.test2()

#print alin == cati

#print alin < cati
#print cati < alin

#print alin
#print cati

#andrei = Employee("Andrei Nicolae", age=29)

#print andrei.get_eid()

#users = [alin, cati, andrei]
#names = [user.name.upper() for user in users]
#print names

