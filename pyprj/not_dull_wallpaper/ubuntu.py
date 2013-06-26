
from commands import *

def SetWallpaper(abs_path):
    command_template = 'gsettings set org.gnome.desktop.background picture-uri'
    command = '%s %s%s' % (command_template, 'file://', abs_path)
    return getoutput(command)
