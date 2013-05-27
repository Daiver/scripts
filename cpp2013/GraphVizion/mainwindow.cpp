#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "graphcanvas.h"
#include <QFileDialog>

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
    QString filename = QFileDialog::getSaveFileName(this,
                                           tr("Save Xml"), ".",
                                           tr("Xml files (*.xml)"));
    canvas->saveIntoFile(filename);
}

void MainWindow::on_pushButton_2_clicked()
{
    GraphCanvas *canvas = dynamic_cast<GraphCanvas*>(this->ui->scrollArea->widget());
    canvas->setVertexAddTool();
}

void MainWindow::on_pushButton_3_clicked()
{
    GraphCanvas *canvas = dynamic_cast<GraphCanvas*>(this->ui->scrollArea->widget());
    canvas->setVertexMoveTool();
}

void MainWindow::on_pushButton_4_clicked()
{
    GraphCanvas *canvas = dynamic_cast<GraphCanvas*>(this->ui->scrollArea->widget());
    canvas->setVertexDeleteTool();
}

void MainWindow::on_pushButton_5_clicked()
{
    GraphCanvas *canvas = dynamic_cast<GraphCanvas*>(this->ui->scrollArea->widget());
    canvas->setEdgeAddTool();
}

void MainWindow::on_pushButton_6_clicked()
{
    GraphCanvas *canvas = dynamic_cast<GraphCanvas*>(this->ui->scrollArea->widget());
    canvas->setVertexMarkTool();
}

void MainWindow::on_pushButton_7_clicked()
{
    GraphCanvas *canvas = dynamic_cast<GraphCanvas*>(this->ui->scrollArea->widget());
    QString filename = QFileDialog::getOpenFileName(this,
                                           tr("read Xml"), ".",
                                           tr("Xml files (*.xml)"));
    canvas->loadFromFile(filename);
}
