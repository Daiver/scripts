
import os, sys
from notimodel import Notification, get_sesnmetneng
import datetime

pathtobd = 'reminder.db'

def date_from_input(raw):
    '''Formats date from raw input'''
    if len(raw.split(' ')) in [2, 3]:
        today = " ".join(reversed(str(datetime.date.today()).split('-')))
        raw += ' ' + today
    raw = raw.replace('-', ' ')
    raw = raw.replace(':', ' ')
    return datetime.datetime.strptime(raw, '%H %M %d %m %Y')

def add_notification(ses, title, text, raw_date):
    try:
        newnote = Notification(title, text, date_from_input(raw_date))
        ses.add(newnote)
        ses.commit()
        return True
    except Exception as er:
        print('Exception!:\n%s' % str(er))
        return False

if __name__ == '__main__':
    ses, met, eng = get_sesnmetneng(pathtobd)
    if not os.path.exists(pathtobd):
        met.create_all(eng)
    if len(sys.argv) > 2:
        if sys.argv[1] == 'add':
            if len(sys.argv) < 4:
                print('Bad args!')
                exit()
            title = sys.argv[2]
            text = sys.argv[3]
            raw_date = " ".join(sys.argv[4:])
            if add_notification(ses, title, text, raw_date):
                print('Nice :)')
            else:
                print('Something went wrong')
    print('Showing all notes...')
    ourNotes = ses.query(Notification).all()
    for note in ourNotes:
        print(note)

    '''
    testNote = Notification('Test', 'test', datetime.datetime.now())
    ses.add(testNote)
    testNote.has_shown = True
    ses.commit()
    ourNotes = ses.query(Notification).all()
    for note in ourNotes:
        print(note)

    '''
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
