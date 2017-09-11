/****************************************************************************
** Meta object code from reading C++ file 'ItemModel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../TableView/ItemModel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ItemModel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ItemModel_t {
    QByteArrayData data[11];
    char stringdata0[121];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ItemModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ItemModel_t qt_meta_stringdata_ItemModel = {
    {
QT_MOC_LITERAL(0, 0, 9), // "ItemModel"
QT_MOC_LITERAL(1, 10, 15), // "currentItemData"
QT_MOC_LITERAL(2, 26, 11), // "QDomElement"
QT_MOC_LITERAL(3, 38, 0), // ""
QT_MOC_LITERAL(4, 39, 21), // "currentItemDataEdited"
QT_MOC_LITERAL(5, 61, 11), // "dataChanged"
QT_MOC_LITERAL(6, 73, 8), // "getValue"
QT_MOC_LITERAL(7, 82, 12), // "QScriptValue"
QT_MOC_LITERAL(8, 95, 10), // "expression"
QT_MOC_LITERAL(9, 106, 8), // "setValue"
QT_MOC_LITERAL(10, 115, 5) // "value"

    },
    "ItemModel\0currentItemData\0QDomElement\0"
    "\0currentItemDataEdited\0dataChanged\0"
    "getValue\0QScriptValue\0expression\0"
    "setValue\0value"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ItemModel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    3, 0x06 /* Public */,
       4,    0,   40,    3, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   41,    3, 0x0a /* Public */,
       6,    1,   42,    3, 0x0a /* Public */,
       9,    2,   45,    3, 0x0a /* Public */,

 // signals: parameters
    0x80000000 | 2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::QString, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 7, QMetaType::QString,    8,   10,

       0        // eod
};

void ItemModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ItemModel *_t = static_cast<ItemModel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { QDomElement _r = _t->currentItemData();
            if (_a[0]) *reinterpret_cast< QDomElement*>(_a[0]) = _r; }  break;
        case 1: _t->currentItemDataEdited(); break;
        case 2: _t->dataChanged(); break;
        case 3: { QString _r = _t->getValue((*reinterpret_cast< const QScriptValue(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 4: _t->setValue((*reinterpret_cast< const QScriptValue(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef QDomElement (ItemModel::*_t)() const;
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ItemModel::currentItemData)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ItemModel::*_t)() const;
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ItemModel::currentItemDataEdited)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject ItemModel::staticMetaObject = {
    { &QAbstractItemModel::staticMetaObject, qt_meta_stringdata_ItemModel.data,
      qt_meta_data_ItemModel,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ItemModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ItemModel::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ItemModel.stringdata0))
        return static_cast<void*>(const_cast< ItemModel*>(this));
    return QAbstractItemModel::qt_metacast(_clname);
}

int ItemModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractItemModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
QDomElement ItemModel::currentItemData()const
{
    QDomElement _t0 = QDomElement();
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)) };
    QMetaObject::activate(const_cast< ItemModel *>(this), &staticMetaObject, 0, _a);
    return _t0;
}

// SIGNAL 1
void ItemModel::currentItemDataEdited()const
{
    QMetaObject::activate(const_cast< ItemModel *>(this), &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
