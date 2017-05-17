#include <QtQml/QQmlApplicationEngine>
#include <QtQuickControls2/QQuickStyle>
#include <QtGui/QGuiApplication>
#include "apsg.h"

using apsg::APSG;

int main(int argc, char **argv) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    const QUrl qmlUrl(QLatin1String("qrc:/main.qml"));

    qmlRegisterSingletonType<APSG>("APSG", 1, 0, "APSG", APSG::typeProvider);

    QQuickStyle::setStyle("Material");

    QQmlApplicationEngine engine;
    engine.load(qmlUrl);

    return app.exec();
}