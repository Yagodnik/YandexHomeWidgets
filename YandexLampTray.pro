QT += quick
QT += networkauth
QT += widgets

win32:RC_ICONS += assets/icon.ico

CONFIG += c++11

SOURCES += \
        3rdparty/colors.cpp \
        3rdparty/desktopfeatures.cpp \
        3rdparty/temperatures.cpp \
        3rdparty/updater.cpp \
        main.cpp \
        models/colorsmodel.cpp \
        3rdparty/secrets.cpp \
        models/deviceslistmodel.cpp \
        models/temperaturesmodel.cpp \
        yandex/capabilities/basecapability.cpp \
        yandex/capabilities/colorsetting.cpp \
        yandex/capabilities/onoff.cpp \
        yandex/capabilities/range.cpp \
        yandex/yandexaccount.cpp \
        yandex/yandexdevice.cpp \
        yandex/yandexdevices.cpp \
        yandex/yandexhome.cpp \
        yandex/yandexlamp.cpp \
        yandex/yandexoauth.cpp \
        yandex/yandexsocket.cpp \
        yandex/yandexwatcher.cpp

HEADERS += \
        3rdparty/colors.h \
        3rdparty/constants.h \
        3rdparty/desktopfeatures.h \
        3rdparty/temperatures.h \
        3rdparty/updater.h \
        models/colorsmodel.h \
        3rdparty/secrets.h \
        models/deviceslistmodel.h \
        models/temperaturesmodel.h \
        yandex/capabilities/basecapability.h \
        yandex/capabilities/colorsetting.h \
        yandex/capabilities/onoff.h \
        yandex/capabilities/range.h \
        yandex/yandexaccount.h \
        yandex/yandexdevice.h \
        yandex/yandexdevicedata.h \
        yandex/yandexdevices.h \
        yandex/yandexhome.h \
        yandex/yandexlamp.h \
        yandex/yandexoauth.h \
        yandex/yandexsocket.h \
        yandex/yandexwatcher.h

RESOURCES += qml.qrc

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    .gitignore

