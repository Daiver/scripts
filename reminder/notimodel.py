import sqlalchemy
from sqlalchemy.ext.declarative import declarative_base
Base = declarative_base()
from sqlalchemy.orm import sessionmaker
from sqlalchemy import Table, Column, Integer, String, MetaData, ForeignKey, DateTime, Boolean

class Notification(Base):
    __tablename__ = 'notifications'
    id = Column(Integer, primary_key=True)
    title = Column(String)
    text = Column(String)
    dt = Column(DateTime)
    has_shown = Column(Boolean)
 
    def __init__(self, title, text, dt):
        self.title = title
        self.text = text
        self.dt = dt
        self.has_shown = False
    
    def __repr__(self):
        return "<Notification('%s','%s', '%s', '%s')>" % (self.title, self.text, str(self.dt), 'already swown' if self.has_shown else 'waiting to show')

def get_sesnmetneng(pathtodb):
    engine = sqlalchemy.create_engine('sqlite:///' + pathtodb, echo=False)
    Session = sessionmaker(bind=engine)
    session = Session()
    metadata = Base.metadata
    return session, metadata, engine

