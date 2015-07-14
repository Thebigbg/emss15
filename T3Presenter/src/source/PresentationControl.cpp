#include "PresentationControl.hpp"
#include <bb/system/SystemDialog>
#include <bb/cascades/Application>
#include <bb/cascades/ArrayDataModel>

PresentationControl::PresentationControl() : QObject() {
    // prepare the presentation
    m_Presentation = new Presentation();
    // setting current page
    currentPage = 0;
    //creating directory
    dir.mkdir("shared/documents/T3Presenter");
    //
    saved = false;
}
Presentation* PresentationControl::getPresentation() {
    return m_Presentation;
}
//FILEACCESS//////////////////////////////////////////////////////////////////////
void PresentationControl::loadFiles(QStringList path) {
    // adding files to presentation
    for (int i = 0; i < path.length(); i++) {
        m_Presentation->add(path[i]);
    }
    saved = false;
    emit presentationChanged();
}

void PresentationControl::load(QString path) {
    m_Presentation->clear();
    //load path of Images and Presentation title from a TXT
    QFile file(path);
    if(file.open(QIODevice::ReadOnly)) {
        QTextStream stream(&file);

        // reading the file
        QString all = stream.readAll();

        //split the list
        QStringList list = all.split("|", QString::SkipEmptyParts);

        // pop the title
        QString title = list.at(0);
        m_Presentation->setTitle(title);
        list.removeAt(0);

        // inserting paths
        for(int i = 0; i < list.length(); i++) {
            m_Presentation->add(list.at(i));
        }

        emit loadSucessfull(m_Presentation->getTitle());
        emit presentationChanged();
        saved = true;
    }else {
        emit loadFailed();
    }
}

void PresentationControl::save(QString title) {
    // creating directory
    dir.mkdir("shared/documents/T3Presenter/"+title);
    // creating presentation file
    QFile file("shared/documents/T3Presenter/"+title+"/"+title+".txt");

    //save path of Images and Presentation title in a TXT
    if(file.open(QIODevice::WriteOnly)) {
        QTextStream stream(&file);
        stream << "|"+title;
        for(int i = 0; i < m_Presentation->size(); i++) {
            stream << "|" << m_Presentation->get(i);
        }
        saved = true;
        emit saveSucessfull(title);
    }else {
        emit saveFailed();
    }
}

bool PresentationControl::isSaved() {
    return saved;
}

//SIGNALS//////////////////////////////////////////////////////////////////////////
void PresentationControl::onPresentationChanged() {
    qDebug() << "Presentation changed";
    emit presentationChanged();
}

//CURRENTPAGE//////////////////////////////////////////////////////////////////////
QString PresentationControl::getCurrentPage() {
    if(!isEmpty()) {
        return m_Presentation->get(currentPage);
    }
    return "";
}
qint32 PresentationControl::getCurrentPageNumber() {
    return currentPage;
}
void PresentationControl::setCurrentPageNumber(qint32 page) {
    currentPage = page;
    emit currentPageChanged();
}

void PresentationControl::onCurrenPageChanged(qint64 page) {
    currentPage = page;
    qDebug() << "Current page changed";
    emit presentationChanged();
}

//PRESENTATION//////////////////////////////////////////////////////////////////////
QString PresentationControl::getTitle() {
    return m_Presentation->getTitle();
}
QString PresentationControl::get(qint32 page) {
    return m_Presentation->get(page);
}
qint32 PresentationControl::getNumberOfPages() {
    return m_Presentation->size();
}
void PresentationControl::setTitle(QString title) {
    m_Presentation->setTitle(title);
    saved = false;
    emit presentationChanged();
}
void PresentationControl::clear() {
    m_Presentation->clear();
    emit presentationChanged();
}
bool PresentationControl::isEmpty() {
    return m_Presentation->isEmpty();
}



