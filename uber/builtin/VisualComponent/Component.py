# -*- coding: utf-8 -*-

import sys
from PyQt4 import QtCore, QtGui

from component import Component

from ComponentManager import ComponentManager


        
class MainForm(QtGui.QMainWindow):
    def __init__(self,*args):
        QtGui.QMainWindow.__init__(self,*args)
        self.setWindowTitle(u"Main Form")
        
        self.layout = QtGui.QHBoxLayout()
        self.setLayout(self.layout)
        
        menubar = self.menuBar()
        file = menubar.addMenu('&File')
        file.addAction('ext')

class VisualComponent(ComponentManager):
    def __init__(self):
        ComponentManager.__init__(self)
        self.app = QtGui.QApplication([])
        self.mainform = MainForm()
        self.name = 'VisualComponent'

    def Register(self, cc):
        cc.exec_on_run.append(self.run)
        return True

    def run(self):
        
        self.mainform.show()
        self.app.exec_()
        return None
        

def GetComponent():
    return VisualComponent()

    
'''
class AgeSelector(QtGui.QWidget):
    def __init__(self,*args):
        QtGui.QWidget.__init__(self,*args)
        self.setWindowTitle(u"Вводим свой возраст")
        # создаем объекты:
        spinbox = QtGui.QSpinBox()
        slider = QtGui.QSlider(QtCore.Qt.Horizontal)
        self.textarea = QtGui.QTextEdit(self)
        
        self.textarea.customContextMenuRequested.connect(self.ShowMenu)
        # устанавливаем границы значений:
        spinbox.setRange(0, 130)
        slider.setRange(0, 130)
        # создаем соединения:
        self.connect(spinbox, QtCore.SIGNAL("valueChanged(int)"), \
                slider, QtCore.SLOT("setValue(int)"))
        self.connect(slider, QtCore.SIGNAL("valueChanged(int)"), \
                spinbox, QtCore.SLOT("setValue(int)"))
        self.connect(spinbox, QtCore.SIGNAL("valueChanged(int)"), self.log_to_console)
        self.connect(self.textarea, QtCore.SIGNAL("textChanged()"), self.text_changed)
        # задаем начальное значение:
        spinbox.setValue(27)
        # создаем горизонтальное размещение объектов в окне:
        layout = QtGui.QVBoxLayout()
        layout.addWidget(spinbox)
        layout.addWidget(slider)
        layout.addWidget(self.textarea)
        self.setLayout(layout)

    def ShowMenu(self):
        self.conmenu = self.textarea.createStandardContextMenu()
        self.conmenu.addAction('exit')
        self.conmenu.show()
        print 'UUU'

    def text_changed(self):
        print self.textarea.toPlainText()
        self.ShowMenu()
        
    # слот, пишущий лог изменений в консоль:
    def log_to_console(self,i):
        print i
'''
