# -*- coding: utf-8 -*-

import sys
from PyQt4 import QtCore, QtGui

from component import Component

class TabControllWidget(QtGui.QTabWidget):
    def __init__(self):
        QtGui.QWidget.__init__(self)
        self.addTab(QtGui.QWidget(), '13')
        

class TabContrallerComponent(Component):
    def __init__(self):
        Component.__init__(self)
        self.requires_dependences = ['VisualComponent']
        self.TCW = TabControllWidget()

    def Register(self, cm):
        form = cm.plugins['VisualComponent'].mainform
        form.layout.addWidget(self.TCW)

def GetComponent():
    return TabContrallerComponent()
