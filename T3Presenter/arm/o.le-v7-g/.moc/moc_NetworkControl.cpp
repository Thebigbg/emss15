/****************************************************************************
** Meta object code from reading C++ file 'NetworkControl.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/network/NetworkControl.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'NetworkControl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_NetworkControl[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      27,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      11,       // signalCount

 // signals: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x05,
      28,   15,   15,   15, 0x05,
      52,   15,   15,   15, 0x05,
      64,   15,   15,   15, 0x05,
      85,   15,   15,   15, 0x05,
     105,   15,   15,   15, 0x05,
     120,   15,   15,   15, 0x05,
     136,   15,   15,   15, 0x05,
     154,   15,   15,   15, 0x05,
     171,   15,   15,   15, 0x05,
     184,   15,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
     199,   15,   15,   15, 0x0a,
     223,   15,   15,   15, 0x0a,
     237,   15,   15,   15, 0x0a,
     251,   15,   15,   15, 0x0a,
     265,   15,   15,   15, 0x0a,
     288,   15,   15,   15, 0x0a,
     316,  305,   15,   15, 0x0a,
     362,   15,   15,   15, 0x0a,
     374,   15,   15,   15, 0x0a,
     394,   15,   15,   15, 0x0a,
     413,   15,   15,   15, 0x0a,
     428,   15,   15,   15, 0x0a,

 // methods: signature, parameters, type, tag, flags
     439,   15,   15,   15, 0x02,
     475,  453,   15,   15, 0x02,
     505,   15,   15,   15, 0x02,
     516,   15,   15,   15, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_NetworkControl[] = {
    "NetworkControl\0\0hostFound()\0"
    "connectionSuccessfull()\0loggingIn()\0"
    "connectionAccepted()\0presentationReady()\0"
    "disconnected()\0serverStarted()\0"
    "clientConnected()\0clientVerified()\0"
    "clientLeft()\0serverClosed()\0"
    "onPresentationChanged()\0onHostFound()\0"
    "onConnected()\0onLoggingIn()\0"
    "onConnectionAccepted()\0onDisconnected()\0"
    "title,list\0onPresentationReceived(QString,QList<QImage>)\0"
    "onStarted()\0onClientConnected()\0"
    "onClientVerified()\0onClientLeft()\0"
    "onClosed()\0startServer()\0address,name,password\0"
    "join(QString,QString,QString)\0shutdown()\0"
    "quit()\0"
};

void NetworkControl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        NetworkControl *_t = static_cast<NetworkControl *>(_o);
        switch (_id) {
        case 0: _t->hostFound(); break;
        case 1: _t->connectionSuccessfull(); break;
        case 2: _t->loggingIn(); break;
        case 3: _t->connectionAccepted(); break;
        case 4: _t->presentationReady(); break;
        case 5: _t->disconnected(); break;
        case 6: _t->serverStarted(); break;
        case 7: _t->clientConnected(); break;
        case 8: _t->clientVerified(); break;
        case 9: _t->clientLeft(); break;
        case 10: _t->serverClosed(); break;
        case 11: _t->onPresentationChanged(); break;
        case 12: _t->onHostFound(); break;
        case 13: _t->onConnected(); break;
        case 14: _t->onLoggingIn(); break;
        case 15: _t->onConnectionAccepted(); break;
        case 16: _t->onDisconnected(); break;
        case 17: _t->onPresentationReceived((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QList<QImage>(*)>(_a[2]))); break;
        case 18: _t->onStarted(); break;
        case 19: _t->onClientConnected(); break;
        case 20: _t->onClientVerified(); break;
        case 21: _t->onClientLeft(); break;
        case 22: _t->onClosed(); break;
        case 23: _t->startServer(); break;
        case 24: _t->join((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 25: _t->shutdown(); break;
        case 26: _t->quit(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData NetworkControl::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject NetworkControl::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_NetworkControl,
      qt_meta_data_NetworkControl, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &NetworkControl::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *NetworkControl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *NetworkControl::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NetworkControl))
        return static_cast<void*>(const_cast< NetworkControl*>(this));
    return QObject::qt_metacast(_clname);
}

int NetworkControl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 27)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 27;
    }
    return _id;
}

// SIGNAL 0
void NetworkControl::hostFound()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void NetworkControl::connectionSuccessfull()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void NetworkControl::loggingIn()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void NetworkControl::connectionAccepted()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void NetworkControl::presentationReady()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void NetworkControl::disconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void NetworkControl::serverStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}

// SIGNAL 7
void NetworkControl::clientConnected()
{
    QMetaObject::activate(this, &staticMetaObject, 7, 0);
}

// SIGNAL 8
void NetworkControl::clientVerified()
{
    QMetaObject::activate(this, &staticMetaObject, 8, 0);
}

// SIGNAL 9
void NetworkControl::clientLeft()
{
    QMetaObject::activate(this, &staticMetaObject, 9, 0);
}

// SIGNAL 10
void NetworkControl::serverClosed()
{
    QMetaObject::activate(this, &staticMetaObject, 10, 0);
}
QT_END_MOC_NAMESPACE
