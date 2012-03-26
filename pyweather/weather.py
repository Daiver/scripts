import feedparser
import re
url = 'http://weather.yahooapis.com/forecastrss?p=RSXX0412&u=c'
data = feedparser.parse(url)
summary = data.entries[0].summary
pattern = '<.+?>'
temp = re.sub(pattern,'',summary)
#temp = re.split(r'\n',temp)
print temp
