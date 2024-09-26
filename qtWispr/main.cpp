
#include "mainwindow.h"
#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Load the custom font
    int fontId = QFontDatabase::addApplicationFont(":/fonts/GohuFont.ttf");
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont gohuFont(fontFamily, 11);
    a.setFont(gohuFont);

    MainWindow w;
    w.show();

    return a.exec();
}
