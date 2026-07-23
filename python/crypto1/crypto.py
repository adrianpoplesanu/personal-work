import hashlib
from cryptography.hazmat.primitives.asymmetric import rsa, padding
from cryptography.hazmat.primitives import hashes, serialization
from cryptography.hazmat.primitives.asymmetric.rsa import RSAPrivateKey, RSAPublicKey
from cryptography.hazmat.primitives.ciphers.aead import AESGCM


class Crypto:
    def __init__(self, public_rsa_key: RSAPublicKey = None, private_rsa_key: RSAPrivateKey = None):
        self.public_rsa_key = public_rsa_key
        self.private_rsa_key = private_rsa_key

    def sha256(self, message):
        hash_value = hashlib.sha256(message.encode()).hexdigest()
        print("[ LOG ]", "generated sha:", hash_value, "for:", message)
        return hash_value

    def generate_aes_key(self) -> bytes:
        key = AESGCM.generate_key(bit_length=256)
        print("[ LOG ]", "AES key generated:", key.hex())
        return key

    def public_pem_decode(self):
        public_pem = self.public_rsa_key.public_bytes(
            encoding=serialization.Encoding.PEM,
            format=serialization.PublicFormat.SubjectPublicKeyInfo,
        )

        return public_pem.decode()

    def private_pem_decode(self):
        private_pem = self.private_rsa_key.private_bytes(
            encoding=serialization.Encoding.PEM,
            format=serialization.PrivateFormat.PKCS8,
            encryption_algorithm=serialization.NoEncryption(),
        )

        return private_pem.decode()

    def generate_rsa_keys(self) -> (RSAPublicKey, RSAPrivateKey):
        private_key = rsa.generate_private_key(
            public_exponent=65537,
            key_size=2048,
        )

        public_key = private_key.public_key()

        self.public_rsa_key = public_key
        self.private_rsa_key = private_key

        print("[ LOG ]", "RSA public key generated:")
        print(self.public_pem_decode())
        print("[ LOG ]", "RSA private key generated:")
        print(self.private_pem_decode())

        return public_key, private_key

    def encode_rsa(self, message):
        ciphertext = self.public_rsa_key.encrypt(
            message.encode('UTF-8'),
            padding.OAEP(
                mgf=padding.MGF1(algorithm=hashes.SHA256()),
                algorithm=hashes.SHA256(),
                label=None,
            ),
        )

        print("[ LOG ]", "generated ciphertext using RSA:", ciphertext.hex())

        return ciphertext

    def decode_rsa(self, ciphertext):
        plaintext = self.private_rsa_key.decrypt(
            ciphertext,
            padding.OAEP(
                mgf=padding.MGF1(algorithm=hashes.SHA256()),
                algorithm=hashes.SHA256(),
                label=None,
            ),
        )

        print("[ LOG ]", "decoded text using RSA:", plaintext.decode())

        return plaintext

    def verify_signature_rsa(self):
        pass