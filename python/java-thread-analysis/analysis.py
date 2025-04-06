filename = open("output.txt", "r")
lines = filename.readlines()[3:1003]
result = {}
for line in lines:
    key = int(line.split("got: ")[1])
    if key in result:
        result[key] += 1
    else:
        result[key] = 1

print(result)

print('multiple values:')
for k, v in result.items():
    if v > 1:
        print(str(k) + ' ... ' + str(v))

print('max reached:')
print(max(result.keys()))
