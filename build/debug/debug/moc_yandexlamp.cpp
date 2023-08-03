/****************************************************************************
** Meta object code from reading C++ file 'yandexlamp.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.1.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../yandex/yandexlamp.h"
#include <QtNetwork/QSslError>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'yandexlamp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.1.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_YandexLamp_t {
    const uint offsetsAndSize[24];
    char stringdata0[93];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_YandexLamp_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_YandexLamp_t qt_meta_stringdata_YandexLamp = {
    {
QT_MOC_LITERAL(0, 10), // "YandexLamp"
QT_MOC_LITERAL(11, 7), // "onReply"
QT_MOC_LITERAL(19, 0), // ""
QT_MOC_LITERAL(20, 14), // "QNetworkReply*"
QT_MOC_LITERAL(35, 5), // "reply"
QT_MOC_LITERAL(41, 2), // "on"
QT_MOC_LITERAL(44, 3), // "off"
QT_MOC_LITERAL(48, 13), // "setBrightness"
QT_MOC_LITERAL(62, 10), // "brightness"
QT_MOC_LITERAL(73, 8), // "setColor"
QT_MOC_LITERAL(82, 4), // "QRgb"
QT_MOC_LITERAL(87, 5) // "color"

    },
    "YandexLamp\0onReply\0\0QNetworkReply*\0"
    "reply\0on\0off\0setBrightness\0brightness\0"
    "setColor\0QRgb\0color"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_YandexLamp[] = {

 // content:
       9,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   44,    2, 0x08,    0 /* Private */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
       5,    0,   47,    2, 0x02,    2 /* Public */,
       6,    0,   48,    2, 0x02,    3 /* Public */,
       7,    1,   49,    2, 0x02,    4 /* Public */,
       9,    1,   52,    2, 0x02,    6 /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // methods: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, 0x80000000 | 10,   11,

       0        // eod
};

void YandexLamp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<YandexLamp *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onReply((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 1: _t->on(); break;
        case 2: _t->off(); break;
        case 3: _t->setBrightness((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->setColor((*reinterpret_cast< QRgb(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QNetworkReply* >(); break;
            }
            break;
        }
    }
}

const QMetaObject YandexLamp::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_YandexLamp.offsetsAndSize,
    qt_meta_data_YandexLamp,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_YandexLamp_t

, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QNetworkReply *, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QRgb, std::false_type>

>,
    nullptr
} };


const QMetaObject *YandexLamp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *YandexLamp::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_YandexLamp.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int YandexLamp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
