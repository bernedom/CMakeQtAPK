#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>
#include <QtQuick/QQuickWindow>
#include <qguiapplication.h>
#include <qqmlapplicationengine.h>
#include <qstringliteral.h>
#include <qurl.h>

int main(int argc, char** argv)
{
    QGuiApplication app(argc, argv);
    app.setApplicationDisplayName("QML example");
    QQmlApplicationEngine qmlEngine;
    qmlEngine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}