#include "serverdialog.h"
#include <QApplication>
#include <QDir>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDir::setCurrent(QApplication::applicationDirPath());
//    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));//set QString codec
    ServerDialog w;
    w.show();
    return a.exec();

}
