
from commands import *

def SetWallpaper(abs_path):
    command_template = 'awsetbg'
    command = '%s %s%s' % (command_template, '', abs_path)
    return getoutput(command)
