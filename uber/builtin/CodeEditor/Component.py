# -*- coding: utf-8 -*-

import sys
from PyQt4 import QtCore, QtGui

from component import Component

class CodeEditArea(QtGui.QWidget):
    def __init__(self, form, compliter):
        QtGui.QWidget.__init__(self, form)

        #form.layout.addWidget(self)
        #form.setCentralWidget(self)
        self.complite_num = -1
        self.setGeometry(0, 0, 100, 500)
        self.compliter = compliter
        self.setWindowTitle(u"M")
        self.textarea = QtGui.QTextEdit(self)
        self.comarea = QtGui.QListWidget(self)#QtGui.QTextEdit(self)
        
        self.layout = QtGui.QHBoxLayout()
        self.setLayout(self.layout)
        self.layout.addWidget(self.textarea)
        self.layout.addWidget(self.comarea)

        self.connect(self.textarea, QtCore.SIGNAL("textChanged()"), self.OnInput)

    def GetWord(self, text):
        pos = self.textarea.textCursor().position()
        text = text[:pos]
        while pos > 0 and text[pos - 1] not in ['\n', '\t',' ']:
            pos -= 1
        word = text[pos:]
        return unicode(word)

    def OnInput(self):
        
        text = self.textarea.toPlainText()
        
        self.compliter.Reset()
        self.compliter.FromText(unicode(text))
        
        self.comarea.clear()
        word = self.GetWord(text)
        res = self.compliter.Completelist(word)
        for x in res: self.comarea.addItem(x)
        self.comarea.addItem(word)
        if len(text) > 0 and (text[-1]) == '\t':
            if self.comarea.count > 1:
                if self.complite_num > -1:
                    self.comarea.setItemSelected(self.comarea.item(self.complite_num), False)
                text = text[:len(text) - 1]
                pos = self.textarea.textCursor().position()
                self.complite_num += 1
                if self.complite_num > self.comarea.count:
                    self.comarea.count = 0
                self.comarea.setItemSelected(self.comarea.item(self.complite_num), True)
                #text = text[:len(word)]
                
                self.textarea.setText(text)
        else:
            self.complite_num = -1
                

class CodeEditorComponent(Component):
    def __init__(self):
        Component.__init__(self)
        self.requires_dependences = ['VisualComponent']

    def Register(self, cc):
        form = cc.plugins['VisualComponent'].mainform
        self.compliter = cc.plugins['freakcompliter'].compliterclass()
        self.win = CodeEditArea(form, self.compliter)

def GetComponent():
    return CodeEditorComponent()
