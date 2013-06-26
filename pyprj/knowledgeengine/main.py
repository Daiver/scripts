#!/usr/bin/ python
# -*- coding: utf-8

from mysql import *

import config as conf

class KnowledgeEngine:

    def __init__(self, db):
        self.db = db

    def GetListOfKW(self, s):
        s = s.lower()
        s = s.replace(',', ' ')
        s = s.replace('\t', ' ')
        s = s.replace('.', ' ')
        
        li = s.split(' ')#fill it
        res = []

        for x in li:
            if x != '':
                res.append(x)

        return res


    def searchansewer(self, s):
        kw = str(self.GetListOfKW(s))
        kw = kw.replace('[','(')
        kw = kw.replace(']',')')
        sql = u'select distinct ar.ar_value, ar.ar_type, ar.ar_id from articles ar \
            join k2a_links k2a on k2a.ar_id = ar.ar_id \
            join keywords kw on kw.kw_id = k2a.kw_id \
            where kw.word in ' + kw + ';'
        data = db.Run(sql)

        listforsort = []
        
        for x in data:
            sql = 'select sum(weight) from k2a_links \
            where ar_id = ' + str(x[2]) + ' and kw_id in \
            (select kw_id from keywords where word in ' + kw + ');'
            result = db.Run(sql)[0][0]
            listforsort.append( (result, x) )

        listforsort.sort(key=lambda x: -x[0])
        data = [x[1] for x in listforsort]
        
        return data

    def DataFromDB(self, index):
        sql = u'select text from text_articles where ta_id = ' + str(index)
        data = db.Run(sql)
        
        res = data[0][0]        
            
        return res

    def ansewer(self, s):
        data = self.searchansewer(s)
        res = []
        for x in data:
            res.append((self.DataFromDB(x[0]), x[0]))
            
        return res

def showcontent(s):
    i = 1
    for x in s:
        print i,':', x[0], '\nid:', x[1]
        i += 1
db = MySQLWork(host=conf.conf['dbhost'], user=conf.conf['dbuser'], passwd=conf.conf['dbpass'], db=conf.conf['dbname'])

eng = KnowledgeEngine(db)

showcontent( eng.ansewer('c++ '))
#for x in data:
#    print x



