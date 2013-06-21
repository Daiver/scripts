required_plugins = ['testmenu']
def registration(manager):
    print 'Reg! In req_test'
    manager.API['testmenu'].AddItem(':)')
    manager.API['testmenu'].AddItem(':(')


def Get_API(d): return 'HI! x 2'
