import re
import urllib2


if __name__ == "__main__":
    data = urllib2.urlopen("https://www.bluemountain.com/sitemap_ecards_category.xml")
    sitemap_content = data.read()
    urls = re.findall("<loc>(.*)</loc>", sitemap_content)
    for url in urls:
        page = urllib2.urlopen(url)
        print url, page.code