
import threading
from threading import Thread, Event

import Queue


import pyaudio
import mad
import sys

class PlayerThread(Thread):

    def __init__(self):
        super(PlayerThread, self).__init__()
        
        self.messages = Queue.Queue()
        self.daemon = True
        self.data = None
        self.stream = None
        self.mf = None
        self.pya = pyaudio.PyAudio()

        self.state = 'Stop'

    def NextData(self):
        return self.mf.read()

    def Stop(self):
        self.state = 'Stop'

    def Exit(self):
        self.state = 'Exit'

    def Pause(self):
        self.state = 'Pause'

    def Play(self):
        self.state = 'Play'

    def Next():
        return None

    def PlayIt(self, filename):
        self.mf = mad.MadFile(filename)
        self.pya = pyaudio.PyAudio()
        p = self.pya
        self.stream = p.open(format =
                    p.get_format_from_width(pyaudio.paInt32),
                    channels = 2,
                    rate = self.mf.samplerate(),
                    output = True)
        self.data = self.NextData()
        self.state = 'Play'

    def isStop(self):
        return self.data == None

    def run(self):
        self.state = 'Play'
        playnext = lambda : (self.data != None) and self.state == 'Play'
        while self.state != 'Exit':
            #message = self.commands.get() if not self.commands.empty() else None
            #self.ProcessMessage(message)
            if playnext():
                self.stream.write(self.data)
                self.data = self.NextData()
                
                if self.data == None:
                    self.state = 'Stop'
                    self.Next()
                
        self.data = None
        self.stream = None
        self.mf = None
'''
def PlayIt(filename, event_for_pause):

    mf = mad.MadFile(filename)

    p = pyaudio.PyAudio()

    # open stream
    stream = p.open(format =
                    p.get_format_from_width(pyaudio.paInt32),
                    channels = 2,
                    rate = mf.samplerate(),
                    output = True)
    # read data
    data = mf.read()
    # play stream
    while data != None:
        stream.write(data)
        data = mf.read()
    stream.close()
    p.terminate()

t1 = PlayerThread()

t1.start()
t1.PlayIt('musicchache/1.mp3')

command = ''
while command != 'q':
    command = raw_input('>>')
    if command == 'p':
        t1.Pause()
    else:
        t1.Play()

t1.Stop()

t1.join()

#musicthread = Thread(target=PlayIt, args=('musicchache/1.mp3',))
#musicthread.start()

#musicthread.join()
'''
