
#POD, describes flag
class ConsoleFlag:
    def __init__(self, name, params):
        self.name = name
        self.params = params

    def __str__(self):
        res = self.name + ':'
        for s in self.params:
            res += s + ' '
        return res
        
