import sqlalchemy
#from sqlalchemy import create_engine
from sqlalchemy.ext.declarative import declarative_base
Base = declarative_base()
from sqlalchemy.orm import sessionmaker
from sqlalchemy import Table, Column, Integer, String, MetaData, ForeignKey

class User(Base):
    __tablename__ = 'users'
    id = Column(Integer, primary_key=True)
    name = Column(String)
    fullname = Column(String)
    password = Column(String)
 
    def __init__(self, name, fullname, password):
        self.name = name
        self.fullname = fullname
        self.password = password
    def __repr__(self):
        return "<User('%s','%s', '%s')>" % (self.name, self.fullname, self.password)

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
