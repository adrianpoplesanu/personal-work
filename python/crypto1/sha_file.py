import hashlib

if __name__ == '__main__':
    filename = "resources/alice_in_wonderland.txt"

    sha = hashlib.sha256()

    with open(filename, "rb") as f:
        while chunk := f.read(4096):
            sha.update(chunk)

    # same as running: shasum -a 256 resources/alice_in_wonderland.txt
    print("SHA-256: ", sha.hexdigest())