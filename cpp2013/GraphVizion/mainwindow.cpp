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

void MainWindow::on_pushButton_clicked()
{
    GraphCanvas *canvas = dynamic_cast<GraphCanvas*>(this->ui->scrollArea->widget());
    canvas->VG.deleteByIndex(0);
    canvas->repaint();
}
