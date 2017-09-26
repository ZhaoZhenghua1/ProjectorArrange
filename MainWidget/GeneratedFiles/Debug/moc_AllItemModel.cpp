/****************************************************************************
** Meta object code from reading C++ file 'AllItemModel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../TableView/AllItemModel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AllItemModel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_AllItemModel_t {
    QByteArrayData data[9];
    char stringdata0[92];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AllItemModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AllItemModel_t qt_meta_stringdata_AllItemModel = {
    {
QT_MOC_LITERAL(0, 0, 12), // "AllItemModel"
QT_MOC_LITERAL(1, 13, 17), // "allItemDataEdited"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 11), // "dataChanged"
QT_MOC_LITERAL(4, 44, 8), // "getValue"
QT_MOC_LITERAL(5, 53, 12), // "QScriptValue"
QT_MOC_LITERAL(6, 66, 10), // "expression"
QT_MOC_LITERAL(7, 77, 8), // "setValue"
QT_MOC_LITERAL(8, 86, 5) // "value"

    },
    "AllItemModel\0allItemDataEdited\0\0"
    "dataChanged\0getValue\0QScriptValue\0"
    "expression\0setValue\0value"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AllItemModel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   35,    2, 0x0a /* Public */,
       4,    1,   36,    2, 0x0a /* Public */,
       7,    2,   39,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::QString, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 5, QMetaType::QString,    6,    8,

       0        // eod
};

void AllItemModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AllItemModel *_t = static_cast<AllItemModel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->allItemDataEdited(); break;
        case 1: _t->dataChanged(); break;
        case 2: { QString _r = _t->getValue((*reinterpret_cast< const QScriptValue(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 3: _t->setValue((*reinterpret_cast< const QScriptValue(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (AllItemModel::*_t)() const;
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AllItemModel::allItemDataEdited)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject AllItemModel::staticMetaObject = {
    { &QAbstractItemModel::staticMetaObject, qt_meta_stringdata_AllItemModel.data,
      qt_meta_data_AllItemModel,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *AllItemModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AllItemModel::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_AllItemModel.stringdata0))
        return static_cast<void*>(const_cast< AllItemModel*>(this));
    return QAbstractItemModel::qt_metacast(_clname);
}

int AllItemModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractItemModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void AllItemModel::allItemDataEdited()const
{
    QMetaObject::activate(const_cast< AllItemModel *>(this), &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
