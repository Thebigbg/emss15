#ifndef PRESENTATION_HPP_
#define PRESENTATION_HPP_

#include <QObject>
#include <QStringList>
/*
 * Class that holds the paths of content
 */
class Presentation : public QObject {
    Q_OBJECT
    public:
        /*
         * (De/)Constructor
         */
        Presentation(QString path);
        Presentation();
        virtual ~Presentation() {};

        /*
         * Capsuling List access methods
         */
        void add(QString path);
        void clear();
        bool isEmpty();
        QByteArray toByteArray();
        qint32 size();
        QString get(qint32 page);
        QByteArray getBuffer(int i);

        /*
         * parameter access: title
         */
        QString getTitle();
        void setTitle(QString title);



    private:
        QStringList pathList;
        QString title;

    signals:
        /*
         * TODO for emittation when content is unavailable or changed
         */
        void contentChanged();
};

#endif /* PRESENTATION_HPP_ */
