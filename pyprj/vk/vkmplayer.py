# -*- coding: utf-8 -*-
import subprocess

import atexit

from threading import Thread

devnull = open('/dev/null', 'w')
url = 'http://cs1-10.userapi.com/d9/b26472253342d4.mp3'
ppn = subprocess.Popen(['mplayer', '-prefer-ipv4', url], stderr=devnull)
atexit.register(ppn.terminate)


inp = ''
while inp != 'q':
    inp = raw_input('>')
    print inp
    ppn.communicate(inp)
