import bcrypt
import base64
import hashlib

password = 'Tester123'
hashed = bcrypt.hashpw(base64.b64encode(hashlib.sha256(password.encode('utf-8')).digest()), bcrypt.gensalt())
print(hashed)
