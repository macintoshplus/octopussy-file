#include <QCoreApplication>
#include <QtCore>
#include <iostream>
#include "ofdiscovermanager.h"

using namespace std;

void help(QString s){
    cout << "Octopussy File" << endl;
    cout << "Ecrit par Jean-Baptiste Nahan.\t\t22 Janvier 2013" << endl << endl;
    cout << "Ce logiciel est livré \"TEL QUEL\". Vous l'utilisez à vos risques et périls." << endl << endl;
    //QString s(app);
    QFileInfo i(s);
    cout << i.fileName().toStdString() << " -h -d -f -c:d|n|s -l path -r path" << endl << endl;
    cout << "-h\tAffiche cette aide." << endl;
    cout << "-d\tCompare uniquement les dossiers. Cette option est activée par défaut." << endl;
    cout << "-f\tCompare uniquement les fichiers. Cette option est activée par défaut." << endl;
    cout << "-c:\tCritère de comparaison:" << endl;
    cout << "    d\t  Par date de modification" << endl;
    cout << "    n\t  Par nom de fichier" << endl;
    cout << "    s\t  Par taille de fichier" << endl << "  \tPar défaut, il compare avec tous les critères possibles."<< endl;
    cout << "-l\tDossier contenant les fichiers à rechercher." << endl;
    cout << "-r\tDossier dans lequel il faut chercher les fichiers." << endl;
    cout << endl << "Veuillez tenir compte que les traitements réalisée peuvent être très long et par conséquent risque de bloquer la machine." << endl;

}







int main(int argc, char *argv[])
{

    cout << "*** NB Arg : " << argc << endl << endl;
    /*if(argc>1 && QString("%1").arg(argv[1])=="-h"){
        help(argv[0]);
        exit(0);
    }*/

    QCoreApplication a(argc, argv);

    QStringList args=a.arguments();

    if (args.count()>1 && args.contains("-h")){
        help(args.at(0));
        return 0;
    }

    if(!args.contains("-l")){
        cerr << "argument -l manquant !" << endl;
        help(args.at(0));
        return 1;
    }

    if(!args.contains("-r")){
        cerr << "argument -r manquant !" << endl;
        help(args.at(0));
        return 1;
    }

    QString pathL=args.at(args.indexOf("-l")+1);
    QString pathR=args.at(args.indexOf("-r")+1);

    if(pathL==pathR){
        cerr << "Les deux chemins sont identiques. Traitement impossible!" << endl;
        return 1;
    }

    if(!QFileInfo(pathL).exists()){
        cerr << "Le chemin du dossier source est inexistant : " << pathL.toStdString() << endl;
        return 1;
    }

    if(!QFileInfo(pathR).exists()){
        cerr << "Le chemin du dossier de recherche est inexistant : " << pathR.toStdString() << endl;
        return 1;
    }

    if(pathL.startsWith(pathR, Qt::CaseInsensitive)){
        cerr << "Le dossier source ne peut pas être un parent du dossier de recherche!" << endl;
        return 1;
    }

    if(pathR.startsWith(pathL, Qt::CaseInsensitive)){
        cerr << "Le dossier de recherche ne peut pas être un parent du dossier source." << endl;
        return 1;
    }

    QString nbproc="0";
    QString user="None";
    QString proc="None";
    QString arch="None";
    foreach (QString env, QProcess::systemEnvironment())
    {
        //qDebug()<<env;
        if(env.startsWith("NUMBER_OF_PROCESSORS=")) nbproc=env.split("=").at(1);
        if(env.startsWith("PROCESSOR_IDENTIFIER=")) proc=env.split("=").at(1);
        if(env.startsWith("PROCESSOR_ARCHITECTURE=")) arch=env.split("=").at(1);
        if(env.startsWith("USERNAME=")) user=env.split("=").at(1);
    }
    //nbproc="1";
    if(nbproc.toInt()==0){
        cerr<<"Impossible de déterminer le nombre de processeur..."<<endl;
        return 1;
    }
    cout<<"Votre ordinateur contien "<<qPrintable(nbproc)<<" processeur(s). Ils seront utilisés pour la recherche des fichiers."<<endl;

    OFDiscoverManager m;
    m.setProcCount(nbproc.toInt());

    cout<<"Appuyez sur ENTREE pour continuer..."<<endl;
    cout.flush();
    cin.ignore(100000,'\n');


    m.setPathLeft(pathL);
    m.setPathRight(pathR);
    
    m.launchDiscover();

    //return 0;

    return a.exec();
}
