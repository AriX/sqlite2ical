//
//  sqlite2icalAppDelegate.h
//  sqlite2ical
//
//  Created by Ari on 9/13/11.
//  Copyright 2011 Squish Software. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <libical/ical.h>
#import <sqlite3.h>

@interface sqlite2icalAppDelegate : NSObject <NSApplicationDelegate> {
    NSWindow *window;
}

- (IBAction)convert:(id)sender;

@property (assign) IBOutlet NSWindow *window;

@end
