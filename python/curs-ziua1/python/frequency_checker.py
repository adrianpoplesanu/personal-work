if __name__ == '__main__':
    words = ['Alice', 'in', 'Wonderland', 'test', 'Alice', 'in', 'in']
    raw_words = set(words)
    frecq = {}
    for raw_word in raw_words:
        #raw_word + ' ' + str(words.count(raw_word))
        frecq[raw_word] = words.count(raw_word)
    print frecq


    frecq = {}
    for word in words:
        if word in frecq:
            frecq[word] += 1
        else:
            frecq[word] = 1
    print frecq