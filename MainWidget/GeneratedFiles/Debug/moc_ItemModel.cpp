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
    QByteArrayData data[12];
    char stringdata0[129];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ItemModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ItemModel_t qt_meta_stringdata_ItemModel = {
    {
QT_MOC_LITERAL(0, 0, 9), // "ItemModel"
QT_MOC_LITERAL(1, 10, 21), // "currentItemDataEdited"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 11), // "dataChanged"
QT_MOC_LITERAL(4, 45, 18), // "setCurrentItemData"
QT_MOC_LITERAL(5, 64, 11), // "QDomElement"
QT_MOC_LITERAL(6, 76, 4), // "data"
QT_MOC_LITERAL(7, 81, 8), // "getValue"
QT_MOC_LITERAL(8, 90, 12), // "QScriptValue"
QT_MOC_LITERAL(9, 103, 10), // "expression"
QT_MOC_LITERAL(10, 114, 8), // "setValue"
QT_MOC_LITERAL(11, 123, 5) // "value"

    },
    "ItemModel\0currentItemDataEdited\0\0"
    "dataChanged\0setCurrentItemData\0"
    "QDomElement\0data\0getValue\0QScriptValue\0"
    "expression\0setValue\0value"
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
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   40,    2, 0x0a /* Public */,
       4,    1,   41,    2, 0x0a /* Public */,
       7,    1,   44,    2, 0x0a /* Public */,
      10,    2,   47,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::QString, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 8, QMetaType::QString,    9,   11,

       0        // eod
};

void ItemModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ItemModel *_t = static_cast<ItemModel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->currentItemDataEdited(); break;
        case 1: _t->dataChanged(); break;
        case 2: _t->setCurrentItemData((*reinterpret_cast< const QDomElement(*)>(_a[1]))); break;
        case 3: { QString _r = _t->getValue((*reinterpret_cast< const QScriptValue(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 4: _t->setValue((*reinterpret_cast< const QScriptValue(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ItemModel::*_t)() const;
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ItemModel::currentItemDataEdited)) {
                *result = 0;
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
void ItemModel::currentItemDataEdited()const
{
    QMetaObject::activate(const_cast< ItemModel *>(this), &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
