#ifndef OFCOMPARMANAGER_H
#define OFCOMPARMANAGER_H

#include <QObject>
#include <QtCore>
#include "offile.h"
#include "ofcompar.h"
#include <iostream>

using namespace std;

class OFComparManager : public QObject
{
    Q_OBJECT
    QList<OFFile> filesFind; //Base des fichiers dans lequel rechercher
    QQueue<OFFile> files; //Fichier à rechercher
    int totalATraiter;
    QList<OFFile> comparedFiles; //Liste des fichiers comparés
    QReadWriteLock rLocker;
    QList<OFCompar*> threadList; //Liste des threads
    int threadTerminatedCount;

public:
    explicit OFComparManager(QObject *parent = 0);
    void initThread(int nbProc = 1);
    OFFile getFindAt(int i);
    void addFiles(OFFile f);
    void addFindFiles(OFFile f);
    int getFindMax();
    void launchThread();
    void checkEndCompar();

signals:
    
public slots:
    void threadTerminated();
    void fileCompared();
    
};

#endif // OFCOMPARMANAGER_H
