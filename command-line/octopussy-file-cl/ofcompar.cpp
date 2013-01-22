#include "ofcompar.h"

OFCompar::OFCompar(QObject *parent) :
    QThread(parent)
{
}

void OFCompar::addFileFind(OFFile f){
    QMutexLocker locker(&mutex);
    this->compare.enqueue();
    if(!isRunning()) start();
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

        QFileInfo fi(f.getPath());
        if(!fi.exists()){
            f.setCompared();
            emit fileCompared(f);
        }
        int max = this->parent()->getFindMax();
        for(int i;i<max;i++){
            int sameFile=0;
            OFFile fF = this->parent()->getFindAt(i);
            QFileInfo fiF(fF);
            if(!fiF.exists()) continue;
            if(fiF.fileName()==fi.fileName()){
                sameFile=sameFile|OF_SAME_NAME;
            }
            if(fiF.size()==fi.size()){
                sameFile=sameFile|OF_SAME_SIZE;
            }
            if(fiF.lastModified()==fi.lastModified()){
                sameFile=sameFile|OF_SAME_DATE;
            }
            //Ajoute le fichier comme semblable si
            // supérieur à zéro et non paire.
            if(sameFile>0 && sameFile%2!=0)
            f.addSame(fF.path,sameFile);
        }
        //Fichier traité
        emit fileCompared(f);
    }


}
