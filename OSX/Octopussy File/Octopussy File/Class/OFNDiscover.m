//
//  OFNDiscover.m
//  Octopussy File
//
//  Created by Jean-Baptiste Nahan on 23/01/13.
//  Copyright (c) 2013 Jean-Baptiste Nahan. All rights reserved.
//

#import "OFNDiscover.h"

@implementation OFNDiscover

- (id)init{
    if(self = [super init]){
    lock = [[NSLock alloc] init];
    pathFolder = [[NSMutableArray alloc] init];
    self.files = [[NSMutableArray alloc] init];
    }
    return self;
}

- (void)stop{

}
- (void)setPath:(NSString*) path{
    [lock lock];
    [pathFolder addObject:path];
    [lock unlock];
}
- (NSUInteger)getCountFile{
    [lock lock];
    NSUInteger val = [self.files count];
    [lock unlock];
    return val;
}


@end
