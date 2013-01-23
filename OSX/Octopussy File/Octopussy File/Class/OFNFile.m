//
//  OFNFile.m
//  Octopussy File
//
//  Created by Jean-Baptiste Nahan on 23/01/13.
//  Copyright (c) 2013 Jean-Baptiste Nahan. All rights reserved.
//

#import "OFNFile.h"

@implementation OFSameFile

@synthesize path, type;

@end

@implementation OFNFile

@synthesize compared, sameList, path;

- (void)addSame:(NSString *)pathF withSameMode:(int)same{
    if([sameList count]==0){ //ajoute si la liste est vide
        OFSameFile * sf= [[OFSameFile alloc] init];
        sf.path=pathF;
        sf.type=same;
        [sameList addObject:sf];
        return;
    }
    
    //Recherche si il existe déjà
    for(int i=0;i<[sameList count]; i++){
        OFSameFile * sf=[sameList objectAtIndex:i];
        if([sf.path isEqualToString:pathF]){
            sf.type=same;
        }
    }
    
    //ajoute si pas trouvé
    OFSameFile * sf2= [[OFSameFile alloc] init];
    sf2.path=pathF;
    sf2.type=same;
    [sameList addObject:sf2];
    
    
}
@end
