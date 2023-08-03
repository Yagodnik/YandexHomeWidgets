QT += quick
QT += networkauth

CONFIG += c++11

SOURCES += \
        colors.cpp \
        main.cpp \
        models/lampslistmodel.cpp \
        yandex/yandexdevicedata.cpp \
        yandex/yandexlamp.cpp

HEADERS += \
    colors.h \
    models/lampslistmodel.h \
    yandex/yandexdevicedata.h \
    yandex/yandexlamp.h

RESOURCES += qml.qrc

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    .gitignore

