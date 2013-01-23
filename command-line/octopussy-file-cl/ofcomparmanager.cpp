#include "ofcomparmanager.h"



OFComparManager::OFComparManager(QObject *parent) :
    QObject(parent)
{
    totalATraiter=0;
}

void OFComparManager::initThread(int nbProc){
    if(this->threadList.count()>0){
        cerr << "Red�finition du nombre de processeurs..."<<endl;
        foreach(OFCompar * f, this->threadList){
            if(f->isRunning()){
                cerr << "Attente de la fin d'un thread..."<<endl;
                f->terminate();
                f->wait();
            }
            //Disconnect signal
            disconnect(f, SIGNAL(finished()), this, SLOT(threadTerminated()));
        }
        this->threadList.clear();
    }
    cout << "Initialisation des Threads..."<<endl;
    for(int i=0;i<nbProc;i++){
        cout << "Initialisation du Threads Numero "<<i<<"..."<<endl;
        OFCompar * t = new OFCompar(this);
        t->setNumber(i);
        connect(t, SIGNAL(finished()), this, SLOT(threadTerminated()));
        //connect(t, SIGNAL(fileCompared()), this, SLOT(fileCompared()));
        threadList.append(t);
    }
    cout << "Fin de l'initialisation des Threads..."<<endl;
}

OFFile OFComparManager::getFindAt(int i)
{
    QReadLocker loker(&rLocker);
    return this->filesFind.at(i);
}
void OFComparManager::addFiles(OFFile f)
{
    QWriteLocker loker(&rLocker);
    this->files.enqueue(f);
    totalATraiter=files.count();
}
void OFComparManager::addFindFiles(OFFile f)
{
    QWriteLocker loker(&rLocker);
    this->filesFind.append(f);
}

int OFComparManager::getFindMax(){
    QReadLocker loker(&rLocker);
    return this->filesFind.count();
}


void OFComparManager::launchThread(){

    //Lance les comparaisons apr�s avoir v�rifi� que le thread avait au moins un fichier � trater.
    if(filesFind.isEmpty()){
        cerr << "-- PAS DE BASE DE COMPARAISON -- Impossible de lancer la comparaison."<<endl;
        return; //Pas de base de comparaison
    }

    if(files.isEmpty()){
        cerr << "Il n'y a pas de fichier � comparer..." << endl;
        return;
    }
    cout << "Il y a "<<files.count()<<"fichier a rechercher dans les "<<filesFind.count()<<" fichiers."<<endl;
    cout << "Il y a " << threadList.count() << " thread dans la liste..." << endl;
    int parT=(files.count()/threadList.count());
    cout << "Cela fait "<<parT<<" fichiers par thread"<<endl;
    threadTerminatedCount=threadList.count();
    for(int i=0;i<threadList.count();i++){
        OFCompar * t = threadList.at(i);
        for(int j =0; j<parT; j++){
            if(files.isEmpty()){
                cerr << "Il n'y a plus de fichier � comparer..." << endl;
                return;
            }
            rLocker.lockForWrite();
            OFFile f = files.dequeue();
            rLocker.unlock();

            //ajoute un fichier
            t->addFileFind(f);
        }
        if(i==threadList.count()-1 && files.count()>0){//Dernier fichier
            cout << "Il reste "<<files.count()<<" dans la liste des fichiers � traiter..."<<endl;
            rLocker.lockForWrite();
            OFFile f = files.dequeue();
            rLocker.unlock();

            //ajoute un fichier
            t->addFileFind(f);
        }
        //D�mare le thread
        t->start();
        threadTerminatedCount--;
        cout << "Lancement du thread "<< t->getNumber() <<"..." << endl;
    }


}

