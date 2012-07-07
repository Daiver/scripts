
from ConsoleFlag import ConsoleFlag

#Reads flags and mksome actions with flags
class FlagReader:

    def __init__(self, flist):
        self.flags = {}
        self.lastparams = []
        self.firstparams = []
        
        if len(flist) > 0:
            self.LoadFromList(flist)

    def IsFlag(self, str):
        return (str != '') and (str[0] == '-')

    def ClearHyphen(self, str):
        res = str[1:]
        if (res != '') and (res[0] == '-'):
            res = res[1:]
        return res

    def LoadFromList(self, flist):

        lastparams = []
        self.flags['firstparams'] = ConsoleFlag('firstparams', lastparams)
        self.firstparams = lastparams
        
        for i in xrange(0, len(flist)):
            if self.IsFlag(flist[i]):
                fname = self.ClearHyphen(flist[i])
                lastparams = []
                self.flags[fname] = ConsoleFlag(fname, lastparams)
            else:
                lastparams.append(flist[i])
        self.flags['lastparams'] = ConsoleFlag('lastparams', lastparams)
        self.lastparams = lastparams
        
        
