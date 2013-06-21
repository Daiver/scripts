
class API:

    def __init__(self):
        self.command = ''
        self.head = []

    def menuhead(self):
        print 'Some items (type exit to exit):'
        for i in xrange(len(self.head)):
            print i, self.head[i]

    def AddItem(self, s):
        self.head.append(s)

    def userloop(self):
        while self.command != 'exit':
            self.menuhead()
            self.command = raw_input('command here>')

api = API()

def Get_API(d):
    return api

def registration(manager):
    manager.exec_on_run.append(api.userloop)
