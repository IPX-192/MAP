#include "MainFrame.h"

MainFrame::MainFrame(QObject *parent)
{

}

MainFrame::~MainFrame()
{

}

void MainFrame::contextToQml(QQmlApplicationEngine &engine)
{
    engine.rootContext()->setContextProperty( "InterAction", &m_SocketServer );
}

void MainFrame::initialize()
{

}
