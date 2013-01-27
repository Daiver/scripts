import sqlalchemy
from sqlalchemy.ext.declarative import declarative_base
Base = declarative_base()
from sqlalchemy.orm import sessionmaker
from sqlalchemy import Table, Column, Integer, String, MetaData, ForeignKey, DateTime

class Notification(Base):
    __tablename__ = 'notifications'
    id = Column(Integer, primary_key=True)
    title = Column(String)
    text = Column(String)
    dt = Column(DateTime)
 
    def __init__(self, title, text, dt):
        self.title = title
        self.text = text
        self.dt = dt
    
    def __repr__(self):
        return "<Notification('%s','%s', '%s')>" % (self.title, self.text, str(self.dt))

def get_sesnmet(pathtodb):
    engine = sqlalchemy.create_engine('sqlite:///' + pathtodb, echo=False)
    Session = sessionmaker(bind=engine)
    session = Session()
    metadata = Base.metadata
    return session, metadata

