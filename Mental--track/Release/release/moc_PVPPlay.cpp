/****************************************************************************
** Meta object code from reading C++ file 'PVPPlay.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../PVPPlay.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PVPPlay.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PVPPlay_t {
    QByteArrayData data[14];
    char stringdata0[196];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PVPPlay_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PVPPlay_t qt_meta_stringdata_PVPPlay = {
    {
QT_MOC_LITERAL(0, 0, 7), // "PVPPlay"
QT_MOC_LITERAL(1, 8, 23), // "onConnectionEstablished"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 12), // "opponentName"
QT_MOC_LITERAL(4, 46, 18), // "onGameDataReceived"
QT_MOC_LITERAL(5, 65, 4), // "data"
QT_MOC_LITERAL(6, 70, 16), // "onConnectionLost"
QT_MOC_LITERAL(7, 87, 18), // "onWaitingForPlayer"
QT_MOC_LITERAL(8, 106, 22), // "onOpponentDisconnected"
QT_MOC_LITERAL(9, 129, 18), // "onConnectionFailed"
QT_MOC_LITERAL(10, 148, 6), // "reason"
QT_MOC_LITERAL(11, 155, 19), // "onExitButtonClicked"
QT_MOC_LITERAL(12, 175, 10), // "onGameOver"
QT_MOC_LITERAL(13, 186, 9) // "playerWon"

    },
    "PVPPlay\0onConnectionEstablished\0\0"
    "opponentName\0onGameDataReceived\0data\0"
    "onConnectionLost\0onWaitingForPlayer\0"
    "onOpponentDisconnected\0onConnectionFailed\0"
    "reason\0onExitButtonClicked\0onGameOver\0"
    "playerWon"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PVPPlay[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x08 /* Private */,
       4,    1,   57,    2, 0x08 /* Private */,
       6,    0,   60,    2, 0x08 /* Private */,
       7,    0,   61,    2, 0x08 /* Private */,
       8,    0,   62,    2, 0x08 /* Private */,
       9,    1,   63,    2, 0x08 /* Private */,
      11,    0,   66,    2, 0x08 /* Private */,
      12,    1,   67,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QByteArray,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   13,

       0        // eod
};

void PVPPlay::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PVPPlay *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onConnectionEstablished((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->onGameDataReceived((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 2: _t->onConnectionLost(); break;
        case 3: _t->onWaitingForPlayer(); break;
        case 4: _t->onOpponentDisconnected(); break;
        case 5: _t->onConnectionFailed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->onExitButtonClicked(); break;
        case 7: _t->onGameOver((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PVPPlay::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_PVPPlay.data,
    qt_meta_data_PVPPlay,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PVPPlay::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PVPPlay::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PVPPlay.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int PVPPlay::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
