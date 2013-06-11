import urllib2

def checkConnection():
    try:
        response = urllib2.urlopen('http://google.com', timeout = 1)
        return True
    except urllib2.URLError as err: pass
    return False
