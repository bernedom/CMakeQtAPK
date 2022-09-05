#include <QtCore/QStringLiteral>
#include <QtCore/QUrl>
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>
#include <QtQuick/QQuickWindow>

#include "slideshow.h"

int main(int argc, char **argv) {
  QGuiApplication app(argc, argv);
  app.setApplicationDisplayName("QML example");
  QQmlApplicationEngine qmlEngine;
  

  SlideShow slideShow;
  qmlEngine.rootContext()->setContextProperty("SlideShow", &slideShow);
  qmlEngine.load(QUrl(QStringLiteral("qrc:/main.qml")));

  return app.exec();
}