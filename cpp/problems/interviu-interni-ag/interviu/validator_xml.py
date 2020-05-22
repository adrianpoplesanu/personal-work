import re

text = "<aaa><bbb>123</bbb><ccc>234</ccc></aaa>"
tags = re.findall(r"<(.+?)>", text)

stiva = []
valid = True

for tag in tags:
    if tag[0] == '/':
        if stiva[-1] != tag[1:]:
            valid = False
            break
        else:
            stiva.pop()
    else:
        stiva.append(tag)

if len(stiva):
    valid = False

if (valid):
    print 'e valid xml-ul'
else:
    print 'e invalid xml-ul'
