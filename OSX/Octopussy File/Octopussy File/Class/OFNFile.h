//
//  OFNFile.h
//  Octopussy File
//
//  Created by Jean-Baptiste Nahan on 23/01/13.
//  Copyright (c) 2013 Jean-Baptiste Nahan. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

#define OF_SAME_NAME 1
#define OF_SAME_DATE 2
#define OF_SAME_SIZE 4

@interface OFSameFile : NSObject 
    @property (retain) NSString * path;
    @property (assign) int type;
@end



@interface OFNFile : NSObject

@property (retain) NSString * path;
@property (retain) NSMutableArray * sameList;
@property (assign) bool compared;

- (void)addSame:(NSString *)pathF withSameMode:(int)same;

@end