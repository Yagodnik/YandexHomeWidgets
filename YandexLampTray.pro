QT += quick
QT += networkauth

CONFIG += c++11

SOURCES += \
        3rdparty/colors.cpp \
        main.cpp \
        models/lampslistmodel.cpp \
        3rdparty/secrets.cpp \
        yandex/yandexdevicedata.cpp \
        yandex/yandexhome.cpp \
        yandex/yandexlamp.cpp \
        yandex/yandexoauth.cpp

HEADERS += \
    3rdparty/colors.h \
    models/lampslistmodel.h \
    3rdparty/secrets.h \
    yandex/yandexdevicedata.h \
    yandex/yandexhome.h \
    yandex/yandexlamp.h \
    yandex/yandexoauth.h

RESOURCES += qml.qrc

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    .gitignore

