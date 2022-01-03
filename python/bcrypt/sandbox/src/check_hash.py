import bcrypt
import base64
import hashlib

password = "Tester123"

if bcrypt.checkpw(base64.b64encode(hashlib.sha256(password.encode('utf-8')).digest()), b'$2b$12$OelV3foJDPp9XqWyjr4cV.miYjLRO5pMcDhb5WRiA/n9gENPBBNOK'):
    print ("match")
else:
    print ("does not match")
