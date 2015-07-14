#ifndef NETWORKCONTROL_H_
#define NETWORKCONTROL_H_

#include "Client.h"
#include "Server.h"
#include <bb/cascades/Image>
#include "src/source/PresentationControl.hpp"

class NetworkControl : public QObject {
    Q_OBJECT

    public:
        NetworkControl(PresentationControl* p);
        NetworkControl();
        ~NetworkControl();

        Q_INVOKABLE void startServer();
        Q_INVOKABLE void join(QString address, QString name, QString password);
        Q_INVOKABLE void shutdown();
        Q_INVOKABLE void quit();

    public slots:
        void onPresentationChanged();
        //client slots
        void onHostFound() {
            emit hostFound();
        }
        void onConnected() {
            emit connectionSuccessfull();
        }
        void onLoggingIn() {
            emit loggingIn();
        }
        void onConnectionAccepted() {
            emit connectionAccepted();
        }
        void onDisconnected() {
            emit disconnected();
        }
        void onPresentationReceived(QString title, QList<QImage> list);
        //server slots
        void onStarted() {
            emit serverStarted();
        }
        void onClientConnected() {
            emit clientConnected();
        }
        void onClientVerified() {
            emit clientVerified();
        }
        void onClientLeft() {
            emit clientLeft();
        }
        void onClosed() {
            emit serverClosed();
        }

    signals:
        //client signals
        void hostFound();
        void connectionSuccessfull();
        void loggingIn();
        void connectionAccepted();
        void presentationReady();
        void disconnected();
        //server signals
        void serverStarted();
        void clientConnected();
        void clientVerified();
        void clientLeft();
        void serverClosed();

    private:
        Client* client;
        Server* server;
        PresentationControl* pc;
};

#endif /* NETWORKCONTROL_H_ */
