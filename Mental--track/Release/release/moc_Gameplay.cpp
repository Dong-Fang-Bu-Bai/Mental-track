/****************************************************************************
** Meta object code from reading C++ file 'Gameplay.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Gameplay.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Gameplay.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Gameplay_t {
    QByteArrayData data[10];
    char stringdata0[133];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Gameplay_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Gameplay_t qt_meta_stringdata_Gameplay = {
    {
QT_MOC_LITERAL(0, 0, 8), // "Gameplay"
QT_MOC_LITERAL(1, 9, 20), // "returnToMapRequested"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 14), // "levelCompleted"
QT_MOC_LITERAL(4, 46, 7), // "levelId"
QT_MOC_LITERAL(5, 54, 11), // "updateTimer"
QT_MOC_LITERAL(6, 66, 21), // "onReturnButtonClicked"
QT_MOC_LITERAL(7, 88, 20), // "onPauseButtonClicked"
QT_MOC_LITERAL(8, 109, 10), // "resumeGame"
QT_MOC_LITERAL(9, 120, 12) // "restartLevel"

    },
    "Gameplay\0returnToMapRequested\0\0"
    "levelCompleted\0levelId\0updateTimer\0"
    "onReturnButtonClicked\0onPauseButtonClicked\0"
    "resumeGame\0restartLevel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Gameplay[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,
       3,    1,   50,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   53,    2, 0x08 /* Private */,
       6,    0,   54,    2, 0x08 /* Private */,
       7,    0,   55,    2, 0x08 /* Private */,
       8,    0,   56,    2, 0x08 /* Private */,
       9,    0,   57,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Gameplay::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Gameplay *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->returnToMapRequested(); break;
        case 1: _t->levelCompleted((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->updateTimer(); break;
        case 3: _t->onReturnButtonClicked(); break;
        case 4: _t->onPauseButtonClicked(); break;
        case 5: _t->resumeGame(); break;
        case 6: _t->restartLevel(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Gameplay::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Gameplay::returnToMapRequested)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Gameplay::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Gameplay::levelCompleted)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Gameplay::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_Gameplay.data,
    qt_meta_data_Gameplay,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Gameplay::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gameplay::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Gameplay.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Gameplay::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void Gameplay::returnToMapRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Gameplay::levelCompleted(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
