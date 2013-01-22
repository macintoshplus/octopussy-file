#include <QCoreApplication>
#include <QtCore>
#include <iostream>

using namespace std;

void help(char * app){
    cout << "Octopussy File" << endl;
    cout << "Ecrit par Jean-Baptiste Nahan.\t\t22 Janvier 2013" << endl << endl;
    cout << "Ce logiciel est livré \"TEL QUEL\". Vous l'utilisez à vos risques et périls." << endl << endl;
    QString s(app);
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
    if(argc>1 && QString("%1").arg(argv[1])=="-h"){
        help(argv[0]);
        exit(0);
    }

    QCoreApplication a(argc, argv);
    
    return a.exec();
}
