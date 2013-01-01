
import os

import logging

import sys

import importlib

from component import Component

logging.basicConfig(level = logging.DEBUG)

class ComponentManager(Component):
    def __init__(self):
        Component.__init__(self)
        self.settings['built-in plugins dir'] = '../builtin'
        self.settings['extern plugins dir'] = '../plugins'
        self.plugins = {}
        self.name = 'ComponentManager'
        self.exec_on_run = []

    def run(self):
        for x in self.exec_on_run: x()

    def LoadPlugins(self):
        pdir = self.settings['built-in plugins dir']
        path = [x for x in os.listdir(pdir) if os.path.exists(os.path.join(pdir, x, '__init__.py'))]
        
        sys.path.append(pdir)
        sys.path.append('ComponentManager.py')
        sys.path.append(os.path.join(pdir, 'component.py'))
        
        plugins = {}
        for x in path:
            try:
                plugin = importlib.import_module(x + '.Component')
                plugins[x] = plugin.GetComponent()
            except Exception as e:
                logging.info('cannot load %s %s' % (x, e))
        self.plugins = plugins

        alreadyreg = {}
        for k, v in plugins.iteritems():
            if k not in alreadyreg:
                try:
                    alreadyreg[k] = v
                    v.Register(self)
                except Exception as e:
                    logging.info('cannot register %s %s' % (v, e))
        
        return plugins

if __name__ == '__main__':
    cc = ComponentManager()
    print cc.LoadPlugins()
    cc.run()


