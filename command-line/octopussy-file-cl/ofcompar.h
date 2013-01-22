#ifndef OFCOMPAR_H
#define OFCOMPAR_H

#include <QThread>
#include <QtCore>
#include "offile.h"

class OFCompar : public QThread
{
    Q_OBJECT
    QMutex mutex;
    QQueue<OFFile> compare;

public:
    explicit OFCompar(QObject *parent = 0);
    void addFileFind(OFFile f);

signals:
    void fileCompared(OFFile f);

public slots:

protected:
    void run();
};

#endif // OFCOMPAR_H
