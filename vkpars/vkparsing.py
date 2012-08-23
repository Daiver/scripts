import pycurl

from StringIO import StringIO

def get_page(url, *args, **kargs):
    c = pycurl.Curl()
    c.setopt(pycurl.URL, url)
    c.bodyio = StringIO()
    c.setopt(pycurl.WRITEFUNCTION, c.bodyio.write)
    c.get_body = c.bodyio.getvalue
    c.headio = StringIO()
    c.setopt(pycurl.HEADERFUNCTION, c.headio.write)
    c.get_head = c.headio.getvalue
    
    c.setopt(pycurl.FOLLOWLOCATION, 1)
    c.setopt(pycurl.MAXREDIRS, 5)
    c.setopt(pycurl.CONNECTTIMEOUT, 60)
    c.setopt(pycurl.TIMEOUT, 120)
    c.setopt(pycurl.NOSIGNAL, 1)
    c.setopt(pycurl.USERAGENT, 'Mozilla/5.0 (X11; Ubuntu; Linux i686; rv:13.0) Gecko/20100101 Firefox/13.0')
    httpheader = [
        'Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8',
        'Accept-Language: ru-ru,ru;q=0.8,en-us;q=0.5,en;q=0.3',
        'Accept-Charset:utf-8;q=0.7,*;q=0.5',
        'Connection: keep-alive',
        ]
    c.setopt(pycurl.HTTPHEADER, httpheader)
    
    c.perform()
    if c.getinfo(pycurl.HTTP_CODE) != 200:
        raise Exception('HTTP code is %s' % c.getinfo(pycurl.HTTP_CODE))

    return c.get_body()

f = open('page.html', 'w')
f.write (get_page('http://vk.com/audio?id=16132336'))

f.close()
