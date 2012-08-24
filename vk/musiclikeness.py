# -*- coding: utf-8 -*-

import os

from vk_auth import auth, call_api
from vk_config import user_params

def outMusicList(music):
    for x in music3:
        print x['artist'], '-' , x['title']

def SimpleCor(li1, li2):
    return len(FindCommonSongs(li1, li2))
    
    

def FriendsList(token, uid):
    return call_api('friends.get', [('uid', uid), ('fields', 'first_name,last_name')], token)

def MusicList(token, uid):
    return call_api('audio.get', [('uid', uid)], token)

def FindCommonSongs(li1, li2):
    res = []
    if not li1 or not li2: return res
    for x in li1:
        for y in li2:
            #if x['url'] == y['url']:
            if x['artist'] == y['artist'] and x['title'] == y['title']:
                res.append(x)
                continue
    return res

email = user_params['email']#raw_input("Email: ")
password = user_params['password']#getpass.getpass()

client_id = "2951857" # Vk application ID
token, user_id = auth(email, password, client_id, "users,offline,photos,status,friends,audio")

friends = FriendsList(token, user_id)

my_music = MusicList(token, user_id)

res = []

for usr in friends:
    try:
        li = MusicList(token, usr['uid'])
    except:
        continue
    rate = SimpleCor(my_music, li)
    res.append((usr, rate))
    #print usr['last_name'], rate

res.sort(key=lambda x:x[1])

for x in res:
    usr = x[0]
    print x[1], usr['first_name'], usr['last_name']

'''


music1 = MusicList(token, user_id)
music2 = MusicList(token, 73476433)

music3 = FindCommonSongs(music1, music2)
#print len(music3)

#outMusicList(music3)
'''
