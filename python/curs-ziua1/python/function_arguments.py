def test(arg, *argv, **kwargs):
    #print arg
    #print argv
    #print kwargs
    start = time.now()
    res = arg(*argv, **kwargs)
    end = time.now()
    log.out('executia a durat ' + end -start)
    return res

test()
test('aaa')
test('aaa', 'bbb')
test('aaa', 'bbb', 'ccc', ddd='eee', fff='ggg')


@test
def server_response(...):
   ...
   return '<HTML></HTML>'
