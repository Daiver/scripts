#include <QtCore>

#include <QtWidgets>
 
int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    QDialog *dialog = new QDialog;
    QLabel *label = new QLabel(dialog);
    label->setText("<font color=red>Hello, World!</font>");
    dialog->show();
    return app.exec();
}
