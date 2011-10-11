//
//  RockBlasterAppDelegate.h
//  RockBlaster
//
//  Created by William Spaetzel on 11-10-10.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface RockBlasterAppDelegate : NSObject <NSApplicationDelegate> {
    NSWindow *window;
}

@property (assign) IBOutlet NSWindow *window;

@end
