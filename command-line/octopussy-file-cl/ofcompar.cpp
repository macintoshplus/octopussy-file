#include "ofcompar.h"
#include "ofcomparmanager.h"

OFCompar::OFCompar(QObject *parent) :
    QThread(parent)
{
    this->setTerminationEnabled(true);
}

void OFCompar::setNumber(int i){
    QWriteLocker locker(&rLock);
    this->tNumber=i;
}

int OFCompar::getNumber(){
    QReadLocker locker(&rLock);
    return this->tNumber;
}

void OFCompar::addFileFind(OFFile f){
    QMutexLocker locker(&mutex);
    this->compare.enqueue(f);
    if(!isRunning()) start();
}

OFFile OFCompar::getLastCompared(){
    rLock.lockForWrite();
    OFFile f=fichierComparer.dequeue();
    rLock.unlock();
    return f;
}

bool OFCompar::hasLastCompared(){
    QReadLocker lok(&rLock);
    return (!fichierComparer.isEmpty());
}

void OFCompar::run(){
    OFFile f;
    forever{
        mutex.lock();
        if(compare.isEmpty()){
            mutex.unlock();
            break;
        }
        f=compare.dequeue();
        mutex.unlock();
        //cout<<"Fichier en cours de traitement : "<<qPrintable(f.baseName)<<endl;
        //QFileInfo fi(f.getPath());
        if(!f.exist){
            f.setCompared();
            rLock.lockForWrite();
            fichierComparer.enqueue(f);
            rLock.unlock();
            //cout << "Thread "<< this->tNumber <<" : Fin comparaison - abs"<< endl;
            emit fileCompared();
        }
        QObject * obj = this->parent();
        OFComparManager * objCasted = qobject_cast<OFComparManager*>(obj);
        if(!objCasted) cerr<<"************************************** CAST ERROR ***************************************";
        int max = objCasted->getFindMax();
        //cout<<"Max base find : "<<max<<endl;
        for(int i=0;i<max;i++){
            //cout<<"I="<<i;
            int sameFile=0;
            OFFile fF = objCasted->getFindAt(i);
            //cout<<"Comparer à : "<<qPrintable(fF.baseName);
            //QFileInfo fiF(fF.getPath());
            if(!fF.exist){
                cout<<"Existe pas !"<<endl;
                continue;
            }
            //cout<<"fF="<<qPrintable(fF.baseName)<<" f="<<qPrintable(f.baseName)<<endl;
            if(fF.baseName==f.baseName){
                sameFile=sameFile|OF_SAME_NAME;
            }
            if(fF.size==f.size){
                sameFile=sameFile|OF_SAME_SIZE;
            }
            if(fF.modify==f.modify){
                sameFile=sameFile|OF_SAME_DATE;
            }
            //Ajoute le fichier comme semblable si
            // supérieur à zéro et non paire.
            if(sameFile>0 && sameFile%2!=0)
            f.addSame(fF.getPath(),sameFile);
        }
        //cout<<"Fin compare !"<<endl;
        //Fichier traité
        f.setCompared();
        rLock.lockForWrite();
        fichierComparer.enqueue(f);
        rLock.unlock();
        //cout << "Thread "<< this->tNumber <<" : Fin comparaison"<< endl;
        emit fileCompared();
    }


}
