import hashlib

if __name__ == '__main__':
    message = "buna dimineata!"
    hash_value = hashlib.sha256(message.encode()).hexdigest()

    # same as running: echo -n "buna dimineata\!" | shasum -a 256
    print(hash_value)