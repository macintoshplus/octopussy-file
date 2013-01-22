#ifndef OFFILE_H
#define OFFILE_H

#include <QObject>

#define OF_SAME_NAME 1
#define OF_SAME_DATE 2
#define OF_SAME_SIZE 4

struct OFSameFile {
    QString path;
    int type;
};

class OFFile : public QObject
{
    Q_OBJECT
    QString path;
    bool compared;
    QList<OFSameFile> sameList;
public:
    explicit OFFile(QObject *parent = 0);
    void addSame(QString path, int same);
    void setPath(QString path);
    QString getPath();
    void setCompared();
    bool isCompared();
    
signals:
    
public slots:
    
};

#endif // OFFILE_H
