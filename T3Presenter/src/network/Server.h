/*
 * Server.h
 *
 *  Created on: 07.06.2015
 *      Author: Philip
 */

#ifndef SERVER_H_
#define SERVER_H_

#include <QtNetwork> // Server.h
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include "src/source/Presentation.hpp"
#include "Client.h"



class Server: public QObject {
    Q_OBJECT

    public:
        Server();
        ~Server();
        void listen();
        void stop();

        void setPresentation(Presentation* p);
        Presentation* getPresentation();

        void setPassword(QString password);
        QString getPassword();

        void writePresentation(QTcpSocket* client);
        void writeChunk(QByteArray, QTcpSocket* client);
        QByteArray getPresentationData();
        void writeCurrentPage(qint64);

    public slots:
        void acceptConnection();


    signals:
        //UI signals
        void listening();
        void connectionAccepted();
        void clientVerified();
        void clientLeft();
        void closing();


    private:
        QTcpServer* server;
        QList<Client*> clientList;
        QList<QTcpSocket*> socketList;
        qint32 idCounter;
        QString password;
        Presentation* presentation;
        QByteArray presentationData;
};


#endif /* SERVER_H_ */
