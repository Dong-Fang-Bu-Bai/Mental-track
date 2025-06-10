/****************************************************************************
** Meta object code from reading C++ file 'PVPNetworkManager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../PVPNetworkManager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PVPNetworkManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PVPNetworkManager_t {
    QByteArrayData data[23];
    char stringdata0[335];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PVPNetworkManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PVPNetworkManager_t qt_meta_stringdata_PVPNetworkManager = {
    {
QT_MOC_LITERAL(0, 0, 17), // "PVPNetworkManager"
QT_MOC_LITERAL(1, 18, 21), // "connectionEstablished"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 12), // "opponentName"
QT_MOC_LITERAL(4, 54, 16), // "gameDataReceived"
QT_MOC_LITERAL(5, 71, 4), // "data"
QT_MOC_LITERAL(6, 76, 14), // "connectionLost"
QT_MOC_LITERAL(7, 91, 16), // "waitingForPlayer"
QT_MOC_LITERAL(8, 108, 20), // "opponentDisconnected"
QT_MOC_LITERAL(9, 129, 16), // "connectionFailed"
QT_MOC_LITERAL(10, 146, 6), // "reason"
QT_MOC_LITERAL(11, 153, 16), // "passwordRequired"
QT_MOC_LITERAL(12, 170, 16), // "passwordAccepted"
QT_MOC_LITERAL(13, 187, 13), // "opponentReady"
QT_MOC_LITERAL(14, 201, 9), // "hostReady"
QT_MOC_LITERAL(15, 211, 12), // "readyToStart"
QT_MOC_LITERAL(16, 224, 16), // "gameOverReceived"
QT_MOC_LITERAL(17, 241, 9), // "playerWon"
QT_MOC_LITERAL(18, 251, 15), // "onNewConnection"
QT_MOC_LITERAL(19, 267, 17), // "onClientConnected"
QT_MOC_LITERAL(20, 285, 14), // "onDataReceived"
QT_MOC_LITERAL(21, 300, 14), // "onDisconnected"
QT_MOC_LITERAL(22, 315, 19) // "onConnectionTimeout"

    },
    "PVPNetworkManager\0connectionEstablished\0"
    "\0opponentName\0gameDataReceived\0data\0"
    "connectionLost\0waitingForPlayer\0"
    "opponentDisconnected\0connectionFailed\0"
    "reason\0passwordRequired\0passwordAccepted\0"
    "opponentReady\0hostReady\0readyToStart\0"
    "gameOverReceived\0playerWon\0onNewConnection\0"
    "onClientConnected\0onDataReceived\0"
    "onDisconnected\0onConnectionTimeout"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PVPNetworkManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      12,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   99,    2, 0x06 /* Public */,
       4,    1,  102,    2, 0x06 /* Public */,
       6,    0,  105,    2, 0x06 /* Public */,
       7,    0,  106,    2, 0x06 /* Public */,
       8,    0,  107,    2, 0x06 /* Public */,
       9,    1,  108,    2, 0x06 /* Public */,
      11,    0,  111,    2, 0x06 /* Public */,
      12,    0,  112,    2, 0x06 /* Public */,
      13,    0,  113,    2, 0x06 /* Public */,
      14,    0,  114,    2, 0x06 /* Public */,
      15,    0,  115,    2, 0x06 /* Public */,
      16,    1,  116,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      18,    0,  119,    2, 0x08 /* Private */,
      19,    0,  120,    2, 0x08 /* Private */,
      20,    0,  121,    2, 0x08 /* Private */,
      21,    0,  122,    2, 0x08 /* Private */,
      22,    0,  123,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QByteArray,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   17,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PVPNetworkManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PVPNetworkManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->connectionEstablished((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->gameDataReceived((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 2: _t->connectionLost(); break;
        case 3: _t->waitingForPlayer(); break;
        case 4: _t->opponentDisconnected(); break;
        case 5: _t->connectionFailed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->passwordRequired(); break;
        case 7: _t->passwordAccepted(); break;
        case 8: _t->opponentReady(); break;
        case 9: _t->hostReady(); break;
        case 10: _t->readyToStart(); break;
        case 11: _t->gameOverReceived((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->onNewConnection(); break;
        case 13: _t->onClientConnected(); break;
        case 14: _t->onDataReceived(); break;
        case 15: _t->onDisconnected(); break;
        case 16: _t->onConnectionTimeout(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PVPNetworkManager::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PVPNetworkManager::connectionEstablished)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PVPNetworkManager::*)(const QByteArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PVPNetworkManager::gameDataReceived)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (PVPNetworkManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PVPNetworkManager::connectionLost)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (PVPNetworkManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PVPNetworkManager::waitingForPlayer)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (PVPNetworkManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PVPNetworkManager::opponentDisconnected)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (PVPNetworkManager::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PVPNetworkManager::connectionFailed)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (PVPNetworkManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PVPNetworkManager::passwordRequired)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (PVPNetworkManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PVPNetworkManager::passwordAccepted)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (PVPNetworkManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PVPNetworkManager::opponentReady)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (PVPNetworkManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PVPNetworkManager::hostReady)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (PVPNetworkManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PVPNetworkManager::readyToStart)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (PVPNetworkManager::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PVPNetworkManager::gameOverReceived)) {
                *result = 11;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PVPNetworkManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_PVPNetworkManager.data,
    qt_meta_data_PVPNetworkManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PVPNetworkManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PVPNetworkManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PVPNetworkManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int PVPNetworkManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void PVPNetworkManager::connectionEstablished(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PVPNetworkManager::gameDataReceived(const QByteArray & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PVPNetworkManager::connectionLost()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void PVPNetworkManager::waitingForPlayer()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void PVPNetworkManager::opponentDisconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void PVPNetworkManager::connectionFailed(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void PVPNetworkManager::passwordRequired()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void PVPNetworkManager::passwordAccepted()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void PVPNetworkManager::opponentReady()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void PVPNetworkManager::hostReady()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void PVPNetworkManager::readyToStart()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}

// SIGNAL 11
void PVPNetworkManager::gameOverReceived(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
