alphabet1 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
alphabet2 = "abcdefghijklmnopqrstuvwxyz"

data = "cvpbPGS{arkg_gvzr_V'yy_gel_2_ebhaqf_bs_ebg13_nSkgmDJE}"
rot = 13
output = ""

for letter in data:
    if letter in alphabet1:
        pos = alphabet1.index(letter)
        pos += rot
        pos = pos % 26
        output += alphabet1[pos]
    elif letter in alphabet2:
        pos = alphabet2.index(letter)
        pos += rot
        pos = pos % 26
        output += alphabet2[pos]
    else:
        output += letter

print output
