#!/usr/bin/python
# coding: utf-8

import sys, json, urllib
from urllib2 import urlopen, HTTPError

if len(sys.argv) < 3:
    print('Not enough parameters.\n./google.py COUNT TEXT')
    exit()
    
COUNT = int(sys.argv[1])
TEXT = ' '.join(sys.argv[2:])

def main():
    results = []
    for i in xrange(COUNT / 4 + 1):
        res = urlopen('http://ajax.googleapis.com/ajax/services/search/web?v=1.0&q=%s&start=%i' % (urllib.quote(TEXT), i*4)).read()
        json_res = json.loads(res)
        results += json_res['responseData']['results']

    for i in xrange(COUNT):
        r = results[i]
        print('%i. \033[1;31m%s\033[0m\n%s\n\033[4;34m%s\033[0m\n' % (i+1, r['titleNoFormatting'], r['content'].replace('<b>', '').replace('</b>', ''), r['url']))

if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        print(u'Exit by Ctrl+C.')
    except HTTPError:
        print(u'Error!')