void OFComparManager::checkEndCompar(){
    if(threadTerminatedCount!=threadList.count()) return;

    foreach(OFCompar * emetteurCasted, threadList){
        cout <<"R�cup�ration du traitement du thread "<< emetteurCasted->getNumber() <<" ..." << endl;
        forever{
            if(!emetteurCasted->hasLastCompared()){
                cout<<"fin de la r�cup�ration du traitement du thread "<<emetteurCasted->getNumber()<<"."<<endl;
                break;
            }
            OFFile f = emetteurCasted->getLastCompared();
            rLocker.lockForWrite();
            comparedFiles.append(f);
            rLocker.unlock();
        }
        cout << " Total � traiter : "<< totalATraiter << " - Trait�s : "<< comparedFiles.count() << endl;
    }
    //tout est fini
    cout<<"Export du r�sultat :"<<endl<<endl;

    foreach(OFFile f, comparedFiles){
        int sameCnt = f.sameCount();
        cout<<qPrintable(f.getPath())<<"\t nbSame : "<<sameCnt<<endl;

        if(sameCnt>0){
            QList<OFSameFile> list= f.getSame();
            foreach(OFSameFile s,list ){
                cout << "Same : " <<qPrintable(s.path)<<"\tType : "<<s.type<<endl;
            }
        }


    }
    exit(0);
}

void OFComparManager::threadTerminated(){

    threadTerminatedCount++;
    this->checkEndCompar();
    /*
    QObject * emetteur = sender();

    // On caste le sender en ce que nous supposons qu'il soit
    OFCompar * emetteurCasted = qobject_cast<OFCompar*>(emetteur);

    // On teste la r�ussite du cast avant de proc�der � un quelconque acc�s dessus !
    if(emetteurCasted) //emetteurCasted vaut 0 si le cast � �chou�
    {
        //Si il n'y a plus de fichier, le thread est laisser stopp�
        //if(files.isEmpty()){
            cerr << "Fin du thread "<<emetteurCasted->getNumber()<<endl;//" : il n'y a plus de fichier � comparer..." << endl;
        threadTerminatedCount++;
        cout <<"R�cup�ration du traitement..." << endl;
        forever{
            if(!emetteurCasted->hasLastCompared()){
                cout<<"fin de la r�cup�ration du traitement du thread "<<emetteurCasted->getNumber()<<"."<<endl;
                break;
            }
            OFFile f = emetteurCasted->getLastCompared();
            rLocker.lockForWrite();
            comparedFiles.append(f);
            rLocker.unlock();
        }

        cout << " Total � traiter : "<< totalATraiter << " - Trait�s : "<< comparedFiles.count() << endl;
        this->checkEndCompar();
*/
        //    return;
        //}
         // Allimente la fille d'attente du thread
        /*rLocker.lockForWrite();
        OFFile f = files.dequeue();
        rLocker.unlock();

        emetteurCasted->addFileFind(f);*/
    //}

}

void OFComparManager::fileCompared(){
    //cout<<"R�cup�ration d'un fichier trait�..."<<endl;
    QObject * emetteur = sender();

    // On caste le sender en ce que nous supposons qu'il soit
    OFCompar * emetteurCasted = qobject_cast<OFCompar*>(emetteur);

    // On teste la r�ussite du cast avant de proc�der � un quelconque acc�s dessus !
    if(emetteurCasted) //emetteurCasted vaut 0 si le cast � �chou�
    {
        /*OFFile f = emetteurCasted->getLastCompared();
        rLocker.lockForWrite();
        comparedFiles.append(f);
        rLocker.unlock();

        system("CLS");
        rLocker.lockForRead();
        //cout << "T" << emetteurCasted->getNumber() << " Total � traiter : "<< totalATraiter << " - Trait�s : "<< comparedFiles.count() << endl;
        rLocker.unlock();
        for(int i=0;i<threadList.count();i++){
            OFCompar * t = threadList.at(i);
            cout << "Thread "<<t->getNumber() <<" est ";
            if(t->isRunning()) cout<<" en cours..."<<endl;
            else cout<<" termin�."<<endl;
        }*/
    }

}

