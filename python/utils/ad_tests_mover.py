limit = 95

def format_2digits(i):
    if i < 10:
        return "test0" + str(i)
    else:
        return "test" + str(i)

def format_3digits(i):
    if i < 10:
        return "test00" + str(i)
    elif i < 100:
        return "test0" + str(i)
    else:
        return "test" + str(i)

if __name__ == '__main__':
    for i in range(1, limit + 1):
        print ("mv " + format_2digits(i) + ".ad " + format_3digits(i) + ".ad ;")

    print ("echo 'done'")

