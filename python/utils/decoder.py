#!/bin/python3
import conversions

def main():
    msg = "010101100110000101101100011010000110000101101100011011000110000100100001"
    print (conversions.bin_2_str(msg))
    msg = "526f636b2c2050617065722c2053636973736f727321"
    print (conversions.hex_2_str(msg))
    msg = "WW91IGRvbid0IG5lZWQgYSBrZXkgdG8gZW5jb2RlIGRhdGEu"
    print (conversions.b64decode(msg))
    msg = "000100010001000000001100000000110001011100000111000010100000100100011101000001010001100100000101"
    #print (conversions.str_2_bin('abcdefghijkl'))
    #print (conversions.bitxor(msg, conversions.str_2_bin('abcdefghijkl')))
    #print (conversions.strxor(msg, conversions.str_2_bin('abcdefghijkl')))
    #print (conversions.bin_2_str('011100000111001001101111011001110111001001100001011011010110000101110100011011110111001001101001'))
    print (conversions.bin_2_str(conversions.bitxor(msg, conversions.str_2_bin('abcdefghijkl'))))
    msg = "02030F07100A061C060B1909"
    print (conversions.hex_2_str(conversions.hexxor(msg, conversions.str_2_hex('abcdefghijkl'))))


if __name__ == '__main__':
    main()