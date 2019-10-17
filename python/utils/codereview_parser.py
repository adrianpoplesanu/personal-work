# tool care elimina liniile goale care au numere la inceput de linie
# util pentru a copia din codereview sursa 
# si a elimina line numberele care sunt puse automat pe linii independente

source = open('codereview.txt', 'r')
lines = source.readlines()

occurances = 0

for line in lines:
    num_start = line.split(' ') [0]
    if num_start:
        try:
            int(num_start.strip())
            occurances += 1
        except:
            occurances = 0
            print line,
    else:
        occurances = 0
        print line,
    if (occurances > 1):
        print
