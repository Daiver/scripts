import mpylayer

class Player(object):

    def __init__(self, playlist=[]):
        self.mp = mpylayer.MPlayerControl()
        self.mp.volume = 50
        self.playlist = playlist
        self.curindex = -1
    
    def pause(self):
        self.mp.pause()

    def play(self):
        if self.curindex < 0 or self.curindex >= len(self.playlist):return
        filename = self.playlist[self.curindex]
        self.mp.loadfile(filename)

    def next(self):
        if self.curindex < (len(self.playlist) -1):
            self.curindex += 1
            self.play()
    
    def prev(self):
        if self.curindex > 0:
            self.curindex -= 1
            self.play()

    def newplaulist(self, playlist):
        self.playlist = playlist
        self.curindex = -1
