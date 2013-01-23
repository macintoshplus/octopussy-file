#include "ofdiscovermanager.h"
#include <iostream>

using namespace std;

OFDiscoverManager::OFDiscoverManager(QObject *parent) :
    QObject(parent)
{
    t.setInterval(50);
    t.stop();
    connect(&t, SIGNAL(timeout()), this, SLOT(updateState()));
    connect(&left, SIGNAL(finished()), this, SLOT(leftFinished()));
    connect(&right, SIGNAL(finished()), this, SLOT(rightFinished()));
}

void OFDiscoverManager::setPathLeft(QString path){
    this->pathLeft=path;
    if(!this->left.isRunning()) this->left.setPath(path);
}

void OFDiscoverManager::setPathRight(QString path){
    this->pathRight=path;
    if(!this->right.isRunning()) this->right.setPath(path);
}

void OFDiscoverManager::launchDiscover(){
    this->left.start();
    this->right.start();
    t.start();
}

void OFDiscoverManager::updateState(){
    int countL,countR;
    countL=left.getCountFile();
    countR=right.getCountFile();
    system("cls");
    cout << "Nombre d'élément dans le dossier source : "<<countL<<endl<<"Nombre d'élément dans le dossier de recherche : "<<countR<<endl;
    if(left.isFinished() && right.isFinished()){
        t.stop();
        cout<<"La recherche est terminée, la comparaison va commencer..."<<endl;
        //exit(0);
        //Transfer des fichiers
        cout<<"Transfert des fichiers à rechercher..."<<endl;
        QList<OFFile> fLeft = left.getFileList();
        foreach(OFFile f1Left,fLeft){
            cManager.addFiles(f1Left);
        }

        cout<<"Transfert des fichiers de comparaison..."<<endl;
        QList<OFFile> fRight = right.getFileList();
        foreach(OFFile f1Right,fRight){
            cManager.addFindFiles(f1Right);
        }
        cout<<"Fin des transferts, début de la comparaison..."<<endl;
        //Langement du traitement
        cManager.launchThread();
    }
}

void OFDiscoverManager::leftFinished(){
    cout<<"La liste des fichiers à rechercher est terminée. Il y a " << left.getCountFile() << " fichier(s)."<<endl;
}

void OFDiscoverManager::rightFinished(){
    cout<<"La liste des fichiers cibles est terminée. Il y a " << right.getCountFile() << " fichier(s)."<<endl;
}

void OFDiscoverManager::setProcCount(int proc){
    this->nbProc=proc;
    this->cManager.initThread(proc);
}
