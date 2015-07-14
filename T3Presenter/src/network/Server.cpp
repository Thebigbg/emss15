/*
 * Server.cpp
 *
 *  Created on: 07.06.2015
 *      Author: Philip
 */

#include "Server.h"
#include <iostream>
#include <QDebug>
using namespace std;

Server::Server(): QObject() {
    server = new QTcpServer();
    idCounter = 0;
    password = "";
    connect(server, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
}

Server::~Server() {
    server->close();
}

void Server::setPresentation(Presentation* p) {
    presentation = p;
}

Presentation* Server::getPresentation() {
    return presentation;
}

void Server::listen() {
    server->listen(QHostAddress("192.168.0.7"), 1234);
    emit listening();
    qDebug() << "Server starts listening ..." << endl;
}

void Server::stop() {
    server->close();
    emit closing();
}

void Server::setPassword(QString password) {
    Server::password = password;
}

QString Server::getPassword() {
    return password;
}

void Server::acceptConnection() {
    qDebug() << ">>server accepts connection ..." << endl;
    // getting socket
    QTcpSocket* socket = server->nextPendingConnection();
    socketList.append(socket);
    writePresentation(socket);

    emit connectionAccepted();
}

void Server::writeCurrentPage(qint64 currentPage) {
    for(int i = 0; i < socketList.size(); i++) {
        socketList.at(i)->write((const char*) &currentPage, sizeof(currentPage));
    }
}

void Server::writeChunk(QByteArray chunk, QTcpSocket* client) {
    qint64 bytesWritten = 0;
    qint64 chunkSize = chunk.size();
    client->write((const char*) &chunkSize, sizeof(chunkSize));
    while(bytesWritten < chunkSize) {
        qint64 bw2 = bytesWritten;
        bytesWritten += client->write(chunk);
        while(!client->waitForBytesWritten(20000)) {
            qDebug() << "Waiting for bytes to write";
            break;
        }
        if(bytesWritten == chunkSize) {
            qDebug() << "Bytes written: " << qint64(bytesWritten) << "/" << chunk.size();
        }
        if(bytesWritten < bw2) {
            qDebug() << "ERROR!!!";
        }
    }
}

QByteArray Server::getPresentationData() {
    QByteArray data;
    QByteArray ba;
    QByteArray imgData;
    QBuffer buffer(&ba);

    buffer.open(QIODevice::ReadWrite);

    data.append(QByteArray::number(presentation->size(), 10));
    data.append(QByteArray::number(presentation->getTitle().size(), 10));
    data.append(presentation->getTitle());

    qint64 imgSize = 0;
    qint64 bufferSize_b = 0;
    qint64 sizeSize = 0;

    for(int i = 0; i < presentation->size(); i++) {
        bufferSize_b = buffer.size();

        QImage img(presentation->get(i));
        img.save(&buffer, "JPG");

        imgSize = buffer.size() - bufferSize_b;
        sizeSize = QByteArray::number(imgSize, 10).size();
        data.append(QByteArray::number(sizeSize, 10));
        data.append(QByteArray::number(imgSize, 10));

        qDebug() << "Buffering image "<< i << "size: "<< imgSize << "bytes, size of size: "<< sizeSize << " bytes";
    }

    imgData = buffer.data();
    data.append(imgData);

    return data;
}

QList<QByteArray> splitData(QByteArray data, qint64 maxSize) {
    qint64 dataSize = data.size();
    QList<QByteArray> chunkList;
    if(dataSize > maxSize) {
        double x = double(dataSize)/double(maxSize);
        qint64 chunks = ceil(x);

        qDebug() << "Split data in " << chunks << "chunks" << x;

        qint64 bytesLeft = dataSize;
        qint64 bytesWritten = 0;
        int pos = 0;
        for(int i = 0; i < chunks; i++) {
            QByteArray chunk;
            for(int j = 0; ((j < maxSize) && (bytesLeft > 0)); j++) {
                int x = pos + j;
                chunk.append(data[x]);
                bytesLeft -= 1;
                bytesWritten += 1;
            }
            pos += bytesWritten;
            chunkList.append(chunk);
            qDebug() << "Chunk " << i << ", size:" << chunk.size() << "bytes, bytes left:" << bytesLeft;
        }
        return chunkList;
    }else {
        chunkList.append(data);
        return chunkList;
    }
}

void Server::writePresentation(QTcpSocket* client) {
    if(client->state()== QAbstractSocket::ConnectedState) {
        QByteArray data = Server::getPresentationData();
        qint64 dataSize = data.size();

        qDebug() << "Buffer size:" << dataSize;
        client->write((const char*) &dataSize, sizeof(dataSize));
        qint64 maxChunkSize = 100000;
        qDebug() << "Maximal chunk size:" << maxChunkSize;

        QList<QByteArray> chunkList = splitData(data, maxChunkSize);
        for(int i = 0; i < chunkList.size(); i++) {
            qDebug() << "Write chunk:" << i;
            Server::writeChunk(chunkList.at(i), client);
        }
    }
}




