/****************************************************************************
** Meta object code from reading C++ file 'RasendeRoboterController.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../RasendeRoboterController.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RasendeRoboterController.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_RasendeRoboterController_t {
    QByteArrayData data[14];
    char stringdata0[201];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RasendeRoboterController_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RasendeRoboterController_t qt_meta_stringdata_RasendeRoboterController = {
    {
QT_MOC_LITERAL(0, 0, 24), // "RasendeRoboterController"
QT_MOC_LITERAL(1, 25, 9), // "upHandler"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 11), // "downHandler"
QT_MOC_LITERAL(4, 48, 11), // "leftHandler"
QT_MOC_LITERAL(5, 60, 12), // "rightHandler"
QT_MOC_LITERAL(6, 73, 13), // "cancelHandler"
QT_MOC_LITERAL(7, 87, 12), // "startHandler"
QT_MOC_LITERAL(8, 100, 15), // "redRadioHandler"
QT_MOC_LITERAL(9, 116, 16), // "blueRadioHandler"
QT_MOC_LITERAL(10, 133, 18), // "yellowRadioHandler"
QT_MOC_LITERAL(11, 152, 17), // "greenRadioHandler"
QT_MOC_LITERAL(12, 170, 15), // "solutionHandler"
QT_MOC_LITERAL(13, 186, 14) // "annonceHandler"

    },
    "RasendeRoboterController\0upHandler\0\0"
    "downHandler\0leftHandler\0rightHandler\0"
    "cancelHandler\0startHandler\0redRadioHandler\0"
    "blueRadioHandler\0yellowRadioHandler\0"
    "greenRadioHandler\0solutionHandler\0"
    "annonceHandler"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RasendeRoboterController[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x0a /* Public */,
       3,    0,   75,    2, 0x0a /* Public */,
       4,    0,   76,    2, 0x0a /* Public */,
       5,    0,   77,    2, 0x0a /* Public */,
       6,    0,   78,    2, 0x0a /* Public */,
       7,    0,   79,    2, 0x0a /* Public */,
       8,    0,   80,    2, 0x0a /* Public */,
       9,    0,   81,    2, 0x0a /* Public */,
      10,    0,   82,    2, 0x0a /* Public */,
      11,    0,   83,    2, 0x0a /* Public */,
      12,    0,   84,    2, 0x0a /* Public */,
      13,    0,   85,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void RasendeRoboterController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RasendeRoboterController *_t = static_cast<RasendeRoboterController *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->upHandler(); break;
        case 1: _t->downHandler(); break;
        case 2: _t->leftHandler(); break;
        case 3: _t->rightHandler(); break;
        case 4: _t->cancelHandler(); break;
        case 5: _t->startHandler(); break;
        case 6: _t->redRadioHandler(); break;
        case 7: _t->blueRadioHandler(); break;
        case 8: _t->yellowRadioHandler(); break;
        case 9: _t->greenRadioHandler(); break;
        case 10: _t->solutionHandler(); break;
        case 11: _t->annonceHandler(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject RasendeRoboterController::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_RasendeRoboterController.data,
      qt_meta_data_RasendeRoboterController,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *RasendeRoboterController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RasendeRoboterController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RasendeRoboterController.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int RasendeRoboterController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
