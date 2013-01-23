#ifndef OFCOMPAR_H
#define OFCOMPAR_H

#include <QThread>
#include <QtCore>
#include "offile.h"
#include <iostream>

using namespace std;

class OFCompar : public QThread
{
    Q_OBJECT
    QMutex mutex;
    QQueue<OFFile> compare;
    QQueue<OFFile> fichierComparer;
    QReadWriteLock rLock;
    int tNumber;

public:
    explicit OFCompar(QObject *parent = 0);
    void addFileFind(OFFile f);
    OFFile getLastCompared();
    bool hasLastCompared();
    void setNumber(int i);
    int getNumber();

signals:
    void fileCompared();

public slots:

protected:
    void run();
};

#endif // OFCOMPAR_H
