#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "AppBackend.hpp"


int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    AppBackend backend;
    engine.rootContext()->setContextProperty(
        "backend", &backend
    );

    engine.loadFromModule("TBO", "Main");

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}