#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "Control/guicontrolclass.h"
#include "Control/memorydisplayclass.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType< MemoryDisplayClass >( "xhd.memory.drawitem", 1, 0, "XhdMemoryDrawItem" );

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    GuiControlClass gGuiContrlObj;
    gGuiContrlObj.sub_SignalConntectSlot();
    engine.rootContext()->setContextProperty( "MyGuiControlObj", &gGuiContrlObj );


    engine.load(url);

    return app.exec();
}
