import psutil
from datetime import datetime

class ProcessInfo:
    def __init__(self, pid, name, creationtime):
        self.name = name
        self.pid = pid
        self.creationtime = creationtime
        self.endtime = creationtime

    def __repr__(self):
        #return 'ProcessInfo(%s:%s:%s)' % (self.name, str(self.creationtime), str(self.endtime))
        return 'Ps(%d, %s)' % (self.pid, self.name)

def get_processes():
    return {process.pid: ProcessInfo(process.pid, process.name, datetime.now()) for process in psutil.process_iter() if process.pid}

if __name__ == '__main__':

    processes_dict = get_processes()
    print processes_dict

