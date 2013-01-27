
import os
from notimodel import Notification, get_sesnmetneng
import datetime

pathtobd = 'reminder.db'

if __name__ == '__main__':
    ses, met, eng = get_sesnmetneng(pathtobd)
    if not os.path.exists(pathtobd):
        met.create_all(eng)
    
    testNote = Notification('Test', 'test', datetime.datetime.now())
    ses.add(testNote)
    testNote.has_shown = True
    ses.commit()
    ourNotes = ses.query(Notification).all()
    for note in ourNotes:
        print(note)

    '''
    metadata.create_all(engine)
    vasiaUser = User("vasia", "Vasiliy Pypkin", "vasia2000")
    session.add(vasiaUser)
    session.commit()
    ourUser = session.query(User).filter_by(name="vasia").first()
    print(ourUser)
    ourUser.password = 'NoPASS:)'
    session.commit()
    ourUser = None
    '''
    #ourUser = session.query(User).filter_by(name="vasia").first()
    #print(ourUser)
