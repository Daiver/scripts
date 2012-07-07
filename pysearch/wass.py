#!/usr/bin/python
# coding: utf-8

import sys, urllib
from urllib2 import urlopen, HTTPError
import xml.etree.ElementTree as etree

import config#your config with wa_ap_id
'''
if len(sys.argv) < 3:
    print('Not enough parameters.\n./wass.py COUNT TEXT')
    exit()
'''

   
def main():
    COUNT  = int(sys.argv[1]) + 1
    TEXT = '+'.join(sys.argv[2:])

    QUERY = u'http://api.wolframalpha.com/v2/query?input=' + TEXT +'&appid=' + config.WA_AP_ID

    res = urlopen(QUERY)
    tree = etree.parse(res)
    root = tree.getroot()
    pods = root.findall('pod')

    
    if COUNT > len(pods):
        COUNT = len(pods)
        
    for i in xrange(0, COUNT):
        pod = pods[i]
        print i + 1, pod.attrib['title']
        spods = pod.findall('subpod')        

        for spod in spods:
            texts = spod.findall('plaintext')
            for text in texts:
                print text.text

        print ''
        i += 1

if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        print(u'Exit by Ctrl+C.')
    except HTTPError:
        print(u'Error!')
