#include "offile.h"

OFFile::OFFile(QObject *parent) :
    QObject(parent)
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
                //Mise � jour de same
                this->sameList.at(i).type=same;
                return;
            }
        }
    }
    //Si inexistant ou liste vide, ajout du fichier
    OFSameFile s=new OFSameFile();
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