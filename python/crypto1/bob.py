from cryptography.hazmat.primitives.asymmetric.rsa import RSAPublicKey

from crypto import Crypto
from encrypted_message import EncryptedMessage


class Bob:
    def __init__(self):
        self.crypto = Crypto()

        self.crypto.generate_rsa_keys()

    def send(self, message, public_key: RSAPublicKey) -> EncryptedMessage:
        self.crypto.generate_aes_key()
        encrypted_message = self.crypto.encrypt_message(message, public_key)
        return encrypted_message

    def receive(self, encrypted_message: EncryptedMessage, public_key) -> str:
        message = self.crypto.decrypt(encrypted_message, public_key)
        return message
