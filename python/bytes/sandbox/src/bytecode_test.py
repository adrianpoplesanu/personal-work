integer_val = 5
  
bytes_val = integer_val.to_bytes(2, 'big')
  
print(type(bytes_val))
print(bytes_val)
print(bytes_val[0])
print(bytes_val[1])
