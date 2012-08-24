#!/usr/bin/python
# -*- coding: UTF-8 -*-

import os
import urllib2

from vk_auth import auth, call_api
from vk_config import user_params

def MusicList(token, uid):
    try:
        return call_api('audio.get', [('uid', uid)], token)
    except:
        return None

def DownLoadFile(url, filename):
    open(filename, "w").write(urllib2.urlopen(url).read())

email = user_params['email']#raw_input("Email: ")
password = user_params['password']#getpass.getpass()

client_id = "2951857" # Vk application ID
token, user_id = auth(email, password, client_id, "users,offline,friends,audio")

li = MusicList(token, user_id)

DownLoadFile(li[0]['url'], 'musicchache/' + li[0]['artist'] + '-' + li[0]['title'] + '.mp3')
