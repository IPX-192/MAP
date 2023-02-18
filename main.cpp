#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "MainFrame.h"
#include "datamodel/CUserInfoModel.h"
#include "datamodel/CTagInfoModel.h"
#include "CUserCoordView.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    MainFrame mainFrame;

    QQmlApplicationEngine engine;

    mainFrame.contextToQml(engine);

    qmlRegisterType<CUserCoordView>("Charts", 1, 0, "CUserCoordView");

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);


    CTagInfoModel m_tagDataModel;
    engine.rootContext()->setContextProperty( "TagInfoModel", &m_tagDataModel );

    return app.exec();
}
