import requests
from html.parser import HTMLParser
import sys
import os


class MyHTMLParser(HTMLParser):

    urls = []

    def handle_starttag(self, tag, attrs):
        if tag == "area":
            # print("Encountered a area node:", tag)
            for (key, value) in attrs:
                if key == 'href':
                    self.urls.append(value)
                    # print('href : ', value)

    def handle_endtag(self, tag):
        # print("Encountered an end tag :", tag)
        pass

    def handle_data(self, data):
        # print("Encountered some data  :", data)
        pass


res = requests.get(
    "http://viewfinderpanoramas.org/Coverage%20map%20viewfinderpanoramas_org3.htm")
if res.status_code == 200:
    print("OK")
    # print(dir(res))
    # print(res.content)
else:
    print("Can't reach given url")
    sys.exit(0)


parser = MyHTMLParser()
parser.feed(str(res.content))
print("num urls : ", len(parser.urls))

with open(os.path.join(os.path.dirname(__file__), "urls.txt"), 'w') as f:
    # f.writelines(parser.urls)
    for url in parser.urls:
        f.write(url + "\n")
