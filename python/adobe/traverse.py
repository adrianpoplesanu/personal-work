frecv = {}

def generate_key(word):
    letters = {}
    for ch in word:
        if ch not in letters:
            letters[ch] = True
    return ''.join(sorted(letters.keys()))

if __name__ == '__main__':
    filename = open('data.txt')
    data = filename.read()
    words = [word.strip() for word in data.split(',')]
    for word in words:
        hash = generate_key(word)
        if hash not in frecv:
            frecv[hash] = 1
        else:
            frecv[hash] += 1
    for hash in sorted(frecv.keys()):
        print hash, ' -> ', frecv[hash]
