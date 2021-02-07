numbers = [1, 2, 3]
print numbers

# for-each just like Java changess the iteration element only locally
for number in numbers:
    number = number * 2

print numbers

# list comprehension is so cool and the most pythoni
numbers = [number * 2 for number in numbers]

print numbers

# just like Java, traditional for iteration can change the element itself
for i in range(len(numbers)):
    numbers[i] *= 2

print numbers
