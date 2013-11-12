/****************************************************************************
** Meta object code from reading C++ file 'mainwindow3d.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow3d.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow3d.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow3D_t {
    QByteArrayData data[17];
    char stringdata[191];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_MainWindow3D_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_MainWindow3D_t qt_meta_stringdata_MainWindow3D = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 13),
QT_MOC_LITERAL(2, 27, 0),
QT_MOC_LITERAL(3, 28, 12),
QT_MOC_LITERAL(4, 41, 16),
QT_MOC_LITERAL(5, 58, 9),
QT_MOC_LITERAL(6, 68, 14),
QT_MOC_LITERAL(7, 83, 7),
QT_MOC_LITERAL(8, 91, 5),
QT_MOC_LITERAL(9, 97, 4),
QT_MOC_LITERAL(10, 102, 10),
QT_MOC_LITERAL(11, 113, 12),
QT_MOC_LITERAL(12, 126, 8),
QT_MOC_LITERAL(13, 135, 13),
QT_MOC_LITERAL(14, 149, 18),
QT_MOC_LITERAL(15, 168, 10),
QT_MOC_LITERAL(16, 179, 10)
    },
    "MainWindow3D\0invokeConnect\0\0hostAddress*\0"
    "invokeDisconnect\0writeData\0unsigned char*\0"
    "sendCMD\0char*\0open\0netsetting\0"
    "displayError\0QString*\0connectToHost\0"
    "disconnectFromHost\0loadVolume\0generateHR\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow3D[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x05,
       4,    0,   72,    2, 0x05,
       5,    1,   73,    2, 0x05,
       7,    1,   76,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       9,    0,   79,    2, 0x0a,
      10,    0,   80,    2, 0x0a,
      11,    1,   81,    2, 0x0a,
      13,    0,   84,    2, 0x0a,
      14,    0,   85,    2, 0x0a,
      15,    1,   86,    2, 0x0a,
      16,    0,   89,    2, 0x0a,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void, 0x80000000 | 8,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    2,
    QMetaType::Void,

       0        // eod
};

void MainWindow3D::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow3D *_t = static_cast<MainWindow3D *>(_o);
        switch (_id) {
        case 0: _t->invokeConnect((*reinterpret_cast< hostAddress*(*)>(_a[1]))); break;
        case 1: _t->invokeDisconnect(); break;
        case 2: _t->writeData((*reinterpret_cast< unsigned char*(*)>(_a[1]))); break;
        case 3: _t->sendCMD((*reinterpret_cast< char*(*)>(_a[1]))); break;
        case 4: _t->open(); break;
        case 5: _t->netsetting(); break;
        case 6: _t->displayError((*reinterpret_cast< QString*(*)>(_a[1]))); break;
        case 7: _t->connectToHost(); break;
        case 8: _t->disconnectFromHost(); break;
        case 9: _t->loadVolume((*reinterpret_cast< char*(*)>(_a[1]))); break;
        case 10: _t->generateHR(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainWindow3D::*_t)(hostAddress * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow3D::invokeConnect)) {
                *result = 0;
            }
        }
        {
            typedef void (MainWindow3D::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow3D::invokeDisconnect)) {
                *result = 1;
            }
        }
        {
            typedef void (MainWindow3D::*_t)(unsigned char * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow3D::writeData)) {
                *result = 2;
            }
        }
        {
            typedef void (MainWindow3D::*_t)(char * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow3D::sendCMD)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject MainWindow3D::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow3D.data,
      qt_meta_data_MainWindow3D,  qt_static_metacall, 0, 0}
};


const QMetaObject *MainWindow3D::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow3D::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow3D.stringdata))
        return static_cast<void*>(const_cast< MainWindow3D*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow3D::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void MainWindow3D::invokeConnect(hostAddress * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow3D::invokeDisconnect()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void MainWindow3D::writeData(unsigned char * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MainWindow3D::sendCMD(char * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
