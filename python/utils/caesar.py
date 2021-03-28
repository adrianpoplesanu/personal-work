alphabet='ABCDEFGHIJKLMNOPQRSTUVWXYZ'

def caesar_enc(letter):
    if letter < 'A' or letter > 'Z':
        #print('Invalid letter')
        return letter
    else:
        return alphabet[(ord(letter) - ord('A') + 3) % len(alphabet)]

def caesar_dec(letter):
    if letter < 'A' or letter > 'Z':
        #print('Invalid letter')
        return letter
    else:
        return alphabet[(ord(letter) - ord('A') - 3) % len(alphabet)]

def caesar_enc_string(plaintext):
    ciphertext = ''
    for letter in plaintext:
        ciphertext = ciphertext + caesar_enc(letter)
    return ciphertext

def caesar_dec_string(ciphertext):
    plaintext = ''
    for letter in ciphertext:
        plaintext = plaintext + caesar_dec(letter)
    return plaintext

def main():
    coded = caesar_enc_string('BUNA DIMINEATA!!!')
    print (coded)
    decoded = caesar_dec_string(coded)
    print (decoded)

if __name__ == '__main__':
    main()