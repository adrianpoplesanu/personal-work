def type_check(param):
    if type(param) == int:
        print 'e int'
    elif type(param) == str:
        print 'e string'
    else:
        print 'e altceva'


if __name__ == '__main__':
    a = 5
    print type(a)
    print type(type(a))
    print type(type(type(a)))

    type_check(7)
    type_check("aaa")
    type_check(0.5)
