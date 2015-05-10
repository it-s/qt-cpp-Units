TARGET = Units
TEMPLATE = lib
CONFIG += staticlib c++11

SOURCES += Units.cpp
HEADERS += Units.h

isEmpty(PREFIX) {
    unix {
        PREFIX = /usr
    } else {
        PREFIX = $$[QT_INSTALL_PREFIX]
    }
}

install_headers.files = Units.h
install_headers.path = $$PREFIX/include
target.path = $$PREFIX/lib
INSTALLS += install_headers target
