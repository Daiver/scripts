#!/usr/bin/python
# -*- coding: UTF-8 -*-

import urllib2

import logging

import pytils

import os
from vk_auth import auth, call_api

from network import checkConnection
from autocomplete import raw_complete as complete
from ConfigWork import CreateFromConsole

from ThreadPlayer import Player

if not os.path.exists('vk_config.py'):
    print 'Making new config...'
    CreateFromConsole()            
from vk_config import user_params

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
    res = ''
    simpleconc = lambda mscdict:mscdict['artist'] + ' - ' + mscdict['title'] + '.mp3'
    try:
        res = pytils.translit.translify(simpleconc(mscdict))
    except :
        res = simpleconc(mscdict)

    res.replace('/', '|')
    res.replace('\\', '|')
    return res

def SimpleMusicList(li):
    return [MusicFileName(x) for x in li]

def MusicListTitle(li):
    res = ''
    for i in xrange(len(li)):
        res += str(i) + ' ' + MusicFileName(li[i]) + '\n'
    return res


class MusicManager:
    def __init__(self, user_paramsi, chache_dir):
        self.user_params = user_params
        self.chache_dir = chache_dir

    def GetMusicListFromUID(self, uid):
        token = self.user_params['token']
        try:
            if checkConnection():
                return call_api('audio.get', [('uid', uid)], token)
            return ListFromDir(self.chache_dir)
        except:
            return None

    def GetMusicList(self):
        return self.GetMusicListFromUID(self.user_params['user_id'])


class VkPlayer(Player):
    def __init__(self, user_params):
        self.chache_dir = 'music_chache'
        self.vkmm = MusicManager(user_params, self.chache_dir)
        super(VkPlayer, self).__init__( self.vkmm.GetMusicList())

    def play(self):
        if self.curindex < 0 or self.curindex >= len(self.playlist):return
        msc = self.playlist[self.curindex]
        filename = MusicFileName(msc)
        path = self.chache_dir + '/' + filename
        if not os.path.exists(path):
            DownLoadFile(msc['url'], path)
        self.mp.loadfile(path)

#player  = VkPlayer(user_params)
#player.curindex = 1
#player.next()
#raw_input()
#vkmm = MusicManager(user_params, 'music_chache')
#for s in SimpleMusicList((vkmm.GetMusicList())):
#    print s

