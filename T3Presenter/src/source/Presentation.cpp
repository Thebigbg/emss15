#include "Presentation.hpp"
#include <QTextStream>
#include <QFile>
#include <QDir>
#include <QBuffer>
#include <Qt/qimage.h>
/*
 * Class that holds the paths of content
 */
Presentation::Presentation() : QObject() {}

/*
 * Capsuling List access methods
 */
void Presentation::add(QString imgPath) {
    pathList.append(imgPath);
}

bool Presentation::isEmpty() {
    return pathList.empty();
}

void Presentation::clear() {
    title = "";
    pathList.clear();
}

QByteArray Presentation::getBuffer(int i) {
    QByteArray ba;              // Construct a QByteArray object
    QBuffer buffer(&ba);        // Construct a QBuffer object using the QbyteArray
    QImage image(pathList.at(i));
    image.save(&buffer, "JPG"); // Save the QImage data into the QBuffer
    return ba;
}

qint32 Presentation::size() {
    return pathList.length();
}

QString Presentation::get(qint32 i) {
    return pathList.at(i);
}
/*
 * parameter access: title
 */
QString Presentation::getTitle() {
    return title;
}
void Presentation::setTitle(QString title) {
    this->title = title;
}
