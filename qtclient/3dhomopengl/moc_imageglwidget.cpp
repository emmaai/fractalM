/****************************************************************************
** Meta object code from reading C++ file 'imageglwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "imageglwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'imageglwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_imageGLWidget_t {
    QByteArrayData data[19];
    char stringdata[208];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_imageGLWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_imageGLWidget_t qt_meta_stringdata_imageGLWidget = {
    {
QT_MOC_LITERAL(0, 0, 13),
QT_MOC_LITERAL(1, 14, 16),
QT_MOC_LITERAL(2, 31, 0),
QT_MOC_LITERAL(3, 32, 5),
QT_MOC_LITERAL(4, 38, 16),
QT_MOC_LITERAL(5, 55, 16),
QT_MOC_LITERAL(6, 72, 10),
QT_MOC_LITERAL(7, 83, 5),
QT_MOC_LITERAL(8, 89, 10),
QT_MOC_LITERAL(9, 100, 12),
QT_MOC_LITERAL(10, 113, 12),
QT_MOC_LITERAL(11, 126, 12),
QT_MOC_LITERAL(12, 139, 10),
QT_MOC_LITERAL(13, 150, 5),
QT_MOC_LITERAL(14, 156, 10),
QT_MOC_LITERAL(15, 167, 10),
QT_MOC_LITERAL(16, 178, 9),
QT_MOC_LITERAL(17, 188, 8),
QT_MOC_LITERAL(18, 197, 9)
    },
    "imageGLWidget\0xRotationChanged\0\0angle\0"
    "yRotationChanged\0zRotationChanged\0"
    "writeParam\0char*\0writeImage\0setXRotation\0"
    "setYRotation\0setZRotation\0setXTParam\0"
    "value\0setYTParam\0setZTParam\0setPParam\0"
    "getImage\0writeData\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_imageGLWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x05,
       4,    1,   87,    2, 0x05,
       5,    1,   90,    2, 0x05,
       6,    1,   93,    2, 0x05,
       8,    1,   96,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       9,    1,   99,    2, 0x0a,
      10,    1,  102,    2, 0x0a,
      11,    1,  105,    2, 0x0a,
      12,    1,  108,    2, 0x0a,
      14,    1,  111,    2, 0x0a,
      15,    1,  114,    2, 0x0a,
      16,    1,  117,    2, 0x0a,
      17,    1,  120,    2, 0x0a,
      18,    0,  123,    2, 0x0a,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void, 0x80000000 | 7,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void,

       0        // eod
};

void imageGLWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        imageGLWidget *_t = static_cast<imageGLWidget *>(_o);
        switch (_id) {
        case 0: _t->xRotationChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->yRotationChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->zRotationChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->writeParam((*reinterpret_cast< char*(*)>(_a[1]))); break;
        case 4: _t->writeImage((*reinterpret_cast< char*(*)>(_a[1]))); break;
        case 5: _t->setXRotation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->setYRotation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->setZRotation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->setXTParam((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->setYTParam((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->setZTParam((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->setPParam((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->getImage((*reinterpret_cast< char*(*)>(_a[1]))); break;
        case 13: _t->writeData(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (imageGLWidget::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&imageGLWidget::xRotationChanged)) {
                *result = 0;
            }
        }
        {
            typedef void (imageGLWidget::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&imageGLWidget::yRotationChanged)) {
                *result = 1;
            }
        }
        {
            typedef void (imageGLWidget::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&imageGLWidget::zRotationChanged)) {
                *result = 2;
            }
        }
        {
            typedef void (imageGLWidget::*_t)(char * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&imageGLWidget::writeParam)) {
                *result = 3;
            }
        }
        {
            typedef void (imageGLWidget::*_t)(char * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&imageGLWidget::writeImage)) {
                *result = 4;
            }
        }
    }
}

const QMetaObject imageGLWidget::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_imageGLWidget.data,
      qt_meta_data_imageGLWidget,  qt_static_metacall, 0, 0}
};


const QMetaObject *imageGLWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *imageGLWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_imageGLWidget.stringdata))
        return static_cast<void*>(const_cast< imageGLWidget*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int imageGLWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void imageGLWidget::xRotationChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void imageGLWidget::yRotationChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void imageGLWidget::zRotationChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void imageGLWidget::writeParam(char * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void imageGLWidget::writeImage(char * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
