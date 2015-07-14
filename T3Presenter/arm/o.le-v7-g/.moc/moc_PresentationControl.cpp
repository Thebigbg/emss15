/****************************************************************************
** Meta object code from reading C++ file 'PresentationControl.hpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/source/PresentationControl.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PresentationControl.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PresentationControl[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x05,
      40,   34,   20,   20, 0x05,
      64,   20,   20,   20, 0x05,
      77,   34,   20,   20, 0x05,
     101,   20,   20,   20, 0x05,
     123,   20,   20,   20, 0x05,

 // slots: signature, parameters, type, tag, flags
     144,   20,   20,   20, 0x0a,
     168,   20,   20,   20, 0x0a,

 // methods: signature, parameters, type, tag, flags
     201,  196,   20,   20, 0x02,
     224,  196,   20,   20, 0x02,
     238,   34,   20,   20, 0x02,
     257,   20,  252,   20, 0x02,
     274,   20,  267,   20, 0x02,
     304,  297,   20,   20, 0x02,
     341,   20,  333,   20, 0x02,
     363,  358,  333,   20, 0x02,
     375,   20,  333,   20, 0x02,
     386,   34,   20,   20, 0x02,
     404,   20,  267,   20, 0x02,
     423,   20,   20,   20, 0x02,
     431,   20,  252,   20, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_PresentationControl[] = {
    "PresentationControl\0\0loadFailed()\0"
    "title\0loadSucessfull(QString)\0"
    "saveFailed()\0saveSucessfull(QString)\0"
    "presentationChanged()\0currentPageChanged()\0"
    "onPresentationChanged()\0"
    "onCurrenPageChanged(qint64)\0path\0"
    "loadFiles(QStringList)\0load(QString)\0"
    "save(QString)\0bool\0isSaved()\0qint32\0"
    "getCurrentPageNumber()\0number\0"
    "setCurrentPageNumber(qint32)\0QString\0"
    "getCurrentPage()\0page\0get(qint32)\0"
    "getTitle()\0setTitle(QString)\0"
    "getNumberOfPages()\0clear()\0isEmpty()\0"
};

void PresentationControl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PresentationControl *_t = static_cast<PresentationControl *>(_o);
        switch (_id) {
        case 0: _t->loadFailed(); break;
        case 1: _t->loadSucessfull((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->saveFailed(); break;
        case 3: _t->saveSucessfull((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->presentationChanged(); break;
        case 5: _t->currentPageChanged(); break;
        case 6: _t->onPresentationChanged(); break;
        case 7: _t->onCurrenPageChanged((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 8: _t->loadFiles((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 9: _t->load((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->save((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: { bool _r = _t->isSaved();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 12: { qint32 _r = _t->getCurrentPageNumber();
            if (_a[0]) *reinterpret_cast< qint32*>(_a[0]) = _r; }  break;
        case 13: _t->setCurrentPageNumber((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 14: { QString _r = _t->getCurrentPage();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 15: { QString _r = _t->get((*reinterpret_cast< qint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 16: { QString _r = _t->getTitle();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 17: _t->setTitle((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 18: { qint32 _r = _t->getNumberOfPages();
            if (_a[0]) *reinterpret_cast< qint32*>(_a[0]) = _r; }  break;
        case 19: _t->clear(); break;
        case 20: { bool _r = _t->isEmpty();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData PresentationControl::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PresentationControl::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_PresentationControl,
      qt_meta_data_PresentationControl, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PresentationControl::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PresentationControl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PresentationControl::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PresentationControl))
        return static_cast<void*>(const_cast< PresentationControl*>(this));
    return QObject::qt_metacast(_clname);
}

int PresentationControl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    }
    return _id;
}

// SIGNAL 0
void PresentationControl::loadFailed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void PresentationControl::loadSucessfull(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PresentationControl::saveFailed()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void PresentationControl::saveSucessfull(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void PresentationControl::presentationChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void PresentationControl::currentPageChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}
QT_END_MOC_NAMESPACE
