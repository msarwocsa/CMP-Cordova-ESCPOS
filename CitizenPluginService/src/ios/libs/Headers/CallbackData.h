//
//  CallbackData.h
//  iOS
//
//  Created by leesk on 11. 12. 13..
//  Copyright 2011. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface CallbackData : NSObject 
{
	int dataType;
	NSData * data;
	int dataLength;
}
@property (nonatomic) int dataType;
@property (copy,nonatomic) NSData * data;
@property (nonatomic) int dataLength;

-(id) initWithData:(NSData *) data withLength:(int) length withType:(int) type;
-(void) dealloc;
@end
