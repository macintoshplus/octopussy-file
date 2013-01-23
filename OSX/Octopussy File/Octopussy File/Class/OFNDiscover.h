//
//  OFNDiscover.h
//  Octopussy File
//
//  Created by Jean-Baptiste Nahan on 23/01/13.
//  Copyright (c) 2013 Jean-Baptiste Nahan. All rights reserved.
//

#import <Foundation/Foundation.h>
/*
 
 class OFDiscover : public QThread
 {
 Q_OBJECT
 volatile bool stopped;
 QMutex mutex;
 QQueue<QString> pathFolder;
 QList<OFFile> file;
 bool discoveFolder;
 bool discoveFile;
 
 public:
 explicit OFDiscover(QObject *parent = 0);
 void stop();
 void setPath(QString path);
 int getCountFile();
 void setNotDiscodeFile();
 void setNotDiscodeFolder();
 QList<OFFile> getFileList();
 
 protected:
 void run();

 */



@interface OFNDiscover : NSThread

@property (assign) bool discoveFolder;
@property (assign) bool discoveFile;
@property (retain) NSMutableArray * files;

- (void)stop;
- (void)setPath:(NSString*) path;
- (NSUInteger)getCountFile;

@end


bool stopped;
NSLock * lock;
NSMutableArray * pathFolder;
