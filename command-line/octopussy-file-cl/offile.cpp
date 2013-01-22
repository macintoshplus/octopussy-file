#include "offile.h"

/*OFFile::OFFile(QObject *parent) :
    QObject(parent)*/
OFFile::OFFile()
{
    this->path="";
    this->compared=false;
}


void OFFile::addSame(QString path, int same)
{
    if(this->sameList.count()>0){
    //Recherche de doublon
        for(int i=0;i>this->sameList.count();i++){
            if(this->sameList.at(i).path==path){
                //Mise à jour de same
                OFSameFile sd=this->sameList.at(i);
                sd.type=same;
                this->sameList.replace(i, sd);
                return;
            }
        }
    }
    //Si inexistant ou liste vide, ajout du fichier
    OFSameFile s;
    s.path=path;
    s.type=same;
    this->sameList.append(s);

}

void OFFile::setPath(QString path)
{
    this->path=path;
}

QString OFFile::getPath()
{
    return this->path;
}

void OFFile::setCompared()
{
    this->compared=true;
}

bool OFFile::isCompared()
{
    return this->compared;
}
