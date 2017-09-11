/****************************************************************************
** Meta object code from reading C++ file 'Ruler.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Ruler.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Ruler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Ruler_t {
    QByteArrayData data[9];
    char stringdata0[68];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Ruler_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Ruler_t qt_meta_stringdata_Ruler = {
    {
QT_MOC_LITERAL(0, 0, 5), // "Ruler"
QT_MOC_LITERAL(1, 6, 9), // "createBar"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 15), // "Qt::Orientation"
QT_MOC_LITERAL(4, 33, 1), // "o"
QT_MOC_LITERAL(5, 35, 3), // "pos"
QT_MOC_LITERAL(6, 39, 10), // "pixToRuler"
QT_MOC_LITERAL(7, 50, 6), // "timeMS"
QT_MOC_LITERAL(8, 57, 10) // "rulerToPix"

    },
    "Ruler\0createBar\0\0Qt::Orientation\0o\0"
    "pos\0pixToRuler\0timeMS\0rulerToPix"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Ruler[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   34,    2, 0x0a /* Public */,
       8,    1,   37,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QPointF,    4,    5,

 // slots: parameters
    QMetaType::QReal, QMetaType::QReal,    7,
    QMetaType::QReal, QMetaType::QReal,    5,

       0        // eod
};

void Ruler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Ruler *_t = static_cast<Ruler *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->createBar((*reinterpret_cast< Qt::Orientation(*)>(_a[1])),(*reinterpret_cast< const QPointF(*)>(_a[2]))); break;
        case 1: { qreal _r = _t->pixToRuler((*reinterpret_cast< qreal(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< qreal*>(_a[0]) = _r; }  break;
        case 2: { qreal _r = _t->rulerToPix((*reinterpret_cast< qreal(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< qreal*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Ruler::*_t)(Qt::Orientation , const QPointF & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Ruler::createBar)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject Ruler::staticMetaObject = {
    { &QGraphicsWidget::staticMetaObject, qt_meta_stringdata_Ruler.data,
      qt_meta_data_Ruler,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Ruler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Ruler::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Ruler.stringdata0))
        return static_cast<void*>(const_cast< Ruler*>(this));
    return QGraphicsWidget::qt_metacast(_clname);
}

int Ruler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void Ruler::createBar(Qt::Orientation _t1, const QPointF & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
