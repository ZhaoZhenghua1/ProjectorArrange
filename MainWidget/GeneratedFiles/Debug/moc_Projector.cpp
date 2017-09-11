/****************************************************************************
** Meta object code from reading C++ file 'Projector.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Projector.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Projector.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Projector_t {
    QByteArrayData data[27];
    char stringdata0[249];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Projector_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Projector_t qt_meta_stringdata_Projector = {
    {
QT_MOC_LITERAL(0, 0, 9), // "Projector"
QT_MOC_LITERAL(1, 10, 15), // "positionToValue"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 15), // "Qt::Orientation"
QT_MOC_LITERAL(4, 43, 15), // "valueToPosition"
QT_MOC_LITERAL(5, 59, 8), // "attached"
QT_MOC_LITERAL(6, 68, 1), // "o"
QT_MOC_LITERAL(7, 70, 3), // "pos"
QT_MOC_LITERAL(8, 74, 13), // "mouseTracking"
QT_MOC_LITERAL(9, 88, 8), // "location"
QT_MOC_LITERAL(10, 97, 13), // "setSelectArea"
QT_MOC_LITERAL(11, 111, 8), // "QString&"
QT_MOC_LITERAL(12, 120, 5), // "index"
QT_MOC_LITERAL(13, 126, 7), // "QRectF&"
QT_MOC_LITERAL(14, 134, 4), // "rect"
QT_MOC_LITERAL(15, 139, 9), // "showValue"
QT_MOC_LITERAL(16, 149, 5), // "value"
QT_MOC_LITERAL(17, 155, 9), // "hideValue"
QT_MOC_LITERAL(18, 165, 8), // "limitPos"
QT_MOC_LITERAL(19, 174, 8), // "Qt::Edge"
QT_MOC_LITERAL(20, 183, 10), // "isMoveMode"
QT_MOC_LITERAL(21, 194, 11), // "dataChanged"
QT_MOC_LITERAL(22, 206, 10), // "removeData"
QT_MOC_LITERAL(23, 217, 11), // "QDomElement"
QT_MOC_LITERAL(24, 229, 4), // "data"
QT_MOC_LITERAL(25, 234, 8), // "onRotate"
QT_MOC_LITERAL(26, 243, 5) // "angle"

    },
    "Projector\0positionToValue\0\0Qt::Orientation\0"
    "valueToPosition\0attached\0o\0pos\0"
    "mouseTracking\0location\0setSelectArea\0"
    "QString&\0index\0QRectF&\0rect\0showValue\0"
    "value\0hideValue\0limitPos\0Qt::Edge\0"
    "isMoveMode\0dataChanged\0removeData\0"
    "QDomElement\0data\0onRotate\0angle"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Projector[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      11,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   79,    2, 0x06 /* Public */,
       4,    2,   84,    2, 0x06 /* Public */,
       5,    2,   89,    2, 0x06 /* Public */,
       8,    1,   94,    2, 0x06 /* Public */,
      10,    2,   97,    2, 0x06 /* Public */,
      15,    1,  102,    2, 0x06 /* Public */,
      17,    0,  105,    2, 0x06 /* Public */,
      18,    1,  106,    2, 0x06 /* Public */,
      20,    0,  109,    2, 0x06 /* Public */,
      21,    0,  110,    2, 0x06 /* Public */,
      22,    1,  111,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      24,    0,  114,    2, 0x0a /* Public */,
      25,    1,  115,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::QReal, 0x80000000 | 3, QMetaType::QReal,    2,    2,
    QMetaType::QReal, 0x80000000 | 3, QMetaType::QReal,    2,    2,
    QMetaType::QLineF, 0x80000000 | 3, QMetaType::QLineF,    6,    7,
    QMetaType::Void, QMetaType::QPointF,    9,
    QMetaType::Void, 0x80000000 | 11, 0x80000000 | 13,   12,   14,
    QMetaType::Void, QMetaType::QRectF,   16,
    QMetaType::Void,
    QMetaType::QReal, 0x80000000 | 19,    2,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 23,   24,

 // slots: parameters
    0x80000000 | 23,
    QMetaType::Void, QMetaType::QReal,   26,

       0        // eod
};

