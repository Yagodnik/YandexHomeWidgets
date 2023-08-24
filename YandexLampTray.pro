QT += quick
QT += networkauth
QT += widgets

CONFIG += c++11

SOURCES += \
        3rdparty/colors.cpp \
        3rdparty/desktopfeatures.cpp \
        main.cpp \
        models/colorsmodel.cpp \
        models/lampslistmodel.cpp \
        3rdparty/secrets.cpp \
        yandex/yandexaccount.cpp \
        yandex/yandexdevice.cpp \
        yandex/yandexdevices.cpp \
        yandex/yandexhome.cpp \
        yandex/yandexlamp.cpp \
        yandex/yandexoauth.cpp

HEADERS += \
    3rdparty/colors.h \
    3rdparty/constants.h \
    3rdparty/desktopfeatures.h \
    models/colorsmodel.h \
    models/lampslistmodel.h \
    3rdparty/secrets.h \
    yandex/yandexaccount.h \
    yandex/yandexdevice.h \
    yandex/yandexdevicedata.h \
    yandex/yandexdevices.h \
    yandex/yandexhome.h \
    yandex/yandexlamp.h \
    yandex/yandexoauth.h

RESOURCES += qml.qrc

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    .gitignore

