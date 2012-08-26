#!/usr/bin/python
# -*- coding: UTF-8 -*-

import os
import urllib2

import logging

import pytils

from threading import Thread

from vk_auth import auth, call_api
from vk_config import user_params
from MusicPlayer import PlayerThread
from network import checkConnection
from autocomplete import raw_complete as complete

chachedir = 'musicchache'

def ListFromDir(directory):
    li = [directory + '/' + i for i in os.listdir(directory)]
    res = []
    for item in li:
        x = item[item.find('/') + 1:]
        if (len(x) > 3) and (x[-4:] == '.mp3'):
            i =x.find(' - ')
            artist = x[:i]
            title = x[i + 3:-4]
            res.append({'artist' : artist, 'title' : title})
    return res

def DownLoadFile(url, filename):
    open(filename, "w").write(urllib2.urlopen(url).read())

def MusicFileName(mscdict):
    simpleconc = lambda mscdict:mscdict['artist'] + ' - ' + mscdict['title'] + '.mp3'
    try:
        return pytils.translit.translify(simpleconc(mscdict))
    except :
        return simpleconc(mscdict)

def NormalMusicList(li):
    return [MusicFileName(x) for x in li]

def MusicListTitle(li):
    res = ''
    for i in xrange(len(li)):
        res += str(i) + ' ' + MusicFileName(li[i]) + '\n'
    return res

def MusicList(token, uid):
    try:
        return call_api('audio.get', [('uid', uid)], token)
    except:
        return None


class VKPlayer(PlayerThread):
    def __init__(self, mlist):
        super(VKPlayer, self).__init__()
        self.mlist = mlist
        self.cur_track = 0
        
    def PlayMe(self, mscdict):
        name = MusicFileName(mscdict)
        path = chachedir + '/' + name
        if not os.path.exists(path):
            #print 
            logging.info( name + u' - Downloading...' )

            DownLoadFile(mscdict['url'], path)
        logging.info('Now Playing ' + name)
        self.PlayIt(path)

    def CheckListRange(self):
        return self.cur_track > -1 and self.cur_track < len(self.mlist)

    def Prev(self):
        self.cur_track -= 1
        if self.CheckListRange():
            self.PlayMe(self.mlist[self.cur_track])

    def Next(self):
        self.cur_track += 1
        if self.CheckListRange():
            self.PlayMe(self.mlist[self.cur_track])

    def PlayNum(self, num):
        self.cur_track = num
        if self.CheckListRange():
            self.PlayMe(self.mlist[self.cur_track])

    def Now_Playing(self):
        if self.state in ('Stop', ):
            return '{' + self.state + '}~>'
        res = '{' + MusicFileName(self.mlist[self.cur_track]) + '}'
        if self.state == 'Pause':
            res += ' Paused '
        res += '~>'
        return res


def InputCycle():
    command = ''
    while command != 'q':#cut my arms
        command = raw_input(player.Now_Playing())
        #try:
        if len(command) > 1 and (command[0] == 'p'):
            num = int(command.split()[1])
            player.PlayNum(num)            
        elif command == 'b':
            player.Prev()
        elif command == 'n':
            player.Next()
                
        elif command == 'p':
            if player.state == 'Play':
                player.Pause()
            else:
                if not player.data:
                    player.PlayNum(player.cur_track)
                player.Play()
                
        elif command == 's':
            player.Stop()
        elif command == 'l':
            pl = MusicListTitle(player.mlist)
            print pl
        elif command == 'r':
            print 'refreshing...'
            player.mlist = MusicList(token, user_id)
            pl = MusicListTitle(player.mlist)
            print pl
        else:
            completelist = complete(command, NormalMusicList(player.mlist))
            if len(completelist) == 1:
                num = completelist[0]
                player.PlayNum(num)
            elif len(completelist) > 1:
                for x in completelist:
                    print x, MusicFileName(player.mlist[x])
        #except:
        #    print 'Cannot process command, try again'

#logging.basicConfig(level = logging.DEBUG)

user_id = None
token = None
li = None

email = user_params['email']#raw_input("Email: ")
password = user_params['password']#getpass.getpass()
client_id = "2951857" # Vk application ID

print 'Checking conection....'
if checkConnection():
    print 'Connecting to vk.com...'
    token, user_id = auth(email, password, client_id, "users,offline,friends,audio")

    print 'Getting playlist...'
    li = MusicList(token, user_id)
else:
    print 'Failed to connect google.com'
    print 'Loading chache'
    li = ListFromDir(chachedir)

print 'Creating daemon...'
player = VKPlayer(li)
player.start()

prlist = MusicListTitle(li)
print prlist

inputthread = Thread(target=InputCycle)

inputthread.start()

inputthread.join()
player.Exit()
player.join()

