/****************************************************************************
** Meta object code from reading C++ file 'chanSpreadsheetWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../chanSpreadsheetWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'chanSpreadsheetWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_chanSpreadsheetWidget_t {
    QByteArrayData data[21];
    char stringdata[225];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_chanSpreadsheetWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_chanSpreadsheetWidget_t qt_meta_stringdata_chanSpreadsheetWidget = {
    {
QT_MOC_LITERAL(0, 0, 21), // "chanSpreadsheetWidget"
QT_MOC_LITERAL(1, 22, 8), // "modified"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 3), // "cut"
QT_MOC_LITERAL(4, 36, 4), // "copy"
QT_MOC_LITERAL(5, 41, 5), // "paste"
QT_MOC_LITERAL(6, 47, 3), // "del"
QT_MOC_LITERAL(7, 51, 16), // "selectCurrentRow"
QT_MOC_LITERAL(8, 68, 19), // "selectCurrentColumn"
QT_MOC_LITERAL(9, 88, 11), // "recalculate"
QT_MOC_LITERAL(10, 100, 8), // "findNext"
QT_MOC_LITERAL(11, 109, 19), // "Qt::CaseSensitivity"
QT_MOC_LITERAL(12, 129, 8), // "findPrev"
QT_MOC_LITERAL(13, 138, 18), // "setAutoRecalculate"
QT_MOC_LITERAL(14, 157, 10), // "autoRecalc"
QT_MOC_LITERAL(15, 168, 16), // "somethingChanged"
QT_MOC_LITERAL(16, 185, 4), // "cell"
QT_MOC_LITERAL(17, 190, 10), // "tableCell*"
QT_MOC_LITERAL(18, 201, 4), // "text"
QT_MOC_LITERAL(19, 206, 7), // "formula"
QT_MOC_LITERAL(20, 214, 10) // "setFormula"

    },
    "chanSpreadsheetWidget\0modified\0\0cut\0"
    "copy\0paste\0del\0selectCurrentRow\0"
    "selectCurrentColumn\0recalculate\0"
    "findNext\0Qt::CaseSensitivity\0findPrev\0"
    "setAutoRecalculate\0autoRecalc\0"
    "somethingChanged\0cell\0tableCell*\0text\0"
    "formula\0setFormula"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_chanSpreadsheetWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   95,    2, 0x0a /* Public */,
       4,    0,   96,    2, 0x0a /* Public */,
       5,    0,   97,    2, 0x0a /* Public */,
       6,    0,   98,    2, 0x0a /* Public */,
       7,    0,   99,    2, 0x0a /* Public */,
       8,    0,  100,    2, 0x0a /* Public */,
       9,    0,  101,    2, 0x0a /* Public */,
      10,    2,  102,    2, 0x0a /* Public */,
      12,    2,  107,    2, 0x0a /* Public */,
      13,    1,  112,    2, 0x0a /* Public */,
      15,    0,  115,    2, 0x08 /* Private */,
      16,    2,  116,    2, 0x08 /* Private */,
      18,    2,  121,    2, 0x08 /* Private */,
      19,    2,  126,    2, 0x08 /* Private */,
      20,    3,  131,    2, 0x08 /* Private */,

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
    QMetaType::Void, QMetaType::QString, 0x80000000 | 11,    2,    2,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 11,    2,    2,
    QMetaType::Void, QMetaType::Bool,   14,
    QMetaType::Void,
    0x80000000 | 17, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::QString, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::QString, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::QString,    2,    2,    2,

       0        // eod
};

void chanSpreadsheetWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        chanSpreadsheetWidget *_t = static_cast<chanSpreadsheetWidget *>(_o);
        switch (_id) {
        case 0: _t->modified(); break;
        case 1: _t->cut(); break;
        case 2: _t->copy(); break;
        case 3: _t->paste(); break;
        case 4: _t->del(); break;
        case 5: _t->selectCurrentRow(); break;
        case 6: _t->selectCurrentColumn(); break;
        case 7: _t->recalculate(); break;
        case 8: _t->findNext((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< Qt::CaseSensitivity(*)>(_a[2]))); break;
        case 9: _t->findPrev((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< Qt::CaseSensitivity(*)>(_a[2]))); break;
        case 10: _t->setAutoRecalculate((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->somethingChanged(); break;
        case 12: { tableCell* _r = _t->cell((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< tableCell**>(_a[0]) = _r; }  break;
        case 13: { QString _r = _t->text((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 14: { QString _r = _t->formula((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 15: _t->setFormula((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (chanSpreadsheetWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&chanSpreadsheetWidget::modified)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject chanSpreadsheetWidget::staticMetaObject = {
    { &QTableWidget::staticMetaObject, qt_meta_stringdata_chanSpreadsheetWidget.data,
      qt_meta_data_chanSpreadsheetWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *chanSpreadsheetWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *chanSpreadsheetWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_chanSpreadsheetWidget.stringdata))
        return static_cast<void*>(const_cast< chanSpreadsheetWidget*>(this));
    return QTableWidget::qt_metacast(_clname);
}

int chanSpreadsheetWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTableWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void chanSpreadsheetWidget::modified()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
