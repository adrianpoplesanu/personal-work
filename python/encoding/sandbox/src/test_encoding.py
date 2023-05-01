import base64

text = "LIPwImNG5vovjmwDOIZsHWxSIYRDOFaQbEGfRFM9RgA="
b64_decoded = base64.b64decode(text)
byte_arr_unformatted = bytearray(b64_decoded)
byte_arr_formatted = [x for x in byte_arr_unformatted]

print(text)
print(b64_decoded)
print(byte_arr_unformatted)
print(byte_arr_formatted)
