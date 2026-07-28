from dataclasses import dataclass
from typing import Optional


@dataclass
class EncryptedMessage:
    encrypted_aes_key: Optional[str] = None
    nonce: Optional[str] = None
    ciphertext: Optional[str] = None
    signature: Optional[str] = None

#    def __init__(self, encrypted_aes_key: str = None,
#                 nonce: str = None,
#                 ciphertext: str = None,
#                 signature: str = None):
#        self.encrypted_aes_key = encrypted_aes_key
#        self.nonce = nonce
#        self.ciphertext = ciphertext
#        self.signature = signature

#    def __str__(self):
#        return "EncryptedMessage{{aes_key='{0}', nonce='{1}', ciphertext='{2}', signature='{3}'}}".format(
#            self.encrypted_aes_key,
#            self.nonce,
#            self.ciphertext,
#            self.signature)

    def __str__(self):
        return (
            f"EncryptedMessage{{"
            f"aes_key='{self.encrypted_aes_key}', "
            f"nonce='{self.nonce}', "
            f"ciphertext='{self.ciphertext}', "
            f"signature='{self.signature}'"
        )
