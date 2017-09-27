/****************************************************************************
** Meta object code from reading C++ file 'MainWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MainWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWidget_t {
    QByteArrayData data[21];
    char stringdata0[195];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWidget_t qt_meta_stringdata_MainWidget = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWidget"
QT_MOC_LITERAL(1, 11, 6), // "zoomIn"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 7), // "zoomOut"
QT_MOC_LITERAL(4, 27, 7), // "setSnap"
QT_MOC_LITERAL(5, 35, 11), // "onSetPixmap"
QT_MOC_LITERAL(6, 47, 10), // "onSetRatio"
QT_MOC_LITERAL(7, 58, 15), // "onMouseTracking"
QT_MOC_LITERAL(8, 74, 3), // "pos"
QT_MOC_LITERAL(9, 78, 6), // "onOpen"
QT_MOC_LITERAL(10, 85, 7), // "onClose"
QT_MOC_LITERAL(11, 93, 6), // "onSave"
QT_MOC_LITERAL(12, 100, 5), // "onNew"
QT_MOC_LITERAL(13, 106, 7), // "onAbout"
QT_MOC_LITERAL(14, 114, 10), // "onViewHelp"
QT_MOC_LITERAL(15, 125, 11), // "domDocument"
QT_MOC_LITERAL(16, 137, 12), // "QDomDocument"
QT_MOC_LITERAL(17, 150, 12), // "onOpenRecent"
QT_MOC_LITERAL(18, 163, 16), // "onSetOrientation"
QT_MOC_LITERAL(19, 180, 2), // "id"
QT_MOC_LITERAL(20, 183, 11) // "onSetRation"

    },
    "MainWidget\0zoomIn\0\0zoomOut\0setSnap\0"
    "onSetPixmap\0onSetRatio\0onMouseTracking\0"
    "pos\0onOpen\0onClose\0onSave\0onNew\0onAbout\0"
    "onViewHelp\0domDocument\0QDomDocument\0"
    "onOpenRecent\0onSetOrientation\0id\0"
    "onSetRation"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x06 /* Public */,
       3,    0,   95,    2, 0x06 /* Public */,
       4,    1,   96,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   99,    2, 0x0a /* Public */,
       6,    0,  100,    2, 0x0a /* Public */,
       7,    1,  101,    2, 0x0a /* Public */,
       9,    0,  104,    2, 0x0a /* Public */,
      10,    0,  105,    2, 0x0a /* Public */,
      11,    0,  106,    2, 0x0a /* Public */,
      12,    0,  107,    2, 0x0a /* Public */,
      13,    0,  108,    2, 0x0a /* Public */,
      14,    0,  109,    2, 0x0a /* Public */,
      15,    0,  110,    2, 0x0a /* Public */,
      17,    0,  111,    2, 0x0a /* Public */,
      18,    1,  112,    2, 0x08 /* Private */,
      20,    1,  115,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    0x80000000 | 16,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void, QMetaType::Int,   19,

       0        // eod
};

void MainWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWidget *_t = static_cast<MainWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->zoomIn(); break;
        case 1: _t->zoomOut(); break;
        case 2: _t->setSnap((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->onSetPixmap(); break;
        case 4: _t->onSetRatio(); break;
        case 5: _t->onMouseTracking((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 6: _t->onOpen(); break;
        case 7: _t->onClose(); break;
        case 8: _t->onSave(); break;
        case 9: _t->onNew(); break;
        case 10: _t->onAbout(); break;
        case 11: _t->onViewHelp(); break;
        case 12: { QDomDocument _r = _t->domDocument();
            if (_a[0]) *reinterpret_cast< QDomDocument*>(_a[0]) = _r; }  break;
        case 13: _t->onOpenRecent(); break;
        case 14: _t->onSetOrientation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->onSetRation((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWidget::zoomIn)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MainWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWidget::zoomOut)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (MainWidget::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWidget::setSnap)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject MainWidget::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWidget.data,
      qt_meta_data_MainWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWidget.stringdata0))
        return static_cast<void*>(const_cast< MainWidget*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void MainWidget::zoomIn()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void MainWidget::zoomOut()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void MainWidget::setSnap(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
