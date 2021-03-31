from caesar import *
import operator

bigrams = ["TH", "HE", 'IN', 'OR', 'HA', 'ET', 'AN',
           'EA', 'IS', 'OU', 'HI', 'ER', 'ST', 'RE', 'ND']

monograms = ['E', 'T', 'A', 'O', 'I', 'N', 'S', 'R', 'H', 'D', 'L', 'U',
             'C', 'M', 'F', 'Y', 'W', 'G', 'P', 'B', 'V', 'K', 'X', 'Q', 'J', 'Z']

subst_table = {}

freq_table_bi = {}
freq_table_mono = {}

# sorts a dictionary d by the value

def sort_dictionary(d):
    sorted_dict = list(reversed(sorted(d.items(), key=operator.itemgetter(1))))
    return sorted_dict

# computes the frequencies of the monograms and bigrams in the text

def analize(text):
    global freq_table_bi

    # fill in the freq_table_mono dictionary
    for letter in text[:-1]:
        if letter in freq_table_mono:
            freq_table_mono[letter] += 1
        else:
            freq_table_mono[letter] = 1

    print sort_dictionary(freq_table_mono)

    # fill in the freq_table_bi dictionary
    for i in range(len(text[:-1]) - 1):
        bigram = text[i:i + 2]
        if bigram in freq_table_bi:
            freq_table_bi[bigram] += 1
        else:
            freq_table_bi[bigram] = 0

# creates a substitution table using the frequencies of the bigrams


def create_subst_table():
    global subst_table

    # TODO 2.1 sort the bigrams frequence table by the frequency
    data = sort_dictionary(freq_table_bi)
    print data

    # TODO 2.2 fill in the substitution table by associating the sorted frequence
    # dictionary with the given bigrams

    for index, bigram in enumerate(bigrams):
        initial = data[index][0][0]
        final = bigram[0]
        if initial not in subst_table.keys() and final not in subst_table.values():
            subst_table[initial] = final
        initial = data[index][0][1]
        final = bigram[1]
        if initial not in subst_table.keys() and final not in subst_table.values():
            subst_table[initial] = final

# fills in the letters missing from the substitution table using the frequencies
# of the monograms

def complete_subst_table():
    global subst_table

    # sort the monograms frequence table by the frequency
    data = sort_dictionary(freq_table_mono)
    print data

    # fill in the missing letters from the substitution table by
    for index, mono in enumerate(monograms):
        #print mono, data[i]
        if data[index][0] not in subst_table.values() and mono not in subst_table.keys():
            subst_table[mono] = data[index][0]

# this is magic stuff used in main

def adjust():
    global subst_table
    subst_table['Y'] = 'B'
    subst_table['E'] = 'L'
    subst_table['L'] = 'M'
    subst_table['P'] = 'W'
    subst_table['F'] = 'C'
    subst_table['X'] = 'F'
    subst_table['J'] = 'G'
    subst_table['I'] = 'Y'
    # adaugat de adrianus
    subst_table['A'] = 'K'
    subst_table['H'] = 'P'
    subst_table['D'] = 'J'
    subst_table['Z'] = 'X'
    subst_table['U'] = 'Z'


def decrypt_text(text):
    global subst_table

    decoded = ''
    for letter in text[:-1]:
        try:
            decoded = decoded + subst_table[letter]
        except:
            print '=' + letter + '='
            decoded = decoded + '-'
    print decoded

def main():
    with open('biblical_input.txt', 'r') as myfile:
        text = myfile.read()

    analize(text)
    create_subst_table()
    complete_subst_table()
    adjust()
    print subst_table
    decrypt_text(text)


if __name__ == "__main__":
    main()