void Projector::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Projector *_t = static_cast<Projector *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { qreal _r = _t->positionToValue((*reinterpret_cast< Qt::Orientation(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< qreal*>(_a[0]) = _r; }  break;
        case 1: { qreal _r = _t->valueToPosition((*reinterpret_cast< Qt::Orientation(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< qreal*>(_a[0]) = _r; }  break;
        case 2: { QLineF _r = _t->attached((*reinterpret_cast< Qt::Orientation(*)>(_a[1])),(*reinterpret_cast< const QLineF(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QLineF*>(_a[0]) = _r; }  break;
        case 3: _t->mouseTracking((*reinterpret_cast< const QPointF(*)>(_a[1]))); break;
        case 4: _t->setSelectArea((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QRectF(*)>(_a[2]))); break;
        case 5: _t->showValue((*reinterpret_cast< const QRectF(*)>(_a[1]))); break;
        case 6: _t->hideValue(); break;
        case 7: { qreal _r = _t->limitPos((*reinterpret_cast< const Qt::Edge(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< qreal*>(_a[0]) = _r; }  break;
        case 8: { bool _r = _t->isMoveMode();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 9: _t->dataChanged(); break;
        case 10: _t->removeData((*reinterpret_cast< const QDomElement(*)>(_a[1]))); break;
        case 11: { QDomElement _r = _t->data();
            if (_a[0]) *reinterpret_cast< QDomElement*>(_a[0]) = _r; }  break;
        case 12: _t->onRotate((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef qreal (Projector::*_t)(Qt::Orientation , qreal );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Projector::positionToValue)) {
                *result = 0;
                return;
            }
        }
        {
            typedef qreal (Projector::*_t)(Qt::Orientation , qreal );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Projector::valueToPosition)) {
                *result = 1;
                return;
            }
        }
        {
            typedef QLineF (Projector::*_t)(Qt::Orientation , const QLineF & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Projector::attached)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (Projector::*_t)(const QPointF & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Projector::mouseTracking)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (Projector::*_t)(QString & , QRectF & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Projector::setSelectArea)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (Projector::*_t)(const QRectF & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Projector::showValue)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (Projector::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Projector::hideValue)) {
                *result = 6;
                return;
            }
        }
        {
            typedef qreal (Projector::*_t)(const Qt::Edge );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Projector::limitPos)) {
                *result = 7;
                return;
            }
        }
        {
            typedef bool (Projector::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Projector::isMoveMode)) {
                *result = 8;
                return;
            }
        }
        {
            typedef void (Projector::*_t)() const;
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Projector::dataChanged)) {
                *result = 9;
                return;
            }
        }
        {
            typedef void (Projector::*_t)(const QDomElement & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Projector::removeData)) {
                *result = 10;
                return;
            }
        }
    }
}

const QMetaObject Projector::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Projector.data,
      qt_meta_data_Projector,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Projector::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Projector::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Projector.stringdata0))
        return static_cast<void*>(const_cast< Projector*>(this));
    if (!strcmp(_clname, "QGraphicsRectItem"))
        return static_cast< QGraphicsRectItem*>(const_cast< Projector*>(this));
    return QObject::qt_metacast(_clname);
}

int Projector::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
qreal Projector::positionToValue(Qt::Orientation _t1, qreal _t2)
{
    qreal _t0 = qreal();
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)), const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
    return _t0;
}

// SIGNAL 1
qreal Projector::valueToPosition(Qt::Orientation _t1, qreal _t2)
{
    qreal _t0 = qreal();
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)), const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
    return _t0;
}

// SIGNAL 2
QLineF Projector::attached(Qt::Orientation _t1, const QLineF & _t2)
{
    QLineF _t0 = QLineF();
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)), const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
    return _t0;
}

// SIGNAL 3
void Projector::mouseTracking(const QPointF & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Projector::setSelectArea(QString & _t1, QRectF & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Projector::showValue(const QRectF & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Projector::hideValue()
{
    QMetaObject::activate(this, &staticMetaObject, 6, Q_NULLPTR);
}

// SIGNAL 7
qreal Projector::limitPos(const Qt::Edge _t1)
{
    qreal _t0 = qreal();
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)), const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
    return _t0;
}

// SIGNAL 8
bool Projector::isMoveMode()
{
    bool _t0 = bool();
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
    return _t0;
}

// SIGNAL 9
void Projector::dataChanged()const
{
    QMetaObject::activate(const_cast< Projector *>(this), &staticMetaObject, 9, Q_NULLPTR);
}

// SIGNAL 10
void Projector::removeData(const QDomElement & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}
QT_END_MOC_NAMESPACE
