#!/usr/bin/env python

import pynotify
import time
import datetime
from notimodel import Notification, get_sesnmetneng

class NotifyDaemon(object):
    def __init__(self, dbses):
        self.dbses = dbses
        self.timeout = 5

    def run(self):
        while True:
            now = datetime.datetime.now()
            cand_notes = self.dbses.query(Notification).filter(Notification.dt < now).all()
            for note in cand_notes:
                if not note.has_shown:
                    n = pynotify.Notification('NOTIFICATION\n%s' % note.title, '%s\nDate:%s' % ( note.text, str(note.dt)))
                    n.set_timeout(10000)
                    n.show()
                    note.has_shown = True
            self.dbses.commit()
            time.sleep(self.timeout)

if __name__ == '__main__':
    pynotify.init('reminder')
    daemon = NotifyDaemon(get_sesnmetneng('reminder.db')[0])
    daemon.run()
