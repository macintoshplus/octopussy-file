#include "ofdiscover.h"
#include <iostream>

using namespace std;

OFDiscover::OFDiscover(QObject *parent) :
    QThread(parent)
{
    this->stopped=false;
    this->discoveFile=true;
    this->discoveFolder=true;
}

void OFDiscover::setPath(QString path){
    QMutexLocker locker(&mutex);
    this->pathFolder.enqueue(path);
}

void OFDiscover::stop(){
    QMutexLocker locker(&mutex);
    this->stopped=true;
}
int OFDiscover::getCountFile(){
    QMutexLocker locker(&mutex);
    return this->file.count();
}

void OFDiscover::setNotDiscodeFile(){
    QMutexLocker locker(&mutex);
    this->discoveFile=false;
}
void OFDiscover::setNotDiscodeFolder(){
    QMutexLocker locker(&mutex);
    this->discoveFolder=false;
}

void OFDiscover::run(){
    forever{

        this->mutex.lock();
        if(stopped){
            stopped=false;
            this->mutex.unlock();
            cout << "Stopped Discover ! "<< this->currentThread()<<endl;
            break;
        }
        if(this->pathFolder.isEmpty()){
            this->mutex.unlock();
            cout << "End Discover ! "<< this->currentThread()<<endl;
            break;
        }
        //Traitement d'un dossier
        QString p=this->pathFolder.dequeue();
        mutex.unlock();
        cout << "Tratement chemin : " << p.toStdString();
        //Parcour du dossier
        QDir dir(p);

        mutex.lock();
        if(discoveFile)
        foreach(QString f, dir.entryList(QDir::Files)){
            mutex.unlock();
            OFFile off();
            off.setPath(QFileInfo(dir,f).absoluteFilePath());
            this->mutex.lock();
            this->file.append(off);
            this->mutex.unlock();
        }
        mutex.unlock();
        //Ajoute les dossiers dans la liste des dossiers à traiter
        foreach(QStrinf f, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)){
            this->setPath(QFileInfo(dir,f).absoluteFilePath());
            mutex.lock();
            if(discoveFolder){ //ajoute les dossiers à la listes des fichiers à comparer
                mutex.unlock();
                OFFile off();
                off.setPath(QFileInfo(dir,f).absoluteFilePath());
                this->mutex.lock();
                this->file.append(off);
                this->mutex.unlock();
            }
            mutex.unlock();
        }
    }
    this->stopped=false;
}
