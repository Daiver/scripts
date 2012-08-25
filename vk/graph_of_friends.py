# -*- coding: utf-8 -*-

import os

import pygraphviz as pgv

from time import time
from vk_auth import auth, call_api
from vk_config import user_params

def FriendsList(token, uid):
    return call_api('friends.get', [('uid', uid), ('fields', 'first_name,last_name')], token)

def MutualFriendsList(token, source_uid, target_uid):
    #print source_uid, target_uid
    return call_api('friends.getMutual', [('target_uid', target_uid), ('source_uid', source_uid)], token)


def UserAsNode(usr):
    return usr['last_name'] + '_' + usr['first_name']


email = user_params['email']#raw_input("Email: ")
password = user_params['password']#getpass.getpass()

client_id = "2951857" # Vk application ID
token, user_id = auth(email, password, client_id, "users,offline,photos,status,friends,audio")

friends = FriendsList(token, user_id)

FG = pgv.AGraph()

for x in friends:
    FG.add_node(x['uid'], label=UserAsNode(x), shape='rect')
    print x['uid'], UserAsNode(x), 'added'

for x in friends:

    mutual = MutualFriendsList(token, user_id, x['uid'])
    if mutual:
        for y in mutual:
            FG.add_edge(x['uid'], y, color='green')
            #print 'edge', x['uid'], '-', y

print 'start write'
FG.write('file.dot')

print 'finish vk work'

FG.layout()
FG.draw('file.png') 
print FG
