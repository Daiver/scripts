import psutil
from datetime import datetime
import os
import time

from processinfomodel import ProcessInfo, get_sesnmetneng

def get_processes():
    return {process.pid:[process.name, datetime.now()] for process in psutil.process_iter() if process.pid}

if __name__ == '__main__':

    ses, met, eng = get_sesnmetneng('ps.db')
    old_info = ses.query(ProcessInfo).all()
    for x in old_info: print x

    processes_dict = get_processes()
    while True:
        try:
            time.sleep(1)
            tmp_dict = get_processes()
            for old in processes_dict:
                if old not in tmp_dict:
                    pi = ProcessInfo(old, processes_dict[old][0], processes_dict[old][1], datetime.now())
                    ses.add(pi)
                else:
                    tmp_dict[old][1] = processes_dict[old][1]
            ses.commit()
            processes_dict = tmp_dict
        except KeyboardInterrupt as e:
            for key in processes_dict:
                ses.add(ProcessInfo(key, processes_dict[key][0], processes_dict[key][1], datetime.now()))
            ses.commit()
            print 'KeyboardInterrupt', e
            break

        except Exception as e:
            print e

