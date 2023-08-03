/****************************************************************************
** Meta object code from reading C++ file 'colors.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.1.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../colors.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'colors.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.1.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Colors_t {
    const uint offsetsAndSize[14];
    char stringdata0[58];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_Colors_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_Colors_t qt_meta_stringdata_Colors = {
    {
QT_MOC_LITERAL(0, 6), // "Colors"
QT_MOC_LITERAL(7, 11), // "getColorHex"
QT_MOC_LITERAL(19, 0), // ""
QT_MOC_LITERAL(20, 5), // "index"
QT_MOC_LITERAL(26, 11), // "getColorRgb"
QT_MOC_LITERAL(38, 4), // "QRgb"
QT_MOC_LITERAL(43, 14) // "getColorsCount"

    },
    "Colors\0getColorHex\0\0index\0getColorRgb\0"
    "QRgb\0getColorsCount"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Colors[] = {

 // content:
       9,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   32,    2, 0x02,    0 /* Public */,
       4,    1,   35,    2, 0x02,    2 /* Public */,
       6,    0,   38,    2, 0x02,    4 /* Public */,

 // methods: parameters
    QMetaType::QString, QMetaType::Int,    3,
    0x80000000 | 5, QMetaType::Int,    3,
    QMetaType::Int,

       0        // eod
};

void Colors::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Colors *>(_o);
        (void)_t;
        switch (_id) {
        case 0: { QString _r = _t->getColorHex((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 1: { QRgb _r = _t->getColorRgb((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QRgb*>(_a[0]) = std::move(_r); }  break;
        case 2: { int _r = _t->getColorsCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

const QMetaObject Colors::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Colors.offsetsAndSize,
    qt_meta_data_Colors,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_Colors_t


, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<QRgb, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>

>,
    nullptr
} };


const QMetaObject *Colors::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Colors::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Colors.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Colors::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
