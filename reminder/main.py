#!/usr/bin/env python

import pynotify
#.Notification
import sys, time
from daemon import Daemon


class NotifyDaemon(Daemon):
    def run(self):
        i = 9
        while True:
            n = pynotify.Notification('Test', 'text '+str(i))
            n.set_timeout(1000)
            i += 1
            n.show()
            #time.sleep(10000)
 
if __name__ == "__main__":
    if not pynotify.init('Reminder daemon'):
        print 'Notify init failed!'
        exit(2)
    daemon = NotifyDaemon('/tmp/reminderdaemon.pid')
    if len(sys.argv) == 2:
        if 'start' == sys.argv[1]:
            print('before start')
            daemon.start()
        elif 'stop' == sys.argv[1]:
            daemon.stop()
        elif 'restart' == sys.argv[1]:
            daemon.restart()
        else:
            print "Unknown command"
            sys.exit(2)
        sys.exit(0)
    else:
        print "usage: %s start|stop|restart" % sys.argv[0]
        sys.exit(2)
