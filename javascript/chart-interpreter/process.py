import csv

with open('input.csv', mode='r') as input_file:
    reader = csv.reader(input_file)

    values = []
    for i, row in enumerate(reader):
        if i == 0:
            continue
        #values.append(int(row[1]))
        values.append(row[0])

    print values