QT += quick
QT += networkauth

CONFIG += c++11

SOURCES += \
        colors.cpp \
        main.cpp \
        models/lampslistmodel.cpp \
        secrets.cpp \
        yandex/yandexdevicedata.cpp \
        yandex/yandexlamp.cpp \
        yandex/yandexwrapper.cpp

HEADERS += \
    colors.h \
    models/lampslistmodel.h \
    secrets.h \
    yandex/yandexdevicedata.h \
    yandex/yandexlamp.h \
    yandex/yandexwrapper.h

RESOURCES += qml.qrc

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    .gitignore

