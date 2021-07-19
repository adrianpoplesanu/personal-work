filename = open('readme.txt', 'r')
output = open('output.txt', 'w')

content = filename.read()
print content


#lines = filename.readlines()
#for line in lines:
#    output.write(line.replace('Alice', 'Bob'))

output.close()
filename.close()