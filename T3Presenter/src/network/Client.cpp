/*
 * Client.cpp
 *
 *  Created on: 07.06.2015
 *      Author: Philip
 */

// Client.cpp – class definition
#include "Client.h"


Client::Client(): QObject() {
    id = 0;
    presentationReady = false;
    expectedBytes = 0;
    socket = new QTcpSocket();
    socket->open(QIODevice::ReadWrite);
}

Client::~Client() {
    socket->close();
}

void Client::setSocket(QTcpSocket* socket) {
    Client::socket = socket;
}

QTcpSocket* Client::getSocket() {
    return socket;
}
void Client::setName(QString name) {
    Client::name = name;
}

QString Client::getName() {
    return name;
}

void Client::setPassword(QString password) {
    Client::password = password;
}

QString Client::getPassword() {
    return password;
}

void Client::setID(qint32 id) {
    Client::id = id;
}

qint32 Client::getID() {
    return id;
}

void Client::connect(QString address, quint16 port) {
    //connecting signals for UI
    QObject::connect(socket, SIGNAL(connected()), this, SLOT(onConnected()));
    //QObject::connect(socket, SIGNAL(hostFound()), this, SLOT(onHostFound()));
    QObject::connect(socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    QObject::connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onError(QAbstractSocket::SocketError)));
    // connecting read function to new data signal
    QObject::connect(socket, SIGNAL(readyRead()), this, SLOT(receiveData()));
    // and the socket to host
    QHostAddress addr(address);
    socket->connectToHost(addr, port);
    qDebug() << ">>connecting to Server" << endl;
}

QByteArray Client::receiveBuffer(QTcpSocket* socket) {
        QByteArray buffer;
        qint64 bytesExpected = 0;

        while(bytesExpected == 0 && socket->bytesAvailable() >= sizeof(qint64)) {
            socket->read((char *)&bytesExpected, sizeof(bytesExpected));
            qDebug() << "Expecting:" << qint64(bytesExpected) << "bytes" << endl << endl;
        }
        while(bytesExpected > 0) {
            if(!socket->waitForReadyRead(20000)) {
                qDebug() << "waiting for bytes to read ..."<< endl << endl;
                break;
            }
            QByteArray chunk = socket->read(qMin(bytesExpected, socket->bytesAvailable()));
            buffer += chunk;
            bytesExpected -= chunk.size();
            qDebug() << "Read:"<< chunk.size() <<"Remaining:" << bytesExpected << "Available: "<< socket->bytesAvailable() << endl << endl;;

            if (bytesExpected == 0) {
                qDebug() << "Bytes left in socket:" << socket->bytesAvailable() << endl << endl;
            }
        }
        return buffer;
}

void Client::extractPresentationData(QByteArray buffer) {
    //Number of Pages
    qint32 pages;
    QByteArray x;
    x.append(buffer.at(0));
    bool* ok = false;
    pages = x.toInt(ok, 10);

    //Length of title
    qint32 titleLength;
    QByteArray y;
    y.append(buffer.at(1));
    bool* ok1 = false;
    titleLength = y.toInt(ok1, 10);

    //Title itself
    QString title;
    for(int i = 2; i < 2+titleLength; i++) {
        title += buffer.at(i);
    }

    qDebug() << "Presentation"<< title <<" contains "<< pages << " pages";

    //extracting image sizes
    QByteArray z;
    qint64 sizeSize = 0;
    QList<qint64> sizeList;

    int pos = 2+titleLength;
    for(int i = 0; i < pages; i++) {
        z.append(buffer.at(pos));
        bool* ok = false;
        sizeSize = z.toInt(ok, 10);
        QByteArray q;
        for(int i = pos+1; i < (pos+sizeSize)+1; i++) {
            q.append(buffer.at(i));
        }
        qint64 size = q.toInt(ok, 10);
        q.clear();
        sizeList.append(size);
        qDebug() << "Received Image size: "<< size << "bytes, size of size:" << sizeSize << "bytes";
        pos += (sizeSize+1);
        z.clear();
    }

    qDebug() << "Position: " << pos;

    //extract images
    QList<QImage> imgList;
    QImage img;

    for(int i = 0; i < pages; i++) {

        qint64 imgSize = sizeList.at(i);
        QByteArray imgData;
        for(int j = pos; j < pos+imgSize; j++) {
            imgData.append(buffer.at(j));
        }

        pos += (imgSize);

        qDebug() << imgData.size() << "bytes read";
        qDebug() << "Position: " << pos;

        QBuffer imgBuffer(&imgData);
        QImageReader reader(&imgBuffer, "JPG");
        img = reader.read();

        if(!img.isNull()) {
            imgList.append(img);
            qDebug() << "image load successfull:"<< i;
        } else {
            qDebug() << "image load failed";
        }
    }
    emit presentationReceived(title, imgList);
    presentationReady = true;
}


void Client::receiveData() {
    if(!presentationReady) {
        while(expectedBytes == 0 && socket->bytesAvailable() >= sizeof(qint64)) {
            socket->read((char *)&expectedBytes, sizeof(expectedBytes));
            qDebug() << "Expected Presentation data:" << expectedBytes << "bytes";
        }

        QByteArray buffer;
        while(buffer.size() < expectedBytes) {
            buffer += Client::receiveBuffer(socket);
            qDebug() << "Received:" << buffer.size() << "of" << expectedBytes << "bytes";
        }
        Client::extractPresentationData(buffer);
    }else {
        qint64 currentPage = 0;
        while(currentPage == 0 && socket->bytesAvailable() >= sizeof(qint64)) {
            socket->read((char *)&currentPage, sizeof(currentPage));
            qDebug() << "Current Page:" << currentPage;
            emit currentPageReceived(currentPage);
        }
    }
}


void Client::onConnected() {
   emit connected();
}

void Client::onHostFound() {
    emit hostFound();
}

void Client::onDisconnected() {
    emit disconnected();
}

void Client::onError(QAbstractSocket::SocketError) {

}






