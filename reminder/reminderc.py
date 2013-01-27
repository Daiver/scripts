
import os
from notimodel import Notification, get_sesnmet


if __name__ == '__main__':
    engine = sqlalchemy.create_engine('sqlite:///reminders.db', echo=False)
    Session = sessionmaker(bind=engine)
    session = Session()
    metadata = Base.metadata
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
    ourUser = session.query(User).filter_by(name="vasia").first()
    print(ourUser)
