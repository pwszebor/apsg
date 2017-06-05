#include <QtQml/QQmlApplicationEngine>
#include <QtQuickControls2/QQuickStyle>
#include <QtWidgets/QApplication>
#include <thread>
#include "apsg.h"
#include "plot.h"

int main(int argc, char **argv) {
    std::cout << __PRETTY_FUNCTION__ << std::this_thread::get_id() << "\n";
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    const QUrl qmlUrl(QLatin1String("qrc:/ui/main.qml"));

    qmlRegisterSingletonType<APSG>("APSG", 1, 0, "APSG", APSG::typeProvider);
    qmlRegisterType<Plot>("Plot", 1, 0, "Plot");

    QQuickStyle::setStyle("Material");

    QQmlApplicationEngine engine;
    engine.load(qmlUrl);

    return app.exec();
}