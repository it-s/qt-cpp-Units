# qt-cpp-Units
Simple unit-to-pixel implementation to simplify mobile development in QML and other

A small collection of lua functions split into cathegories. Each module is fully self-contained and does not depend on any external library.

##Adding you your [existing] project
* Add the library to your git project. Clone it, or use it as a submodule:
```bash
  git submodule add git@github.com:it-s/qt-cpp-Units.git
```
##Initializing the module
* Include it into your Qt project file:
```c++
  include(qt-cpp-Units/Units.pri)
```

##Using Units in your QML project

```c++
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "unit.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
#if (defined(Q_OS_ANDROID) || defined(Q_OS_IOS) || defined(Q_OS_WINPHONE))
    engine.rootContext()->setContextProperty("U", new Units(qApp->screens().first()->size(), QSize(768,1280)));
#else
    engine.rootContext()->setContextProperty("U", new Units());
#endif
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    return app.exec();
}
```

And then in your QML files

```qml
Rectangle {
  x: U.px(15)
  y: U.px(15)
  width: U.px(320)
  height: U.px(200)
}
```
