#!/usr/bin/ python
# -*- coding: utf-8

from mysqlwork import *
import config as conf

# подключаемся к базе данных (не забываем указать кодировку, а то в базу запишутся иероглифы)
db = MySQLWork(host=conf.conf['dbhost'], user=conf.conf['dbuser'], passwd=conf.conf['dbpassword'], db=conf.conf['dbname'])

str = '1'

'''sql = 'SET NAMES "utf8"; SET CHARACTER SET \'utf8\''

db.Run(sql)
db.db.commit()
'''
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
    
'''
CREATE TABLE `ForumDB`.`users` (
  `users_id` INTEGER  NOT NULL AUTO_INCREMENT,
  `name` varchar (255)  NOT NULL,
  `email` varchar (255)  NOT NULL,
  `avatar` varchar (255)  NOT NULL,
  PRIMARY KEY (`users_id`)
)
ENGINE = InnoDB;

'''

'''
CREATE TABLE `ForumDB`.`messages` (
  `msg_id` INTEGER  NOT NULL AUTO_INCREMENT,
  `text` LONGTEXT  NOT NULL,
  `create_date` DATETIME  NOT NULL,
  `changed_date` DATETIME  DEFAULT NULL,
  PRIMARY KEY (`msg_id`)
)
ENGINE = MyISAM;

'''

'''
CREATE TABLE `ForumDB`.`genders` (
  `gndr_id` Integer  NOT NULL AUTO_INCREMENT,
  `name` varchar(255)  NOT NULL,
  PRIMARY KEY (`gndr_id`)
)
ENGINE = MyISAM;

'''

'''

sql = 'CREATE TABLE `ForumDB`.`user_states` (\
  `st_id` Integer  NOT NULL AUTO_INCREMENT,\
  `name` varchar(255)  NOT NULL,\
  PRIMARY KEY (`st_id`)\
)\
ENGINE = MyISAM;'

'''

'''

sql = 'CREATE TABLE `ForumDB`.`message_states` (\
  `msg_st_id` Integer  NOT NULL AUTO_INCREMENT,\
  `name` varchar(255)  NOT NULL,\
  PRIMARY KEY (`msg_st_id`)\
)\
ENGINE = MyISAM;'

'''

'''
CREATE TABLE `ForumDB`.`sections` (
  `sct_id` integer  NOT NULL AUTO_INCREMENT,
  `sct_name` varchar(255)  NOT NULL,
  `create_date` datetime  NOT NULL,
  PRIMARY KEY (`sct_id`)
)
ENGINE = MyISAM;

'''
