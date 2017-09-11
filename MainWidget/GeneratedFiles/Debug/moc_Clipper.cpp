/****************************************************************************
** Meta object code from reading C++ file 'Clipper.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Clipper.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Clipper.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_RootWidget_t {
    QByteArrayData data[23];
    char stringdata0[244];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RootWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RootWidget_t qt_meta_stringdata_RootWidget = {
    {
QT_MOC_LITERAL(0, 0, 10), // "RootWidget"
QT_MOC_LITERAL(1, 11, 13), // "mouseTracking"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 8), // "location"
QT_MOC_LITERAL(4, 35, 11), // "setBarValue"
QT_MOC_LITERAL(5, 47, 15), // "Qt::Orientation"
QT_MOC_LITERAL(6, 63, 6), // "qreal&"
QT_MOC_LITERAL(7, 70, 13), // "setSelectArea"
QT_MOC_LITERAL(8, 84, 8), // "QString&"
QT_MOC_LITERAL(9, 93, 5), // "index"
QT_MOC_LITERAL(10, 99, 7), // "QRectF&"
QT_MOC_LITERAL(11, 107, 4), // "rect"
QT_MOC_LITERAL(12, 112, 20), // "selectionAreaCreated"
QT_MOC_LITERAL(13, 133, 10), // "Projector*"
QT_MOC_LITERAL(14, 144, 11), // "domDocument"
QT_MOC_LITERAL(15, 156, 12), // "QDomDocument"
QT_MOC_LITERAL(16, 169, 15), // "valueToPosition"
QT_MOC_LITERAL(17, 185, 1), // "o"
QT_MOC_LITERAL(18, 187, 5), // "value"
QT_MOC_LITERAL(19, 193, 15), // "positionToValue"
QT_MOC_LITERAL(20, 209, 7), // "postion"
QT_MOC_LITERAL(21, 217, 15), // "onMouseTracking"
QT_MOC_LITERAL(22, 233, 10) // "ratioValue"

    },
    "RootWidget\0mouseTracking\0\0location\0"
    "setBarValue\0Qt::Orientation\0qreal&\0"
    "setSelectArea\0QString&\0index\0QRectF&\0"
    "rect\0selectionAreaCreated\0Projector*\0"
    "domDocument\0QDomDocument\0valueToPosition\0"
    "o\0value\0positionToValue\0postion\0"
    "onMouseTracking\0ratioValue"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RootWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       4,    2,   62,    2, 0x06 /* Public */,
       7,    2,   67,    2, 0x06 /* Public */,
      12,    1,   72,    2, 0x06 /* Public */,
      14,    0,   75,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      16,    2,   76,    2, 0x0a /* Public */,
      19,    2,   81,    2, 0x0a /* Public */,
      21,    1,   86,    2, 0x0a /* Public */,
      22,    2,   89,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QPoint,    3,
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 6,    2,    2,
    QMetaType::Void, 0x80000000 | 8, 0x80000000 | 10,    9,   11,
    QMetaType::Void, 0x80000000 | 13,    2,
    0x80000000 | 15,

 // slots: parameters
    QMetaType::QReal, 0x80000000 | 5, QMetaType::QReal,   17,   18,
    QMetaType::QReal, 0x80000000 | 5, QMetaType::QReal,   17,   20,
    QMetaType::Void, QMetaType::QPointF,    3,
    QMetaType::Int, 0x80000000 | 5, QMetaType::QReal,   17,    2,

       0        // eod
};

void RootWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RootWidget *_t = static_cast<RootWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->mouseTracking((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 1: _t->setBarValue((*reinterpret_cast< Qt::Orientation(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2]))); break;
        case 2: _t->setSelectArea((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QRectF(*)>(_a[2]))); break;
        case 3: _t->selectionAreaCreated((*reinterpret_cast< Projector*(*)>(_a[1]))); break;
        case 4: { QDomDocument _r = _t->domDocument();
            if (_a[0]) *reinterpret_cast< QDomDocument*>(_a[0]) = _r; }  break;
        case 5: { qreal _r = _t->valueToPosition((*reinterpret_cast< Qt::Orientation(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< qreal*>(_a[0]) = _r; }  break;
        case 6: { qreal _r = _t->positionToValue((*reinterpret_cast< Qt::Orientation(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< qreal*>(_a[0]) = _r; }  break;
        case 7: _t->onMouseTracking((*reinterpret_cast< const QPointF(*)>(_a[1]))); break;
        case 8: { int _r = _t->ratioValue((*reinterpret_cast< Qt::Orientation(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (RootWidget::*_t)(const QPoint & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RootWidget::mouseTracking)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (RootWidget::*_t)(Qt::Orientation , qreal & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RootWidget::setBarValue)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (RootWidget::*_t)(QString & , QRectF & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RootWidget::setSelectArea)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (RootWidget::*_t)(Projector * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RootWidget::selectionAreaCreated)) {
                *result = 3;
                return;
            }
        }
        {
            typedef QDomDocument (RootWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RootWidget::domDocument)) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject RootWidget::staticMetaObject = {
    { &QGraphicsWidget::staticMetaObject, qt_meta_stringdata_RootWidget.data,
      qt_meta_data_RootWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *RootWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RootWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_RootWidget.stringdata0))
        return static_cast<void*>(const_cast< RootWidget*>(this));
    return QGraphicsWidget::qt_metacast(_clname);
}

int RootWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void RootWidget::mouseTracking(const QPoint & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void RootWidget::setBarValue(Qt::Orientation _t1, qreal & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void RootWidget::setSelectArea(QString & _t1, QRectF & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void RootWidget::selectionAreaCreated(Projector * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
QDomDocument RootWidget::domDocument()
{
    QDomDocument _t0 = QDomDocument();
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
    return _t0;
}
struct qt_meta_stringdata_Clipper_t {
    QByteArrayData data[27];
    char stringdata0[280];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Clipper_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Clipper_t qt_meta_stringdata_Clipper = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Clipper"
QT_MOC_LITERAL(1, 8, 13), // "mouseTracking"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 8), // "location"
QT_MOC_LITERAL(4, 32, 20), // "selectionAreaCreated"
QT_MOC_LITERAL(5, 53, 10), // "Projector*"
QT_MOC_LITERAL(6, 64, 12), // "isIndexValid"
QT_MOC_LITERAL(7, 77, 5), // "index"
QT_MOC_LITERAL(8, 83, 11), // "domDocument"
QT_MOC_LITERAL(9, 95, 12), // "QDomDocument"
QT_MOC_LITERAL(10, 108, 15), // "currentItemData"
QT_MOC_LITERAL(11, 124, 11), // "QDomElement"
QT_MOC_LITERAL(12, 136, 21), // "currentItemDataEdited"
QT_MOC_LITERAL(13, 158, 11), // "dataChanged"
QT_MOC_LITERAL(14, 170, 5), // "ratio"
QT_MOC_LITERAL(15, 176, 6), // "setBar"
QT_MOC_LITERAL(16, 183, 15), // "Qt::Orientation"
QT_MOC_LITERAL(17, 199, 1), // "o"
QT_MOC_LITERAL(18, 201, 6), // "qreal&"
QT_MOC_LITERAL(19, 208, 8), // "valueRet"
QT_MOC_LITERAL(20, 217, 13), // "setSelectArea"
QT_MOC_LITERAL(21, 231, 8), // "QString&"
QT_MOC_LITERAL(22, 240, 8), // "indexRet"
QT_MOC_LITERAL(23, 249, 7), // "QRectF&"
QT_MOC_LITERAL(24, 257, 7), // "rectRet"
QT_MOC_LITERAL(25, 265, 6), // "zoomIn"
QT_MOC_LITERAL(26, 272, 7) // "zoomOut"

    },
    "Clipper\0mouseTracking\0\0location\0"
    "selectionAreaCreated\0Projector*\0"
    "isIndexValid\0index\0domDocument\0"
    "QDomDocument\0currentItemData\0QDomElement\0"
    "currentItemDataEdited\0dataChanged\0"
    "ratio\0setBar\0Qt::Orientation\0o\0qreal&\0"
    "valueRet\0setSelectArea\0QString&\0"
    "indexRet\0QRectF&\0rectRet\0zoomIn\0zoomOut"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Clipper[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,
       4,    1,   77,    2, 0x06 /* Public */,
       6,    1,   80,    2, 0x06 /* Public */,
       8,    0,   83,    2, 0x06 /* Public */,
      10,    0,   84,    2, 0x06 /* Public */,
      12,    0,   85,    2, 0x06 /* Public */,
      13,    0,   86,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      14,    0,   87,    2, 0x0a /* Public */,
      15,    2,   88,    2, 0x0a /* Public */,
      20,    2,   93,    2, 0x0a /* Public */,
      25,    0,   98,    2, 0x0a /* Public */,
      26,    0,   99,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QPoint,    3,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Bool, QMetaType::QString,    7,
    0x80000000 | 9,
    0x80000000 | 11,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::QSize,
    QMetaType::Void, 0x80000000 | 16, 0x80000000 | 18,   17,   19,
    QMetaType::Void, 0x80000000 | 21, 0x80000000 | 23,   22,   24,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Clipper::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Clipper *_t = static_cast<Clipper *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->mouseTracking((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 1: _t->selectionAreaCreated((*reinterpret_cast< Projector*(*)>(_a[1]))); break;
        case 2: { bool _r = _t->isIndexValid((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: { QDomDocument _r = _t->domDocument();
            if (_a[0]) *reinterpret_cast< QDomDocument*>(_a[0]) = _r; }  break;
        case 4: { QDomElement _r = _t->currentItemData();
            if (_a[0]) *reinterpret_cast< QDomElement*>(_a[0]) = _r; }  break;
        case 5: _t->currentItemDataEdited(); break;
        case 6: _t->dataChanged(); break;
        case 7: { QSize _r = _t->ratio();
            if (_a[0]) *reinterpret_cast< QSize*>(_a[0]) = _r; }  break;
        case 8: _t->setBar((*reinterpret_cast< Qt::Orientation(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2]))); break;
        case 9: _t->setSelectArea((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QRectF(*)>(_a[2]))); break;
        case 10: _t->zoomIn(); break;
        case 11: _t->zoomOut(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Clipper::*_t)(const QPoint & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Clipper::mouseTracking)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Clipper::*_t)(Projector * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Clipper::selectionAreaCreated)) {
                *result = 1;
                return;
            }
        }
        {
            typedef bool (Clipper::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Clipper::isIndexValid)) {
                *result = 2;
                return;
            }
        }
        {
            typedef QDomDocument (Clipper::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Clipper::domDocument)) {
                *result = 3;
                return;
            }
        }
        {
            typedef QDomElement (Clipper::*_t)() const;
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Clipper::currentItemData)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (Clipper::*_t)() const;
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Clipper::currentItemDataEdited)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (Clipper::*_t)() const;
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Clipper::dataChanged)) {
                *result = 6;
                return;
            }
        }
    }
}

const QMetaObject Clipper::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_Clipper.data,
      qt_meta_data_Clipper,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Clipper::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Clipper::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Clipper.stringdata0))
        return static_cast<void*>(const_cast< Clipper*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int Clipper::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void Clipper::mouseTracking(const QPoint & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Clipper::selectionAreaCreated(Projector * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
bool Clipper::isIndexValid(const QString & _t1)
{
    bool _t0 = bool();
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)), const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
    return _t0;
}

// SIGNAL 3
QDomDocument Clipper::domDocument()
{
    QDomDocument _t0 = QDomDocument();
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
    return _t0;
}

// SIGNAL 4
QDomElement Clipper::currentItemData()const
{
    QDomElement _t0 = QDomElement();
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)) };
    QMetaObject::activate(const_cast< Clipper *>(this), &staticMetaObject, 4, _a);
    return _t0;
}

// SIGNAL 5
void Clipper::currentItemDataEdited()const
{
    QMetaObject::activate(const_cast< Clipper *>(this), &staticMetaObject, 5, Q_NULLPTR);
}

// SIGNAL 6
void Clipper::dataChanged()const
{
    QMetaObject::activate(const_cast< Clipper *>(this), &staticMetaObject, 6, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
