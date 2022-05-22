#file_handler = open('enc', 'r')
#flag = file_handler.read()

#print(flag)

flag = '\u7069\u636f\u4354\u467b\u3136\u5f62\u6974\u735f\u696e\u7374\u3334\u645f\u6f66\u5f38\u5f65\u3134\u3161\u3066\u377d'

secret = ''.join([chr((ord(flag[i]) << 8) + ord(flag[i + 1])) for i in range(0, len(flag), 2)])
print (secret)
