s='s=%r;print(s%%s)';print(s%s)

print 'first'
print '%r' % s
print 'second'
print '%s' % s
print 'last'
print s%s

print '==='

a='a=%r'
print a % a

print '==='

b = 'ccc%s'
print b % b

print '==='

c = 'ccc%r'
print c % c

print '==='
d = 'aa %%s bb'
#print d % 'c'
print d % ()

print '==='
print "%%" % ()

print '==='
print '%% %s' % 'a'

print '==='
print '%%'
print '%%' % ()

print '==='
# asta e motivul pentru care merge, 'aa' e pus in primul %s iar %% e evaluat catre % cand e formatat
# stringul, pentru ca asta e modul in care afisezi % in formatare
print '%s %%' % 'aa'
