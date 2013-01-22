#ifndef OFDISCOVERMANAGER_H
#define OFDISCOVERMANAGER_H

#include <QObject>
#include <QtCore>
#include "ofdiscover.h"
#include "offile.h"

class OFDiscoverManager : public QObject
{
    Q_OBJECT
    OFDiscover left;
    OFDiscover right;
    QString pathLeft;
    QString pathRight;
    QTimer t;

public:
    explicit OFDiscoverManager(QObject *parent = 0);
    void setPathLeft(QString path);
    void setPathRight(QString path);
    void launchDiscover();

signals:
    
public slots:
    void updateState();
    void leftFinished();
    void rightFinished();
    
};

#endif // OFDISCOVERMANAGER_H