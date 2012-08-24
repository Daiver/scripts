#!/usr/bin/python
# -*- coding: UTF-8 -*-

import os
import urllib2

from vk_auth import auth, call_api
from vk_config import user_params
from MusicPlayer import PlayerThread

chachedir = 'musicchache'

def MusicFileName(mscdict):
    return mscdict['artist'] + ' - ' + mscdict['title'] + '.mp3'

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

def DownLoadFile(url, filename):
    open(filename, "w").write(urllib2.urlopen(url).read())

def PlayMe(player, mscdict):
    name = MusicFileName(mscdict)
    path = chachedir + '/' + name
    if not os.path.exists(path):
        print name, '-DownLoading...'
        DownLoadFile(mscdict['url'], path)
    print 'Now Playing', name
    player.PlayIt(path)

email = user_params['email']#raw_input("Email: ")
password = user_params['password']#getpass.getpass()

print 'Connecting to vk.com...'
client_id = "2951857" # Vk application ID
token, user_id = auth(email, password, client_id, "users,offline,friends,audio")

print 'Getting playlist...'
li = MusicList(token, user_id)

print 'Creating daemon...'
player = PlayerThread()
player.start()

prlist = MusicListTitle(li)
print prlist

command = ''
while command != 'q':#cut my arms
    command = raw_input('~>')
    if (command[0] == 'p') and len(command) > 1:
        num = int(command.split()[1])
        if (num > -1) or (num < len(li)):
            PlayMe(player, li[num])
    if command == 'p':
        player.Pause()
    if command == 's':
        player.Stop()
    if command == 'l':
        prlist = MusicListTitle(li)
        print prlist
    if command == 'r':
        li = MusicList(token, user_id)

player.Stop()
player.join()

