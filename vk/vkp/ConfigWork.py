from vk_auth import auth, call_api

import getpass

template = '''
user_params = {
    'email' : '%s',
    'token' : '%s',
    'client_id' : '%s',
    'user_id' : '%s',
}\n'''


def CreateOwnConfig(email, password):
    client_id = "2951857" # Vk application ID
    token, user_id = auth(email, password, client_id, "users,offline,friends,audio")
    return template % (email, token, client_id, user_id)

def WriteOwnConfig(email, password):
    f = open('vk_config.py', 'w')
    f.write(CreateOwnConfig(email, password))
    f.close()

def CreateFromConsole():
    print 'type your email:'
    email = raw_input('~>')
    password = getpass.getpass()
    WriteOwnConfig(email, password)

if __name__ == '__main__':
    CreateFromConsole()
