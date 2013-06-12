import os
import sqlalchemy
from sqlalchemy.ext.declarative import declarative_base
Base = declarative_base()
from sqlalchemy.orm import sessionmaker
from sqlalchemy import Table, Column, Integer, String, MetaData, ForeignKey, DateTime, Boolean


class ProcessInfo(Base):
    __tablename__ = 'ProcessStat'
    id = Column(Integer, primary_key=True)
    name = Column(String)
    pid = Column(Integer)
    starttime = Column(DateTime)
    endtime = Column(DateTime)

    def __init__(self, pid, name, starttime, endtime):
        self.name = name
        self.pid = pid
        self.starttime = starttime
        self.endtime = endtime

    def __repr__(self):
        return 'Ps(%d, %s, %s : %s)' % (self.pid, self.name, str(self.starttime), str(self.endtime))

def get_sesnmetneng(pathtodb):
    engine = sqlalchemy.create_engine('sqlite:///' + pathtodb, echo=False)
    Session = sessionmaker(bind=engine)
    session = Session()
    metadata = Base.metadata
    if not os.path.exists(pathtodb):
        metadata.create_all(engine)
    return session, metadata, engine

