#!/usr/bin/ python
# -*- coding: utf-8

from mysqlwork import *
import config as conf


db = MySQLWork(host=conf.conf['dbhost'], user=conf.conf['dbuser'], passwd=conf.conf['dbpassword'], db=conf.conf['dbname'])

str = '1'


sql = "insert into rules (text) values ('ня')"
data = db.Run(sql)

for x in data:
    print x

exit(0)

try:

    str = raw_input('~>')
    while str != '':        

        sql = str
        data = db.Run(sql)

        #db.commit()
        #data = cursor.fetchall()
        for x in data:
            print x
        str = raw_input('~>')
        
finally:
    db.Close()
 
