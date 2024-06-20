import json
from collections import OrderedDict

# some JSON:
x = '{ "name":"John", "age":30, "city":"New York", "base": { "name":"John", "age":30, "city":"New York" }, "args": ["bbb", "aaa", 2, 1, 3], "records": [{"aaa": 12, "bbb": "test", "ccc":[4,3,2]}]}'
y = '{ "age":30, "name":"John", "city":"New York", "base": { "age":30, "city":"New York", "name":"John" }, "args": [3, 1, "aaa", 2, "bbb"], "records": [{"bbb": "test", "ccc":[3,4,2], "aaa": 12}]}'

# parse x:
a = json.loads(x)
b = json.loads(y)

# the result is a Python dictionary:
print(a)
print(b)

def sort_dict(source):
    if type(source) != dict:
        if type(source) == list:
            original_list = [sort_dict(it) for it in source]
            return sorted(original_list, key=str)
        return source
    sorted_dict = {key: sort_dict(value) for key, value in sorted(source.items())}
    return sorted_dict

#sorted_dict1 = {key: value for key, value in sorted(b.items())}
#sorted_dict2 = {key: value for key, value in sorted(b.items())}

sorted_dict1 = sort_dict(a)
sorted_dict2 = sort_dict(b)

print(sorted_dict1)
print(sorted_dict2)

print(json.dumps(sorted_dict1, indent=4))
print(json.dumps(sorted_dict2, indent=4))
