import hashlib
import json
import os

from cryptography.hazmat.primitives.asymmetric import rsa, padding
from cryptography.hazmat.primitives import hashes, serialization
from cryptography.hazmat.primitives.asymmetric.rsa import RSAPrivateKey, RSAPublicKey
from cryptography.hazmat.primitives.ciphers.aead import AESGCM

from encrypted_message import EncryptedMessage


class Crypto:
    def __init__(self, aes_key: bytes = None, public_rsa_key: RSAPublicKey = None,
                 private_rsa_key: RSAPrivateKey = None):
        self.aes_key = aes_key
        self.public_rsa_key = public_rsa_key
        self.private_rsa_key = private_rsa_key

    def sha256(self, message):
        hash_value = hashlib.sha256(message.encode()).hexdigest()
        print("[ LOG ]", "generated sha:", hash_value, "for:", message)
        return hash_value

    def generate_aes_key(self) -> bytes:
        key = AESGCM.generate_key(bit_length=256)
        print("[ LOG ]", "AES key generated:", key.hex())
        self.aes_key = key
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

    def encode(self, message: bytes, public_key):
        ciphertext = public_key.encrypt(
            #message.encode('UTF-8'),
            message,
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

    def decode(self, ciphertext):
        plaintext = self.private_rsa_key.decrypt(
            ciphertext,
            padding.OAEP(
                mgf=padding.MGF1(algorithm=hashes.SHA256()),
                algorithm=hashes.SHA256(),
                label=None,
            ),
        )

        #print("[ LOG ]", "decoded text using RSA:", plaintext.decode())
        print("[ LOG ] AES key:", plaintext.hex())
        print("[ LOG ] AES key length:", len(plaintext))

        return plaintext

    def generate_signature_rsa(self, message):
        signature = self.private_rsa_key.sign(
            message,
            padding.PSS(
                mgf=padding.MGF1(hashes.SHA256()),
                salt_length=padding.PSS.MAX_LENGTH,
            ),
            hashes.SHA256(),
        )

        print("[ LOG ]", "signature created:", signature)

        return signature

    def verify_signature_rsa(self, signature, message, public_key):
        public_key.verify(
            signature,
            message,
            padding.PSS(
                mgf=padding.MGF1(hashes.SHA256()),
                salt_length=padding.PSS.MAX_LENGTH,
            ),
            hashes.SHA256(),
        )

        print("[ LOG ]", "signature verified:", signature)

    def encrypt_message(self, message, public_key) -> EncryptedMessage:
        aes = AESGCM(self.aes_key)

        nonce = os.urandom(12)
        print("nonce:", nonce.hex())

        ciphertext = aes.encrypt(nonce, message.encode("utf-8"), None)

        encrypted_aes_key = self.encode(self.aes_key, public_key).hex()

        data = json.dumps(
            {
                "encrypted_aes_key": encrypted_aes_key,
                "nonce": nonce.hex(),
                "ciphertext": ciphertext.hex(),
            },
            separators=(",", ":"),
            sort_keys=True,
        ).encode("utf-8")

        return EncryptedMessage(encrypted_aes_key=encrypted_aes_key,
                                nonce=nonce.hex(),
                                ciphertext=ciphertext.hex(),
                                signature=self.generate_signature_rsa(data).hex()
                                )

    def decrypt(self, encrypted_message: EncryptedMessage, public_key):
        # verify signature
        data = json.dumps(
            {
                "encrypted_aes_key": encrypted_message.encrypted_aes_key,
                "nonce": encrypted_message.nonce,
                "ciphertext": encrypted_message.ciphertext,
            },
            separators=(",", ":"),
            sort_keys=True,
        ).encode("utf-8")

        self.verify_signature_rsa(
            bytes.fromhex(encrypted_message.signature),
            data,
            public_key
        )

        print("[ LOG ] Signature verified.")

        # decrypt aes key
        encrypted_aes_key = bytes.fromhex(
            encrypted_message.encrypted_aes_key
        )
        aes_key = self.decode(ciphertext=encrypted_aes_key)
        print(aes_key)

        # decrypt message
        aes = AESGCM(aes_key)

        nonce = bytes.fromhex(encrypted_message.nonce)
        ciphertext = bytes.fromhex(encrypted_message.ciphertext)
        decrypted = aes.decrypt(nonce, ciphertext, None)
        print(decrypted)

    def decode_aes(self, ciphertext):
        pass
