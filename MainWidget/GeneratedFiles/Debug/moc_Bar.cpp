/****************************************************************************
** Meta object code from reading C++ file 'Bar.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Bar.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Bar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Bar_t {
    QByteArrayData data[18];
    char stringdata0[174];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Bar_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Bar_t qt_meta_stringdata_Bar = {
    {
QT_MOC_LITERAL(0, 0, 3), // "Bar"
QT_MOC_LITERAL(1, 4, 15), // "positionToValue"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 15), // "Qt::Orientation"
QT_MOC_LITERAL(4, 37, 15), // "valueToPosition"
QT_MOC_LITERAL(5, 53, 8), // "attached"
QT_MOC_LITERAL(6, 62, 3), // "pos"
QT_MOC_LITERAL(7, 66, 13), // "mouseTracking"
QT_MOC_LITERAL(8, 80, 8), // "location"
QT_MOC_LITERAL(9, 89, 11), // "setBarValue"
QT_MOC_LITERAL(10, 101, 6), // "qreal&"
QT_MOC_LITERAL(11, 108, 9), // "showValue"
QT_MOC_LITERAL(12, 118, 9), // "hideValue"
QT_MOC_LITERAL(13, 128, 8), // "limitPos"
QT_MOC_LITERAL(14, 137, 8), // "Qt::Edge"
QT_MOC_LITERAL(15, 146, 10), // "removeData"
QT_MOC_LITERAL(16, 157, 11), // "QDomElement"
QT_MOC_LITERAL(17, 169, 4) // "data"

    },
    "Bar\0positionToValue\0\0Qt::Orientation\0"
    "valueToPosition\0attached\0pos\0mouseTracking\0"
    "location\0setBarValue\0qreal&\0showValue\0"
    "hideValue\0limitPos\0Qt::Edge\0removeData\0"
    "QDomElement\0data"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Bar[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   59,    2, 0x06 /* Public */,
       4,    2,   64,    2, 0x06 /* Public */,
       5,    1,   69,    2, 0x06 /* Public */,
       7,    1,   72,    2, 0x06 /* Public */,
       9,    2,   75,    2, 0x06 /* Public */,
      11,    2,   80,    2, 0x06 /* Public */,
      12,    0,   85,    2, 0x06 /* Public */,
      13,    1,   86,    2, 0x06 /* Public */,
      15,    1,   89,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::QReal, 0x80000000 | 3, QMetaType::QReal,    2,    2,
    QMetaType::QReal, 0x80000000 | 3, QMetaType::QReal,    2,    2,
    QMetaType::QLineF, QMetaType::QLineF,    6,
    QMetaType::Void, QMetaType::QPointF,    8,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 10,    2,    2,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QReal,    2,    2,
    QMetaType::Void,
    QMetaType::QReal, 0x80000000 | 14,    2,
    QMetaType::Void, 0x80000000 | 16,   17,

       0        // eod
};

void Bar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Bar *_t = static_cast<Bar *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { qreal _r = _t->positionToValue((*reinterpret_cast< Qt::Orientation(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< qreal*>(_a[0]) = _r; }  break;
        case 1: { qreal _r = _t->valueToPosition((*reinterpret_cast< Qt::Orientation(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< qreal*>(_a[0]) = _r; }  break;
        case 2: { QLineF _r = _t->attached((*reinterpret_cast< const QLineF(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QLineF*>(_a[0]) = _r; }  break;
        case 3: _t->mouseTracking((*reinterpret_cast< const QPointF(*)>(_a[1]))); break;
        case 4: _t->setBarValue((*reinterpret_cast< Qt::Orientation(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2]))); break;
        case 5: _t->showValue((*reinterpret_cast< Qt::Orientation(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2]))); break;
        case 6: _t->hideValue(); break;
        case 7: { qreal _r = _t->limitPos((*reinterpret_cast< const Qt::Edge(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< qreal*>(_a[0]) = _r; }  break;
        case 8: _t->removeData((*reinterpret_cast< const QDomElement(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef qreal (Bar::*_t)(Qt::Orientation , qreal );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Bar::positionToValue)) {
                *result = 0;
                return;
            }
        }
        {
            typedef qreal (Bar::*_t)(Qt::Orientation , qreal );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Bar::valueToPosition)) {
                *result = 1;
                return;
            }
        }
        {
            typedef QLineF (Bar::*_t)(const QLineF & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Bar::attached)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (Bar::*_t)(const QPointF & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Bar::mouseTracking)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (Bar::*_t)(Qt::Orientation , qreal & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Bar::setBarValue)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (Bar::*_t)(Qt::Orientation , qreal );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Bar::showValue)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (Bar::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Bar::hideValue)) {
                *result = 6;
                return;
            }
        }
        {
            typedef qreal (Bar::*_t)(const Qt::Edge );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Bar::limitPos)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (Bar::*_t)(const QDomElement & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Bar::removeData)) {
                *result = 8;
                return;
            }
        }
    }
}

const QMetaObject Bar::staticMetaObject = {
    { &QGraphicsWidget::staticMetaObject, qt_meta_stringdata_Bar.data,
      qt_meta_data_Bar,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Bar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Bar::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Bar.stringdata0))
        return static_cast<void*>(const_cast< Bar*>(this));
    return QGraphicsWidget::qt_metacast(_clname);
}

int Bar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
qreal Bar::positionToValue(Qt::Orientation _t1, qreal _t2)
{
    qreal _t0 = qreal();
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)), const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
    return _t0;
}

// SIGNAL 1
qreal Bar::valueToPosition(Qt::Orientation _t1, qreal _t2)
{
    qreal _t0 = qreal();
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)), const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
    return _t0;
}

// SIGNAL 2
QLineF Bar::attached(const QLineF & _t1)
{
    QLineF _t0 = QLineF();
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)), const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
    return _t0;
}

// SIGNAL 3
void Bar::mouseTracking(const QPointF & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Bar::setBarValue(Qt::Orientation _t1, qreal & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Bar::showValue(Qt::Orientation _t1, qreal _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Bar::hideValue()
{
    QMetaObject::activate(this, &staticMetaObject, 6, Q_NULLPTR);
}

// SIGNAL 7
qreal Bar::limitPos(const Qt::Edge _t1)
{
    qreal _t0 = qreal();
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)), const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
    return _t0;
}

// SIGNAL 8
void Bar::removeData(const QDomElement & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}
QT_END_MOC_NAMESPACE
