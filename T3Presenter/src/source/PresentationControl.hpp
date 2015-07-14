/*
 * PresentationController.hpp
 *
 *  Created on: 07.05.2015
 *      Author: Philip
 */

#ifndef PRESENTATIONCONTROL_HPP_
#define PRESENTATIONCONTROL_HPP_

#include "Presentation.hpp"
#include <bb/system/SystemDialog>
#include <bb/cascades/ArrayDataModel>

/*
 * Provides GUI access for the Presentation Class
 */
class PresentationControl : public QObject {
    Q_OBJECT
    public:
        PresentationControl();
        virtual ~PresentationControl() {};

        Presentation* getPresentation();

        /*
         * file access
         */
        Presentation* m_Presentation;
        // load a QStringList
        Q_INVOKABLE void loadFiles(QStringList path);
        // load a presentation from a presentation-file (.txt by now)
        Q_INVOKABLE void load(QString path);
        // save the current list in a presentation-file (.txt by now)
        Q_INVOKABLE void save(QString title);
        // data loss preventation
        Q_INVOKABLE bool isSaved();

        /*
         * current page var for GUI
         */
        Q_INVOKABLE qint32 getCurrentPageNumber();
        Q_INVOKABLE void setCurrentPageNumber(qint32 number);
        Q_INVOKABLE QString getCurrentPage();

        /*
         * QML invokable presentation methods
         */
        Q_INVOKABLE QString get(qint32 page);
        Q_INVOKABLE QString getTitle();
        Q_INVOKABLE void setTitle(QString title);
        Q_INVOKABLE qint32 getNumberOfPages();
        Q_INVOKABLE void clear();
        Q_INVOKABLE bool isEmpty();

    signals:
        /*
         * file access signals
         */
        void loadFailed(void);
        void loadSucessfull(QString title);
        void saveFailed(void);
        void saveSucessfull(QString title);

        /*
         * signals for GUI
         */
        void presentationChanged();
        void currentPageChanged();

    public slots:
        void onPresentationChanged();
        void onCurrenPageChanged(qint64);
    private:

        qint32 currentPage;
        bool saved;
        QDir dir;
};

#endif /* PRESENTATIONCONTROLLER_HPP_ */
