/****************************************************************************
** Meta object code from reading C++ file 'Leaderboard.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Leaderboard.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Leaderboard.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Leaderboard_t {
    QByteArrayData data[10];
    char stringdata0[169];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Leaderboard_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Leaderboard_t qt_meta_stringdata_Leaderboard = {
    {
QT_MOC_LITERAL(0, 0, 11), // "Leaderboard"
QT_MOC_LITERAL(1, 12, 12), // "returnToMain"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 21), // "onPassedLevelsClicked"
QT_MOC_LITERAL(4, 48, 18), // "onBestTimesClicked"
QT_MOC_LITERAL(5, 67, 15), // "onMedalsClicked"
QT_MOC_LITERAL(6, 83, 17), // "onWorkshopClicked"
QT_MOC_LITERAL(7, 101, 22), // "on_btnWorkshop_clicked"
QT_MOC_LITERAL(8, 124, 20), // "on_btnBattle_clicked"
QT_MOC_LITERAL(9, 145, 23) // "on_OnlineBattle_clicked"

    },
    "Leaderboard\0returnToMain\0\0"
    "onPassedLevelsClicked\0onBestTimesClicked\0"
    "onMedalsClicked\0onWorkshopClicked\0"
    "on_btnWorkshop_clicked\0on_btnBattle_clicked\0"
    "on_OnlineBattle_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Leaderboard[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   55,    2, 0x08 /* Private */,
       4,    0,   56,    2, 0x08 /* Private */,
       5,    0,   57,    2, 0x08 /* Private */,
       6,    0,   58,    2, 0x08 /* Private */,
       7,    0,   59,    2, 0x08 /* Private */,
       8,    0,   60,    2, 0x08 /* Private */,
       9,    0,   61,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Leaderboard::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Leaderboard *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->returnToMain(); break;
        case 1: _t->onPassedLevelsClicked(); break;
        case 2: _t->onBestTimesClicked(); break;
        case 3: _t->onMedalsClicked(); break;
        case 4: _t->onWorkshopClicked(); break;
        case 5: _t->on_btnWorkshop_clicked(); break;
        case 6: _t->on_btnBattle_clicked(); break;
        case 7: _t->on_OnlineBattle_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Leaderboard::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Leaderboard::returnToMain)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject Leaderboard::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_Leaderboard.data,
    qt_meta_data_Leaderboard,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Leaderboard::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Leaderboard::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Leaderboard.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Leaderboard::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void Leaderboard::returnToMain()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
