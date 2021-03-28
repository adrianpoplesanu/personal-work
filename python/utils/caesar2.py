text1 = "LDPWKHORUGBRXUJRG"
# IAMTHELORDYOURGOD
text2 = "XNTRGZKKGZUDMNNSGDQFNCRADENQDLD"
# YOUSHALLHAVENOOTHERGODSBEFOREME
text3 = "DTZXMFQQSTYRFPJDTZWXJQKFSDLWFAJSNRFLJ"
# YOUSHALLNOTMAKEYOURSELFANYGRAVENIMAGE
text4 = "SIOMBUFFHINNUEYNBYHUGYIZNBYFILXSIOLAIXCHPUCH"
# YOUSHALLNOTTAKETHENAMEOFTHELORDYOURGODINVAIN
text5 = "ERZRZOREGURFNOONGUQNLGBXRRCVGUBYL"
# REMEMBERTHESABBATHDAYTOKEEPITHOLY
text6 = "CJIJPMTJPMAVOCZMVIYTJPMHJOCZM"
# HONOURYOURFATHERANDYOURMOTHER
text7 = "DTZXMFQQSTYRZWIJW"
# YOUSHALLNOTMURDER
text8 = "ZPVTIBMMOPUDPNNJUBEVMUFSZ"
# YOUSHALLNOTCOMMITADULTERY
text9 = "FVBZOHSSUVAZALHS"
# YOUSHALLNOTSTEAL
text10 = "KAGETMXXZAFSUHQRMXEQFQEFUYAZKMSMUZEFKAGDZQUSTNAGD"
# YOUSHALLNOTGIVEFALSETESTIMONYAGAINSTYOURNEIGHBOUR
text11 = "MCIGVOZZBCHRSGWFSOBMHVWBUHVOHPSZCBUGHCMCIFBSWUVPCIF"
# YOUSHALLNOTDESIREANYTHINGTHATBELONGSTOYOURNEIGHBOUR


alphabet='ABCDEFGHIJKLMNOPQRSTUVWXYZ'

def caesar_enc(letter, displacement):
    if letter < 'A' or letter > 'Z':
        #print('Invalid letter')
        return letter
    else:
        return alphabet[(ord(letter) - ord('A') + displacement) % len(alphabet)]

def caesar_dec(letter, displacement):
    if letter < 'A' or letter > 'Z':
        #print('Invalid letter')
        return letter
    else:
        return alphabet[(ord(letter) - ord('A') - displacement) % len(alphabet)]

def caesar_enc_string(plaintext, displacement):
    ciphertext = ''
    for letter in plaintext:
        ciphertext = ciphertext + caesar_enc(letter, displacement)
    return ciphertext

def caesar_dec_string(ciphertext, displacement):
    plaintext = ''
    for letter in ciphertext:
        plaintext = plaintext + caesar_dec(letter, displacement)
    return plaintext

def main():
    for i in range(len(alphabet)):
        print caesar_dec_string(text11, i)


if __name__ == '__main__':
    main()