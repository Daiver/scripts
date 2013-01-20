#!/usr/bin/ python
# -*- coding: utf-8

import MySQLdb
import string

# подключаемся к базе данных (не забываем указать кодировку, а то в базу запишутся иероглифы)
db = MySQLdb.connect(host="localhost", user="root", passwd="www22341", db="ForumDB", charset='utf8')
# формируем курсор, с помощью которого можно исполнять SQL-запросы
cursor = db.cursor()

str = '1'

try:

    while str != '':

        str = raw_input('~>')

        sql = str
        cursor.execute(sql)

        db.commit()
        data = cursor.fetchall()
        for x in data:
            print x
        
finally:
    db.close()