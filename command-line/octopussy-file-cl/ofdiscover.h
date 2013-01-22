#ifndef OFDISCOVER_H
#define OFDISCOVER_H

#include <QtCore>
#include <QThread>
#include "offile.h"

class OFDiscover : public QThread
{
    Q_OBJECT
    volatile bool stopped;
    QMutex mutex;
    QQueue<QString> pathFolder;
    QList<OFFile> file;
    bool discoveFolder;
    bool discoveFile;

public:
    explicit OFDiscover(QObject *parent = 0);
    void stop();
    void setPath(QString path);
    int getCountFile();
    void setNotDiscodeFile();
    void setNotDiscodeFolder();

protected:
    void run();

signals:
    
public slots:
    
};

#endif // OFDISCOVER_H
