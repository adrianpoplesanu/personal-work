import json
from collections import OrderedDict

# some JSON:
x = '{ "name":"John", "age":30, "city":"New York"}'
y = '{ "age":30, "name":"John", "city":"New York"}'

# parse x:
a = json.loads(x)
b = json.loads(y)

# the result is a Python dictionary:
print(a)
print(b)

aaa = OrderedDict(a.items())
bbb = OrderedDict(b.items())

print(str(aaa))
print(str(bbb))
