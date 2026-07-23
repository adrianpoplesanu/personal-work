
import crypto

if __name__ == '__main__':
    crypto = crypto.Crypto()

    crypto.sha256("buna dimineata!")

    public_key, private_key = crypto.generate_rsa_keys()

    ciphertext = crypto.encode_rsa("bebe dex")
    message = crypto.decode_rsa(ciphertext)
