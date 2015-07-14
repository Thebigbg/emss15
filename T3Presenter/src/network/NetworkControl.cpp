/*
 * NetworkControl.cpp
 *
 *  Created on: 28.06.2015
 *      Author: Philip
 */
#include "NetworkControl.h"

NetworkControl::NetworkControl(PresentationControl* p) {
    pc = p;
    QObject::connect(pc, SIGNAL(presentationChanged()), this, SLOT(onPresentationChanged()));
    QThread* networkThread = new QThread();

    client = new Client();
    QObject::connect(client, SIGNAL(currentPageReceived(qint64)), pc, SLOT(onCurrenPageChanged(qint64)));
    QObject::connect(client, SIGNAL(connected()), this, SLOT(onConnected()));
    QObject::connect(client, SIGNAL(hostFound()), this, SLOT(onHostFound()));
    QObject::connect(client, SIGNAL(loggingIn()), this, SLOT(onLoggingIn()));
    QObject::connect(client, SIGNAL(successfullJoin()), this, SLOT(onConnectionAccepted()));
    QObject::connect(client, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    QObject::connect(client, SIGNAL(presentationReceived(QString, QList<QImage>)), this, SLOT(onPresentationReceived(QString, QList<QImage>)));

    server = new Server();

    server->setPresentation(p->getPresentation());
    QObject::connect(server, SIGNAL(listening()), this, SLOT(onStarted()));
    QObject::connect(server, SIGNAL(connectionAccepted()), this, SLOT(onClientConnected()));
    QObject::connect(server, SIGNAL(clientVerified()), this, SLOT(onClientVerified()));
    QObject::connect(server, SIGNAL(clientLeft()), this, SLOT(onClientLeft()));
    QObject::connect(server, SIGNAL(closing()), this, SLOT(onClosed()));
}
NetworkControl::NetworkControl() {
    client = new Client();

    QObject::connect(client, SIGNAL(connected()), this, SLOT(onConnected()));
    QObject::connect(client, SIGNAL(hostFound()), this, SLOT(onHostFound()));
    QObject::connect(client, SIGNAL(loggingIn()), this, SLOT(onLoggingIn()));
    QObject::connect(client, SIGNAL(successfullJoin()), this, SLOT(onConnectionAccepted()));
    QObject::connect(client, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    QObject::connect(client, SIGNAL(presentationReceived(QString, QList<QImage>)), this, SLOT(onPresentationReceived(QString, QList<QImage>)));

    server = new Server();
    QObject::connect(server, SIGNAL(listening()), this, SLOT(onStarted()));
    QObject::connect(server, SIGNAL(connectionAccepted()), this, SLOT(onClientConnected()));
    QObject::connect(server, SIGNAL(clientVerified()), this, SLOT(onClientVerified()));
    QObject::connect(server, SIGNAL(clientLeft()), this, SLOT(onClientLeft()));
    QObject::connect(server, SIGNAL(closing()), this, SLOT(onClosed()));

}

NetworkControl::~NetworkControl() {
    server->stop();
}
void NetworkControl::startServer() {
    server->listen();
}
void NetworkControl::shutdown() {
    server->stop();
}
void NetworkControl::join(QString address, QString name, QString password) {
    client->setName(name);
    client->setPassword(password);
    client->connect(address, 1234);
}

void NetworkControl::onPresentationChanged() {
    server->writeCurrentPage(pc->getCurrentPageNumber());
}

void NetworkControl::onPresentationReceived(QString title, QList<QImage> list) {
    pc->clear();
    pc->setTitle(title);
    qDebug() << "presentation title set:" << title;
    QDir dir;
    dir.mkdir("shared/documents/T3Presenter/download");
    dir.mkdir("shared/documents/T3Presenter/download/"+title);

    for(int i = 0; i < list.size(); i++) {
        QString name = "image";
        name.append(QString::number(i, 10));
        name.append(".jpg");

        QString path = "shared/documents/T3Presenter/download/"+title+"/"+name;
        qDebug() << "trying to save image as :" << name << ", letters: "<< name.size();
        QImageWriter writer(path, "JPG");
        QImage qi = list.at(i);
        bool saved = writer.write(qi);
        qDebug() << "image saved:" << saved << " bytes written";
        pc->getPresentation()->add("/accounts/1000/"+path);
    }
    emit presentationReady();
}
void NetworkControl::quit() {
    client->getSocket()->close();
}


