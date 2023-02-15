#include "Clientdialog.h"
#include <QApplication>
#include <QDir>
#include <QTextCodec>
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDir::setCurrent(QApplication::applicationDirPath());
//    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));//set QString codec
    QUrl url;
    ClientDialog w(url);
    w.show();
    return a.exec();
}
