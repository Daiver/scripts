#!/usr/bin/ python
# -*- coding: utf-8
import MySQLdb
import datetime

class MySQLWork:
    '''Small class for simple work with db '''
    def __init__(self,  host, user, passwd, db):
        self.db = MySQLdb.connect(host=host, user=user, passwd=passwd, db=db, charset='utf8')
        self.cursor = self.db.cursor()
        self.log = {}

    def __del__(self):
        try:
            self.Close()
        except:
            pass
    
    def Close(self):
        self.db.commit()
        self.db.close()
    
    def CountOfQuery(self):
        return len(self.log)
    
    def Commit(self):
        self.db.commit()

    def Run(self,str):
        self.cursor.execute(str.decode('utf8'))
        date = datetime.datetime.now()
        self.log[date] = str
        return self.cursor.fetchall()    