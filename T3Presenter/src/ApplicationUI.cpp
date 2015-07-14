#include "ApplicationUI.hpp"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>
#include <bb/cascades/LocaleHandler>

using namespace bb::cascades;

ApplicationUI::ApplicationUI(bb::cascades::Application *app) : QObject(app)
{
    // keep display light on
    app->mainWindow()->setScreenIdleMode(ScreenIdleMode::KeepAwake);

    // prepare the localization
    m_pTranslator = new QTranslator(this);
    m_pLocaleHandler = new LocaleHandler(this);

    // connecting the localization
    bool res = QObject::connect(m_pLocaleHandler, SIGNAL(systemLanguageChanged()), this, SLOT(onSystemLanguageChanged()));
    Q_ASSERT(res);

    // initial load
    onSystemLanguageChanged();

    // prepare the DialogSystem
    m_Dialog = new bb::system::SystemDialog();
    m_toast = new SystemToast();

    //INIT PRESENTATIONCONTROL///////////////////////////////////////////////////////////////////////////////////////
    m_PresentationControl = new PresentationControl();
    // connecting the presentation save function
    QObject::connect(m_PresentationControl, SIGNAL(saveSucessfull(QString)), this, SLOT(onSaveSucessfull(QString)));
    QObject::connect(m_PresentationControl, SIGNAL(saveFailed(void)), this, SLOT(onSaveFailed()));
    // connecting the presentation load function
    QObject::connect(m_PresentationControl, SIGNAL(loadSucessfull(QString)), this, SLOT(onLoadSucessfull(QString)));
    QObject::connect(m_PresentationControl, SIGNAL(loadFailed(void)), this, SLOT(onLoadFailed()));
    //connecting changed listener
    QObject::connect(m_PresentationControl, SIGNAL(presentationChanged()), this, SLOT(onPresentationChanged()));
    //END INIT PRESENTATIONCONTROL///////////////////////////////////////////////////////////////////////////////////////

    //INIT NETWORKCONTROL///////////////////////////////////////////////////////////////////////////////////////////////
    m_NetworkControl = new NetworkControl(m_PresentationControl);
    //connecting server signals
    QObject::connect(m_NetworkControl, SIGNAL(serverStarted()), this, SLOT(onStarted()));
    QObject::connect(m_NetworkControl, SIGNAL(clientConnected()), this, SLOT(onClientConnected()));
    QObject::connect(m_NetworkControl, SIGNAL(clientVerified()), this, SLOT(onClientVerified()));
    QObject::connect(m_NetworkControl, SIGNAL(clientLeft()), this, SLOT(onClientLeft()));
    QObject::connect(m_NetworkControl, SIGNAL(serverClosed()), this, SLOT(onClosed()));
    //connecting client signals
    QObject::connect(m_NetworkControl, SIGNAL(hostFound()), this, SLOT(onHostFound()));
    QObject::connect(m_NetworkControl, SIGNAL(connectionSuccessfull()), this, SLOT(onConnectionSuccessfull()));
    QObject::connect(m_NetworkControl, SIGNAL(loggingIn()), this, SLOT(onLoggingIn()));
    QObject::connect(m_NetworkControl, SIGNAL(presentationReady()), this, SLOT(onPresentationReady()));
    QObject::connect(m_NetworkControl, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    //END INIT NETWORKCONTROL///////////////////////////////////////////////////////////////////////////////////////////

    QString workingDir = QDir::currentPath();
    QDeclarativePropertyMap* dirPaths = new QDeclarativePropertyMap;
    qDebug() << "file://" + workingDir + "/shared/documents/" << endl;

    //INIT QML///////////////////////////////////////////////////////////////////////////////////////////////////////////
    qmlRegisterType<PresentationControl>("my.library", 1, 0, "PresentationControl");
    qmlRegisterType<NetworkControl>("my.library", 1, 0, "NetworkControl");
    qmlRegisterType<NetworkControl>("my.library", 1, 0, "Image");
    // Create scene document from main.qml asset, the parent is set
    // to ensure the document gets destroyed properly at shut down.
    QmlDocument *qml = QmlDocument::create("asset:///MainMenuPage.qml").parent(this);
    // Create root object for the UI
    AbstractPane *root = qml->createRootObject<AbstractPane>();
    // Passing the Objects for access to c++ classes
    //!WORKAROUND! TODO pass the propertymap to qml
    qml->setContextProperty("_application", this);
    // Set created root object as the application scene
    Application::instance()->setScene(root);
    //END INIT QML///////////////////////////////////////////////////////////////////////////////////////////////////////////

    //Signal slot that handles the external display
        res = QObject::connect(this, SIGNAL(displaySign()), this, SLOT(ondisplaySign()));
        Q_ASSERT(res);

        bb::ImageData      imageData1, imageData2;

            extDisplay.setResolution(RES1920x1080);
            extDisplay.open(); //Open a new external display

            imageData1 = bb::utility::ImageConverter::decode(QUrl("asset:///images/logo_rub.png"));
            imageData2 = bb::utility::ImageConverter::decode(QUrl("asset:///images/team.png"));

            //Show imageData2 as default image on external display when starting the app
            extDisplay.showImage(imageData2);
}

//Show diff picturs on external display and blackberry display
void ApplicationUI::ondisplaySign() {
    // open external screen (via HDMI)

            bb::ImageData      imageData;
        //extDisplay.setResolution(RES1920x1080);
            //Close the external display -> thus close the default picture
            extDisplay.close();
            //Open up a new external display
            extDisplay.open();

            //Set the picture to show on the external display by getting the current page
            imageData = bb::utility::ImageConverter::decode(QUrl("file://"+m_PresentationControl->getCurrentPage()));

            qDebug() << "FIle:" << m_PresentationControl->getCurrentPage();
            //Show the image set above
            extDisplay.showImage(imageData);
}


//Function is called bei clicking on "next" or " preview during a presentation
void ApplicationUI::displayExt() {
//emit displaySign to call the function that shows a diff picture on external display
    emit displaySign();
  //return "Worked again";
}

PresentationControl* ApplicationUI::getPresentationControl() {
    return m_PresentationControl;
}

NetworkControl* ApplicationUI::getNetworkControl() {
    return m_NetworkControl;
}

void ApplicationUI::onPresentationChanged() {

}

//LANGUAGE//////////////////////////////////////////////////////////////////////////
void ApplicationUI::onSystemLanguageChanged()
{
    QCoreApplication::instance()->removeTranslator(m_pTranslator);
    // Initiate, load and install the application translation files.
    QString locale_string = QLocale().name();
    QString file_name = QString("T3Presenter_%1").arg(locale_string);
    if (m_pTranslator->load(file_name, "app/native/qm")) {
        QCoreApplication::instance()->installTranslator(m_pTranslator);
    }
}
//END LANGUAGE//////////////////////////////////////////////////////////////////////

//PRESENTATIONCONTROL-DIALOGS//////////////////////////////////////////////////////////////////////
void ApplicationUI::onSaveFailed() {
    m_Dialog = new bb::system::SystemDialog("OK");
    m_Dialog->setTitle("Failed!");
    m_Dialog->setBody("Your save request failed!");
    m_Dialog->show();
    QObject::connect(m_Dialog, SIGNAL(finished(bb::system::SystemUiResult::Type)), this, SLOT(onDialogFinished(bb::system::SystemUiResult::Type)));
}
void ApplicationUI::onSaveSucessfull(QString title) {
    m_Dialog = new bb::system::SystemDialog("OK");
    m_Dialog->setTitle("Sucessfull!");
    m_Dialog->setBody("Presentation "+title+" was sucessfully saved!");
    m_Dialog->show();
    QObject::connect(m_Dialog, SIGNAL(finished(bb::system::SystemUiResult::Type)), this, SLOT(onDialogFinished(bb::system::SystemUiResult::Type)));
}
void ApplicationUI::onLoadFailed() {
    m_Dialog = new bb::system::SystemDialog("OK");
    m_Dialog->setTitle("Failed!");
    m_Dialog->setBody("Your load request failed!");
    m_Dialog->show();
    QObject::connect(m_Dialog, SIGNAL(finished(bb::system::SystemUiResult::Type)), this, SLOT(onDialogFinished(bb::system::SystemUiResult::Type)));
}
void ApplicationUI::onLoadSucessfull(QString title) {
    m_Dialog = new bb::system::SystemDialog("OK");
    m_Dialog->setTitle("Sucessfull!");
    m_Dialog->setBody("Presentation "+title+" was sucessfully loaded!");
    m_Dialog->show();
    QObject::connect(m_Dialog, SIGNAL(finished(bb::system::SystemUiResult::Type)), this, SLOT(onDialogFinished(bb::system::SystemUiResult::Type)));
}
//END PRESENTATIONCONTROL-DIALOGS/////////////////////////////////////////////////////////////////////

//NETWORKCONTROL-DIALOGS//////////////////////////////////////////////////////////////////////////////
void ApplicationUI::onStarted() {
    m_toast->setBody("Server started!");
    m_toast->setPosition(SystemUiPosition::MiddleCenter);
    m_toast->show();
}
void ApplicationUI::onClientConnected() {
    m_toast->setBody("Client connected!");
    m_toast->setPosition(SystemUiPosition::MiddleCenter);
    m_toast->show();
}
void ApplicationUI::onClientVerified() {
    m_Dialog = new bb::system::SystemDialog();
    m_Dialog->setTitle("Client verified!");
    m_Dialog->setBody("A Client successfully joined your presentation!");
    m_Dialog->show();
    QObject::connect(m_Dialog, SIGNAL(finished(bb::system::SystemUiResult::Type)), this, SLOT(onDialogFinished(bb::system::SystemUiResult::Type)));
}
void ApplicationUI::onClientLeft() {
    m_toast->setBody("Client left!");
    m_toast->setPosition(SystemUiPosition::MiddleCenter);
    m_toast->show();
}
void ApplicationUI::onClosed() {
    m_toast->setBody("Presentation aborted!");
    m_toast->setPosition(SystemUiPosition::MiddleCenter);
    m_toast->show();
}

void ApplicationUI::onHostFound() {

}
void ApplicationUI::onConnectionSuccessfull() {
    m_toast->setBody("Connected!");
    m_toast->setPosition(SystemUiPosition::MiddleCenter);
    m_toast->show();
}
void ApplicationUI::onLoggingIn() {
    m_Dialog = new bb::system::SystemDialog();
    m_Dialog->setTitle("Logging in!");
    m_Dialog->setBody("The host is validating your identity!");
    m_Dialog->show();
    QObject::connect(m_Dialog, SIGNAL(finished(bb::system::SystemUiResult::Type)), this, SLOT(onDialogFinished(bb::system::SystemUiResult::Type)));
}
void ApplicationUI::onConnectionAccepted() {
    m_Dialog = new bb::system::SystemDialog();
    m_Dialog->setTitle("Accepted!");
    m_Dialog->setBody("You successfully logged in!");
    m_Dialog->show();
    QObject::connect(m_Dialog, SIGNAL(finished(bb::system::SystemUiResult::Type)), this, SLOT(onDialogFinished(bb::system::SystemUiResult::Type)));
}
void ApplicationUI::onPresentationReady() {
    m_Dialog = new bb::system::SystemDialog();
    m_Dialog->setTitle("Presentation ready!");
    m_Dialog->setBody("You successfully downloaded the presentation from the host!");
    m_Dialog->show();
    QObject::connect(m_Dialog, SIGNAL(finished(bb::system::SystemUiResult::Type)), this, SLOT(onDialogFinished(bb::system::SystemUiResult::Type)));
}
void ApplicationUI::onDisconnected() {
    m_Dialog = new bb::system::SystemDialog();
    m_Dialog->setTitle("Disconnected!");
    m_Dialog->setBody("You disconnected from the host!");
    m_Dialog->show();
    QObject::connect(m_Dialog, SIGNAL(finished(bb::system::SystemUiResult::Type)), this, SLOT(onDialogFinished(bb::system::SystemUiResult::Type)));
}
//END NETWORKCONTROL-DIALOGS//////////////////////////////////////////////////////////////////////////////

void ApplicationUI::onDialogFinished(bb::system::SystemUiResult::Type type) {
    m_Dialog->deleteLater();
}
