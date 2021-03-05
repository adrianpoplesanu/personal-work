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
