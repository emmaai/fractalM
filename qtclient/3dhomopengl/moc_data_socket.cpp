/****************************************************************************
** Meta object code from reading C++ file 'data_socket.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "data_socket.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'data_socket.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_rwSockData_t {
    QByteArrayData data[19];
    char stringdata[227];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_rwSockData_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_rwSockData_t qt_meta_stringdata_rwSockData = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 11),
QT_MOC_LITERAL(2, 23, 0),
QT_MOC_LITERAL(3, 24, 8),
QT_MOC_LITERAL(4, 33, 8),
QT_MOC_LITERAL(5, 42, 10),
QT_MOC_LITERAL(6, 53, 5),
QT_MOC_LITERAL(7, 59, 15),
QT_MOC_LITERAL(8, 75, 13),
QT_MOC_LITERAL(9, 89, 12),
QT_MOC_LITERAL(10, 102, 18),
QT_MOC_LITERAL(11, 121, 13),
QT_MOC_LITERAL(12, 135, 28),
QT_MOC_LITERAL(13, 164, 10),
QT_MOC_LITERAL(14, 175, 8),
QT_MOC_LITERAL(15, 184, 10),
QT_MOC_LITERAL(16, 195, 10),
QT_MOC_LITERAL(17, 206, 11),
QT_MOC_LITERAL(18, 218, 7)
    },
    "rwSockData\0rwSockError\0\0QString*\0"
    "finished\0imageReady\0char*\0connectedToHost\0"
    "connectToHost\0hostAddress*\0"
    "disconnectFromHost\0sendSockError\0"
    "QAbstractSocket::SocketError\0readSocket\0"
    "writeImg\0writeParam\0readServer\0"
    "socketReady\0sendCMD\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_rwSockData[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x05,
       4,    0,   82,    2, 0x05,
       5,    1,   83,    2, 0x05,
       7,    0,   86,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       8,    1,   87,    2, 0x0a,
      10,    0,   90,    2, 0x0a,
      11,    1,   91,    2, 0x0a,
      13,    0,   94,    2, 0x0a,
      14,    1,   95,    2, 0x0a,
      15,    1,   98,    2, 0x0a,
      16,    0,  101,    2, 0x0a,
      17,    0,  102,    2, 0x0a,
      18,    1,  103,    2, 0x0a,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 9,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    2,

       0        // eod
};

void rwSockData::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        rwSockData *_t = static_cast<rwSockData *>(_o);
        switch (_id) {
        case 0: _t->rwSockError((*reinterpret_cast< QString*(*)>(_a[1]))); break;
        case 1: _t->finished(); break;
        case 2: _t->imageReady((*reinterpret_cast< char*(*)>(_a[1]))); break;
        case 3: _t->connectedToHost(); break;
        case 4: _t->connectToHost((*reinterpret_cast< hostAddress*(*)>(_a[1]))); break;
        case 5: _t->disconnectFromHost(); break;
        case 6: _t->sendSockError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 7: _t->readSocket(); break;
        case 8: _t->writeImg((*reinterpret_cast< char*(*)>(_a[1]))); break;
        case 9: _t->writeParam((*reinterpret_cast< char*(*)>(_a[1]))); break;
        case 10: _t->readServer(); break;
        case 11: _t->socketReady(); break;
        case 12: _t->sendCMD((*reinterpret_cast< char*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (rwSockData::*_t)(QString * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&rwSockData::rwSockError)) {
                *result = 0;
            }
        }
        {
            typedef void (rwSockData::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&rwSockData::finished)) {
                *result = 1;
            }
        }
        {
            typedef void (rwSockData::*_t)(char * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&rwSockData::imageReady)) {
                *result = 2;
            }
        }
        {
            typedef void (rwSockData::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&rwSockData::connectedToHost)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject rwSockData::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_rwSockData.data,
      qt_meta_data_rwSockData,  qt_static_metacall, 0, 0}
};


const QMetaObject *rwSockData::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *rwSockData::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_rwSockData.stringdata))
        return static_cast<void*>(const_cast< rwSockData*>(this));
    return QObject::qt_metacast(_clname);
}

int rwSockData::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void rwSockData::rwSockError(QString * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void rwSockData::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void rwSockData::imageReady(char * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void rwSockData::connectedToHost()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}
QT_END_MOC_NAMESPACE
