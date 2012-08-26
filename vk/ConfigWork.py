
import getpass

template = '''
user_params = {
    'email' : '%s',
    'password' : '%s',
    'appid' : ''
}\n'''


def CreateOwnConfig(email, password):
    return template % (email, password)

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
