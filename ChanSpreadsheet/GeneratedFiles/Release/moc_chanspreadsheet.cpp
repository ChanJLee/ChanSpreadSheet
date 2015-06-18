/****************************************************************************
** Meta object code from reading C++ file 'chanspreadsheet.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../chanspreadsheet.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'chanspreadsheet.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ChanSpreadsheet_t {
    QByteArrayData data[14];
    char stringdata[142];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ChanSpreadsheet_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ChanSpreadsheet_t qt_meta_stringdata_ChanSpreadsheet = {
    {
QT_MOC_LITERAL(0, 0, 15), // "ChanSpreadsheet"
QT_MOC_LITERAL(1, 16, 7), // "newFile"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 4), // "open"
QT_MOC_LITERAL(4, 30, 4), // "save"
QT_MOC_LITERAL(5, 35, 6), // "saveAs"
QT_MOC_LITERAL(6, 42, 4), // "find"
QT_MOC_LITERAL(7, 47, 8), // "goToCell"
QT_MOC_LITERAL(8, 56, 4), // "sort"
QT_MOC_LITERAL(9, 61, 4), // "plot"
QT_MOC_LITERAL(10, 66, 20), // "aboutChanSpreadsheet"
QT_MOC_LITERAL(11, 87, 14), // "openRecentFile"
QT_MOC_LITERAL(12, 102, 15), // "updateStatusBar"
QT_MOC_LITERAL(13, 118, 23) // "chanSpreadsheetModified"

    },
    "ChanSpreadsheet\0newFile\0\0open\0save\0"
    "saveAs\0find\0goToCell\0sort\0plot\0"
    "aboutChanSpreadsheet\0openRecentFile\0"
    "updateStatusBar\0chanSpreadsheetModified"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ChanSpreadsheet[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x08 /* Private */,
       3,    0,   75,    2, 0x08 /* Private */,
       4,    0,   76,    2, 0x08 /* Private */,
       5,    0,   77,    2, 0x08 /* Private */,
       6,    0,   78,    2, 0x08 /* Private */,
       7,    0,   79,    2, 0x08 /* Private */,
       8,    0,   80,    2, 0x08 /* Private */,
       9,    0,   81,    2, 0x08 /* Private */,
      10,    0,   82,    2, 0x08 /* Private */,
      11,    0,   83,    2, 0x08 /* Private */,
      12,    0,   84,    2, 0x08 /* Private */,
      13,    0,   85,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Bool,
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

void ChanSpreadsheet::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ChanSpreadsheet *_t = static_cast<ChanSpreadsheet *>(_o);
        switch (_id) {
        case 0: _t->newFile(); break;
        case 1: _t->open(); break;
        case 2: { bool _r = _t->save();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: { bool _r = _t->saveAs();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 4: _t->find(); break;
        case 5: _t->goToCell(); break;
        case 6: _t->sort(); break;
        case 7: _t->plot(); break;
        case 8: _t->aboutChanSpreadsheet(); break;
        case 9: _t->openRecentFile(); break;
        case 10: _t->updateStatusBar(); break;
        case 11: _t->chanSpreadsheetModified(); break;
        default: ;
        }
    }
}

const QMetaObject ChanSpreadsheet::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_ChanSpreadsheet.data,
      qt_meta_data_ChanSpreadsheet,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ChanSpreadsheet::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ChanSpreadsheet::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ChanSpreadsheet.stringdata))
        return static_cast<void*>(const_cast< ChanSpreadsheet*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int ChanSpreadsheet::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
