# -*- coding: utf-8 -*-

import sys
import os

from PyQt4 import QtCore, QtGui

from component import Component

class PluginMagagerWindow(QtGui.QMainWindow):
    def __init__(self, cm):
        QtGui.QMainWindow.__init__(self)
        self.setWindowTitle(u"M")
        self.cm = cm
        self.plugin_list = QtGui.QListWidget(self)#QtGui.QTextEdit(self)
        self.layout = QtGui.QVBoxLayout()
        self.layout.addWidget(self.plugin_list)
        self.setLayout(self.layout)
        self.setCentralWidget(self.plugin_list)
        self.FillList()
        
    def FillList(self):
        if len(self.cm.plugins) > 0:
            self.plugin_list.addItem('Built-in modules:')
        for k, v in self.cm.plugins.iteritems():
            self.plugin_list.addItem('Plugin "%s" as %s ' % (k, v))

class PluginManager(Component):
    def __init__(self):
        Component.__init__(self)
        self.requires_dependences = ['VisualComponent']

    def Register(self, cm):
        form = cm.plugins['VisualComponent'].mainform
        menubar = form.menuBar()
        self.PMWindow = PluginMagagerWindow(cm)
        exitaction = QtGui.QAction(u'Plugin Manager', self.PMWindow)
        plugmenu = menubar.addMenu('&Plugins')
        plugmenu.addAction(exitaction)
        self.PMWindow.connect(exitaction, QtCore.SIGNAL('triggered()'), QtCore.SLOT('show()'))

def GetComponent():
    return PluginManager()
