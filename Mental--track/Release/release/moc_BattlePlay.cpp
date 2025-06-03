/****************************************************************************
** Meta object code from reading C++ file 'BattlePlay.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../BattlePlay.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'BattlePlay.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_BattlePlay_t {
    QByteArrayData data[9];
    char stringdata0[110];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BattlePlay_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BattlePlay_t qt_meta_stringdata_BattlePlay = {
    {
QT_MOC_LITERAL(0, 0, 10), // "BattlePlay"
QT_MOC_LITERAL(1, 11, 10), // "onGameOver"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 9), // "playerWon"
QT_MOC_LITERAL(4, 33, 20), // "onDifficultySelected"
QT_MOC_LITERAL(5, 54, 10), // "difficulty"
QT_MOC_LITERAL(6, 65, 20), // "onPauseButtonClicked"
QT_MOC_LITERAL(7, 86, 10), // "resumeGame"
QT_MOC_LITERAL(8, 97, 12) // "restartLevel"

    },
    "BattlePlay\0onGameOver\0\0playerWon\0"
    "onDifficultySelected\0difficulty\0"
    "onPauseButtonClicked\0resumeGame\0"
    "restartLevel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BattlePlay[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x08 /* Private */,
       4,    1,   42,    2, 0x08 /* Private */,
       6,    0,   45,    2, 0x08 /* Private */,
       7,    0,   46,    2, 0x08 /* Private */,
       8,    0,   47,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void BattlePlay::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<BattlePlay *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onGameOver((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->onDifficultySelected((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->onPauseButtonClicked(); break;
        case 3: _t->resumeGame(); break;
        case 4: _t->restartLevel(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject BattlePlay::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_BattlePlay.data,
    qt_meta_data_BattlePlay,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *BattlePlay::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BattlePlay::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BattlePlay.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int BattlePlay::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
