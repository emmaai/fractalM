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
    QByteArrayData data[17];
    char stringdata[206];
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
QT_MOC_LITERAL(6, 53, 14),
QT_MOC_LITERAL(7, 68, 13),
QT_MOC_LITERAL(8, 82, 12),
QT_MOC_LITERAL(9, 95, 18),
QT_MOC_LITERAL(10, 114, 13),
QT_MOC_LITERAL(11, 128, 28),
QT_MOC_LITERAL(12, 157, 10),
QT_MOC_LITERAL(13, 168, 8),
QT_MOC_LITERAL(14, 177, 10),
QT_MOC_LITERAL(15, 188, 5),
QT_MOC_LITERAL(16, 194, 10)
    },
    "rwSockData\0rwSockError\0\0QString*\0"
    "finished\0imageReady\0unsigned char*\0"
    "connectToHost\0hostAddress*\0"
    "disconnectFromHost\0sendSockError\0"
    "QAbstractSocket::SocketError\0readSocket\0"
    "writeImg\0writeParam\0char*\0readServer\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_rwSockData[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x05,
       4,    0,   67,    2, 0x05,
       5,    1,   68,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       7,    1,   71,    2, 0x0a,
       9,    0,   74,    2, 0x0a,
      10,    1,   75,    2, 0x0a,
      12,    0,   78,    2, 0x0a,
      13,    1,   79,    2, 0x0a,
      14,    1,   82,    2, 0x0a,
      16,    0,   85,    2, 0x0a,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 8,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void, 0x80000000 | 15,    2,
    QMetaType::Void,

       0        // eod
};

void rwSockData::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        rwSockData *_t = static_cast<rwSockData *>(_o);
        switch (_id) {
        case 0: _t->rwSockError((*reinterpret_cast< QString*(*)>(_a[1]))); break;
        case 1: _t->finished(); break;
        case 2: _t->imageReady((*reinterpret_cast< unsigned char*(*)>(_a[1]))); break;
        case 3: _t->connectToHost((*reinterpret_cast< hostAddress*(*)>(_a[1]))); break;
        case 4: _t->disconnectFromHost(); break;
        case 5: _t->sendSockError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 6: _t->readSocket(); break;
        case 7: _t->writeImg((*reinterpret_cast< unsigned char*(*)>(_a[1]))); break;
        case 8: _t->writeParam((*reinterpret_cast< char*(*)>(_a[1]))); break;
        case 9: _t->readServer(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
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
            typedef void (rwSockData::*_t)(unsigned char * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&rwSockData::imageReady)) {
                *result = 2;
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
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
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
void rwSockData::imageReady(unsigned char * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
