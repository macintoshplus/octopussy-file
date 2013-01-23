#ifndef OFFILE_H
#define OFFILE_H

#include <QtCore>

#define OF_SAME_NAME 1
#define OF_SAME_DATE 2
#define OF_SAME_SIZE 4

struct OFSameFile {
    QString path;
    int type;
};


class OFFile// : public QObject
{
    //Q_OBJECT
    QString path;
    bool compared;
    QList<OFSameFile> sameList;
public:
    //explicit OFFile(QObject *parent = 0);
    explicit OFFile();
    void addSame(QString path, int same);
    int sameCount();
    QList<OFSameFile> getSame();
    void setPath(QString path);
    QString getPath();
    void setCompared();
    bool isCompared();
    
    QString baseName;
    QDateTime modify;
    qint64 size;
    bool exist;

};

//typedef QObject OFFile;
//qRegisterMetaType<OFFile>("OFFile");

#endif // OFFILE_H
