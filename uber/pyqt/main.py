#!/usr/bin/python3.2
# -*- coding: utf-8 -*-

import sys
from PyQt4 import QtGui, QtCore

class TestGui(QtGui.QDialog):
    def __init__(self):
        QtGui.QDialog.__init__(self)

        self.setGeometry(600, 300, 500, 150)
        self.setWindowTitle(u"Первое GUI-приложение")
        self.setWindowIcon(QtGui.QIcon('data/crazy.ico'))

        lTitle = QtGui.QLabel(u"Пример GUI-приложения", self)
        lTitle.setAlignment(QtCore.Qt.AlignHCenter)
        lTitle.setGeometry(100,10,300,20)
        fntMyFont = QtGui.QFont(self)
        fntMyFont.setBold(True)
        fntMyFont.setPixelSize(18)
        lTitle.setFont(fntMyFont)

        lDescription = QtGui.QLabel(u"Это наше первое GUI-приложение\nСпециально для http://codeinlife.ru", self)
        lDescription.setAlignment(QtCore.Qt.AlignHCenter)
        lDescription.setGeometry(100, 35, 300, 40)
        fntMyFont2 = QtGui.QFont(self)
        fntMyFont2.setItalic(True)
        fntMyFont2.setPixelSize(14)
        lDescription.setFont(fntMyFont2)

        btnQuit = QtGui.QPushButton(u"Выйти", self)
        btnQuit.setGeometry(150, 75, 200, 50)
        self.connect(btnQuit, QtCore.SIGNAL('clicked()'), quit)

app = QtGui.QApplication(sys.argv)
tg = TestGui()
tg.show()

app.exec_()
