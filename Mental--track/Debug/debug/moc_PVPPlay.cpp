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
    QByteArrayData data[22];
    char stringdata0[319];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PVPPlay_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PVPPlay_t qt_meta_stringdata_PVPPlay = {
    {
QT_MOC_LITERAL(0, 0, 7), // "PVPPlay"
QT_MOC_LITERAL(1, 8, 13), // "returnToLobby"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 23), // "onConnectionEstablished"
QT_MOC_LITERAL(4, 47, 12), // "opponentName"
QT_MOC_LITERAL(5, 60, 18), // "onGameDataReceived"
QT_MOC_LITERAL(6, 79, 4), // "data"
QT_MOC_LITERAL(7, 84, 16), // "onConnectionLost"
QT_MOC_LITERAL(8, 101, 18), // "onWaitingForPlayer"
QT_MOC_LITERAL(9, 120, 22), // "onOpponentDisconnected"
QT_MOC_LITERAL(10, 143, 18), // "onConnectionFailed"
QT_MOC_LITERAL(11, 162, 6), // "reason"
QT_MOC_LITERAL(12, 169, 19), // "onExitButtonClicked"
QT_MOC_LITERAL(13, 189, 10), // "onGameOver"
QT_MOC_LITERAL(14, 200, 9), // "playerWon"
QT_MOC_LITERAL(15, 210, 13), // "onTurnChanged"
QT_MOC_LITERAL(16, 224, 12), // "isPlayerTurn"
QT_MOC_LITERAL(17, 237, 24), // "onTimerVisibilityChanged"
QT_MOC_LITERAL(18, 262, 7), // "visible"
QT_MOC_LITERAL(19, 270, 10), // "isCritical"
QT_MOC_LITERAL(20, 281, 24), // "onReturnToLobbyConfirmed"
QT_MOC_LITERAL(21, 306, 12) // "keepRoomOpen"

    },
    "PVPPlay\0returnToLobby\0\0onConnectionEstablished\0"
    "opponentName\0onGameDataReceived\0data\0"
    "onConnectionLost\0onWaitingForPlayer\0"
    "onOpponentDisconnected\0onConnectionFailed\0"
    "reason\0onExitButtonClicked\0onGameOver\0"
    "playerWon\0onTurnChanged\0isPlayerTurn\0"
    "onTimerVisibilityChanged\0visible\0"
    "isCritical\0onReturnToLobbyConfirmed\0"
    "keepRoomOpen"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PVPPlay[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   80,    2, 0x08 /* Private */,
       5,    1,   83,    2, 0x08 /* Private */,
       7,    0,   86,    2, 0x08 /* Private */,
       8,    0,   87,    2, 0x08 /* Private */,
       9,    0,   88,    2, 0x08 /* Private */,
      10,    1,   89,    2, 0x08 /* Private */,
      12,    0,   92,    2, 0x08 /* Private */,
      13,    1,   93,    2, 0x08 /* Private */,
      15,    1,   96,    2, 0x08 /* Private */,
      17,    2,   99,    2, 0x08 /* Private */,
      17,    1,  104,    2, 0x28 /* Private | MethodCloned */,
      20,    1,  107,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QByteArray,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   14,
    QMetaType::Void, QMetaType::Bool,   16,
    QMetaType::Void, QMetaType::Bool, QMetaType::Bool,   18,   19,
    QMetaType::Void, QMetaType::Bool,   18,
    QMetaType::Void, QMetaType::Bool,   21,

       0        // eod
};

void PVPPlay::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PVPPlay *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->returnToLobby(); break;
        case 1: _t->onConnectionEstablished((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->onGameDataReceived((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 3: _t->onConnectionLost(); break;
        case 4: _t->onWaitingForPlayer(); break;
        case 5: _t->onOpponentDisconnected(); break;
        case 6: _t->onConnectionFailed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->onExitButtonClicked(); break;
        case 8: _t->onGameOver((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->onTurnChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->onTimerVisibilityChanged((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 11: _t->onTimerVisibilityChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->onReturnToLobbyConfirmed((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PVPPlay::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PVPPlay::returnToLobby)) {
                *result = 0;
                return;
            }
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
void PVPPlay::returnToLobby()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
