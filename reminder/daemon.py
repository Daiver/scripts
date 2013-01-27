#!/usr/bin/env python

import pynotify
import time

class NotifyDaemon(object):
    def __init__(self):
        self.index = 0

    def run(self):
        while True:
            self.index += 1
            n = pynotify.Notification('Test', 'text ' + str(self.index))
            n.set_timeout(10000)
            n.show()
            time.sleep(3)

if __name__ == '__main__':
    pynotify.init('reminder')
    daemon = NotifyDaemon()
    daemon.run()
