from vk_auth import auth, call_api
from vk_config import user_params

def FriendsList(token, uid):
    return call_api('friends.get', [('uid', uid), ('fields', 'first_name,last_name')], token)

def MusicList(token, uid):
    return call_api('friends.get', [('uid', uid)], token)

email = user_params['email']#raw_input("Email: ")
password = user_params['password']#getpass.getpass()

client_id = "2951857" # Vk application ID
token, user_id = auth(email, password, client_id, "offline,photos,status,friends,audio")


print FriendsList(token, user_id)
