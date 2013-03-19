/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../RncAcqGui/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[22];
    char stringdata[459];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_MainWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 10),
QT_MOC_LITERAL(2, 22, 0),
QT_MOC_LITERAL(3, 23, 11),
QT_MOC_LITERAL(4, 35, 3),
QT_MOC_LITERAL(5, 39, 5),
QT_MOC_LITERAL(6, 45, 16),
QT_MOC_LITERAL(7, 62, 13),
QT_MOC_LITERAL(8, 76, 19),
QT_MOC_LITERAL(9, 96, 24),
QT_MOC_LITERAL(10, 121, 21),
QT_MOC_LITERAL(11, 143, 26),
QT_MOC_LITERAL(12, 170, 26),
QT_MOC_LITERAL(13, 197, 23),
QT_MOC_LITERAL(14, 221, 29),
QT_MOC_LITERAL(15, 251, 26),
QT_MOC_LITERAL(16, 278, 26),
QT_MOC_LITERAL(17, 305, 28),
QT_MOC_LITERAL(18, 334, 28),
QT_MOC_LITERAL(19, 363, 28),
QT_MOC_LITERAL(20, 392, 33),
QT_MOC_LITERAL(21, 426, 31)
    },
    "MainWindow\0AbreMsgBox\0\0const char*\0"
    "msg\0timer\0PlotaCoordenadas\0on_AbreMsgBox\0"
    "on_PlotaCoordenadas\0on_ButtonIniciar_clicked\0"
    "on_ButtonStop_clicked\0on_pushButtonPonte_clicked\0"
    "on_pushButtonTunel_clicked\0"
    "on_pushButtonPN_clicked\0"
    "on_pushButtonInicioSb_clicked\0"
    "on_pushButtonFimSb_clicked\0"
    "on_pushButtonMarco_clicked\0"
    "on_pushButtonUsuario_clicked\0"
    "on_pushButtonTunel_2_clicked\0"
    "on_pushButtonPonte_2_clicked\0"
    "on_toolButtonProximoMarco_clicked\0"
    "on_toolButtonMarcoAtual_clicked\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   99,    2, 0x05,
       6,    0,  104,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       7,    2,  105,    2, 0x0a,
       8,    0,  110,    2, 0x0a,
       9,    0,  111,    2, 0x08,
      10,    0,  112,    2, 0x08,
      11,    0,  113,    2, 0x08,
      12,    0,  114,    2, 0x08,
      13,    0,  115,    2, 0x08,
      14,    0,  116,    2, 0x08,
      15,    0,  117,    2, 0x08,
      16,    0,  118,    2, 0x08,
      17,    0,  119,    2, 0x08,
      18,    0,  120,    2, 0x08,
      19,    0,  121,    2, 0x08,
      20,    0,  122,    2, 0x08,
      21,    0,  123,    2, 0x08,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    4,    5,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    4,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->AbreMsgBox((*reinterpret_cast< const char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->PlotaCoordenadas(); break;
        case 2: _t->on_AbreMsgBox((*reinterpret_cast< const char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->on_PlotaCoordenadas(); break;
        case 4: _t->on_ButtonIniciar_clicked(); break;
        case 5: _t->on_ButtonStop_clicked(); break;
        case 6: _t->on_pushButtonPonte_clicked(); break;
        case 7: _t->on_pushButtonTunel_clicked(); break;
        case 8: _t->on_pushButtonPN_clicked(); break;
        case 9: _t->on_pushButtonInicioSb_clicked(); break;
        case 10: _t->on_pushButtonFimSb_clicked(); break;
        case 11: _t->on_pushButtonMarco_clicked(); break;
        case 12: _t->on_pushButtonUsuario_clicked(); break;
        case 13: _t->on_pushButtonTunel_2_clicked(); break;
        case 14: _t->on_pushButtonPonte_2_clicked(); break;
        case 15: _t->on_toolButtonProximoMarco_clicked(); break;
        case 16: _t->on_toolButtonMarcoAtual_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainWindow::*_t)(const char * , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::AbreMsgBox)) {
                *result = 0;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::PlotaCoordenadas)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    if (!strcmp(_clname, "View"))
        return static_cast< View*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
void MainWindow::AbreMsgBox(const char * _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::PlotaCoordenadas()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
