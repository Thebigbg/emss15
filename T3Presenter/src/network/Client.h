/*
 * Client.h
 *
 *  Created on: 07.06.2015
 *      Author: Philip
 */

#ifndef CLIENT_H_
#define CLIENT_H_

#include <QtNetwork> // Client.h
#include <QHostAddress>
#include <QObject>
#include <QString>
#include <QBuffer>
#include <Qt/qimage.h>
#include <QTcpSocket>
#include "src/source/Presentation.hpp"
#include <bb/cascades/Image>

class Client : public QObject {
    Q_OBJECT

    public:
    Client();
    ~Client();

    void connect(QString address, quint16 port);
    QByteArray receiveBuffer(QTcpSocket* socket);
    void extractPresentationData(QByteArray buffer);

    void setName(QString name);
    QString getName();
    void setPassword(QString password);
    QString getPassword();
    void setSocket(QTcpSocket* socket);
    QTcpSocket* getSocket();
    void setID(qint32 id);
    qint32 getID();

    public slots:
        //
        void receiveData();

        //UI tunnel slots
        void onDisconnected();
        void onHostFound();
        void onConnected();
        void onError(QAbstractSocket::SocketError);

    signals:
        //UI signals
        void hostFound();
        void connected();
        void loggingIn();
        void successfullJoin();
        void disconnected();
        void presentationReceived(QString title, QList<QImage> imgList);
        void currentPageReceived(qint64);

    private:
        bool presentationReady;
        QTcpSocket* socket;
        qint32 id;
        qint64 expectedBytes;
        QString name;
        QString password;
        QImage recievedImg;
};

#endif /* CLIENT_H_ */
