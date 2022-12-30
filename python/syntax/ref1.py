a = 5

def change(a):
    a = 7

print(a)
change(a)
print(a)

numbers = [1, 2, 3]

def change_numbers(numbers):
    numbers = [4, 5]

def change_numbers2(numbers):
    numbers[1] = 7

print (numbers)
change_numbers(numbers)
print (numbers)

print (numbers)
change_numbers2(numbers)
print (numbers)

class Writer:
    name = "radu paraschivescu"

def change_writer(writer):
    writer.name = "mircea cartarescu"

writer = Writer()
print (writer.name)
change_writer(writer)
print (writer.name)

def change_writer2(w):
    w = Writer()

change_writer(writer)
print (writer.name)

def change_numbers3(numbers):
    numbers.append(9)

change_numbers3(numbers)
print (numbers)
