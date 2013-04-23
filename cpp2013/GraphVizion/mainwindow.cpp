#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "graphcanvas.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    GraphCanvas* canvas = new GraphCanvas();
    ui->scrollArea->setWidget(canvas);
}

MainWindow::~MainWindow()
{
    delete ui;
}
