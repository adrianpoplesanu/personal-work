import os
from cryptography.hazmat.primitives.ciphers.aead import AESGCM

if __name__ == '__main__':
    key = AESGCM.generate_key(bit_length=256)
    print(key.hex())
    aes = AESGCM(key)

    nonce = os.urandom(12)

    message = """bebe dex"""

    ciphertext = aes.encrypt(nonce, message.encode("utf-8"), None)

    print("Ciphertext:", ciphertext.hex())

    decrypted = aes.decrypt(nonce, ciphertext, None)

    print("Decrypted:", decrypted.decode())