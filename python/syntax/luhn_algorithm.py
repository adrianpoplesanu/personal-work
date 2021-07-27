def luhn_check(cc_num):
    if len(cc_num) != 16:
        print 'cc num must be 16 digits'
        return False
    checksum = 0
    factor = 2
    for idx in reversed(range(15)):
        digit = int(cc_num[idx]) * factor
        if digit > 9:
            digit -= 9
        checksum += digit
        if factor == 2:
            factor = 1
        else:
            factor = 2
    print (checksum * 9) % 10
    return int(cc_num[15]) == (checksum * 9) % 10

if __name__ == '__main__':
    print luhn_check('4444444444444448')
    print luhn_check('5454545454545454')
