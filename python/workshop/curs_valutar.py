import urllib2
import re

data = urllib2.urlopen('https://www.cursvalutar.ro/curs-gbp/?curs_from_date=02-05-2018&curs_to_date=02-05-2019')
html = data.read()

results = re.findall('<td>(\d+.\d+)</td>', html)
total = 0
for value in results:
    total += float(value)

average = total / len(results)

print 'Media este:', average