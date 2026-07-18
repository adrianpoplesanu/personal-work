import os
from cryptography.hazmat.primitives.ciphers.aead import AESGCM

if __name__ == '__main__':
    key = AESGCM.generate_key(bit_length=256)
    print("AES key:", key.hex())
    aes = AESGCM(key)

    nonce = os.urandom(12)
    print("nonce:", nonce.hex())

    filename = "resources/alice_in_wonderland.txt"
    file_content = ""

    with open(filename, "r") as f:
        while chunk := f.read(4096):
            file_content += chunk

    ciphertext = aes.encrypt(nonce, file_content.encode("utf-8"), None)

    print("Ciphertext:", ciphertext.hex())

    decrypted = aes.decrypt(nonce, ciphertext, None)

    print("Decrypted:", decrypted.decode())