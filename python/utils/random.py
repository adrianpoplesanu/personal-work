import uuid

if __name__ == '__main__':
    numbers = str(uuid.uuid4()).split('-')
    sum = 0
    for number in numbers:
        sum += int(number, 16)
    print sum
