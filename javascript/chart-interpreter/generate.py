from random import randrange

data = []

with open("input2.csv", "w") as filename:
    filename.write('"Timestamps","Values"\n')

    for i in range(360):
        nr = 2000 + randrange(500)
        data.append(nr)
        filename.write("{0},{1}\n".format(i, nr))

print data
