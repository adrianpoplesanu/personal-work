if __name__ == '__main__':
    adder = lambda x: x + 1
    print (adder(2))

    odd_even = lambda x: 'odd' if x % 2 else 'even'
    print (odd_even(3))
    print (odd_even(4))

    odd_even2 = lambda x: x % 2 and 'odd' or 'even'
    print (odd_even2(5))
    print (odd_even2(6))

    print ('========================')
    print (22 % 2 and 'odd' or 'even')
    print (11 % 2 and 'odd' or 'even')