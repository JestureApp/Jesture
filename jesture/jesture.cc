#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>
#include <QtQuick/QQuickView>
#include <QtWidgets/QApplication>
#include <iostream>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  QQmlApplicationEngine engine;

  engine.load(QUrl(QStringLiteral("qrc:/jesture/main.qml")));

  if (engine.rootObjects().isEmpty()) {
    return 1;
  }

  return app.exec();
}