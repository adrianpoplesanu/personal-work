filename = open("board.txt", "r")

source = ""

for line in filename.readlines():
    if not '---' in line:
        source += '{' + line.strip().replace("-", "0").replace("| ", "").replace(' ', ', ') + '}, ' + '\n'
print source[:-3]
