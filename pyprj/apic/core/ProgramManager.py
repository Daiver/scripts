# -*- coding: utf-8 *-*

import os

import logging

import sys

import importlib

import settings as stg

class ProgramManager:

    def __init__(self, abspath):
        self.plugins = {}  # plugins list
        self.API = {}  # API list
        self.exec_on_run = []  # list of methods, this methods will be excuted after start
        self.path_to_builtin = os.path.join(abspath, stg.path_to_builtin)
        sys.path.append(self.path_to_builtin)

    def LoadPlugin(self, pluginname):#load plugin by name
        try:
            plugin = importlib.import_module('%s.%s' % (pluginname, '__init__'))
            self.plugins[pluginname] = plugin
            return True
        except Exception as e:
            logging.info('cannot load %s: %s' % (pluginname, e))
            return False

    def LoadAllPlugins(self):
        files = [x for x in os.listdir(self.path_to_builtin)
                if os.path.exists(os.path.join(self.path_to_builtin, x, '__init__.py'))]
        for x in files:
            self.LoadPlugin(x)

    def RegPlugin(self, plugname):#regplugin from 'plugins' list
        if plugname not in self.plugins:
            logging.info('cannot get api from %s: %s' % (plugname, 'module not found!11'))
            return False
        plugin = self.plugins[plugname]
        if hasattr(plugin, 'required_plugins') and len(plugin.required_plugins) > 0:
            for x in plugin.required_plugins:
                if not x in self.API:
                    res = self.RegPlugin(x)
                    if not res: return False
        if hasattr(plugin, 'registration'):
            plugin.registration(self)
        try:
            api = plugin.Get_API(self)
            self.API[plugname] = api
            return True
        except Exception as e:
            logging.info('cannot get api from %s: %s' % (plugname, e))
            return False

    def RegAllPlugins(self):
        for pl in self.plugins:
            if pl not in self.API:
                self.RegPlugin(pl)

    def run(self):#excute methods
        for x in self.exec_on_run: x()
