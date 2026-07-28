from alice import Alice
from bob import Bob
from crypto import Crypto


def run_alice_bob_communication():
    alice = Alice()
    bob = Bob()

    message = "the quick brown bebe dex"

    encrypted_message = alice.send(message, bob.crypto.public_rsa_key)
    print(encrypted_message)

    original_message = bob.receive(encrypted_message, alice.crypto.public_rsa_key)
    print(original_message)


def main():
    crypto = Crypto()

    crypto.sha256("buna dimineata!")

    public_key, private_key = crypto.generate_rsa_keys()

    ciphertext = crypto.encode_rsa("bebe dex")
    message = crypto.decode_rsa(ciphertext)


if __name__ == '__main__':
    # main()
    run_alice_bob_communication()
