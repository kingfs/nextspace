/*
 * NXScrren.h
 *
 * Provides integration with XRandR subsystem.
 * Manage display layouts.
 *
 * Copyright 2015, Serg Stoyan
 * All right reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * NXScreen, NXDisplay

 *
 * Definitions
 *
 Screen  - A set of displays (monitors) for a single user with one keyboard and
           mouse. In other words, screen is a set of hardware resources: one or
           more monitors, one keyboard and one mouse.
           Logical screen size may be bigger then sum of NXDisplays resolutions.

           Xrandr's name - Screen.

 Display - Physical monitor and hardware that can be color, grayscale, or
           monochrome. Characterized by, resolution, refresh rate, gamma
           correction, brightness, contrast.
           Also has specific properties like: vendor and model name, serial
           number etc.

           Xrandr's name - Output.

 View    - Image visible for user on Display. It's part of Screen and can be
           visible on multiple Displays (in case of clonning). View is always
           part of Screen but can be invisible on some Display.

           Xrandr's name - CRTC.

 *
 * Description
 *
 NXScreen subsystem is a set of functions and classes to get and set underlying 
 windowing system information, including:
 - Getting Display information: resolution, monitor mode, monitor type
   (CRT, TFT, LVDS), gamma, color depth, dpi value, monitor model.
 - Changing Display modes: resolution, refresh rate, full screen.
 - Configuring Display configuration: mirroring, dual screen.
 - Providing mechanism to do various display manipulation: fading, switching
   to console, power management.
 */

#import <Foundation/Foundation.h>
#import <AppKit/NSColor.h>

#import <X11/extensions/Xrandr.h>

@class NXDisplay;

@interface NXScreen : NSObject
{
  Display        *xDisplay;
  Window         xRootWindow;

  BOOL useAutosave;

  NSLock *updateScreenLock;
  
  XRRScreenResources *screen_resources;
  
  NSMutableArray *systemDisplays;

  NSSize sizeInPixels, sizeInMilimeters;
}

+ (id)sharedScreen;
- (void)setUseAutosave:(BOOL)yn;

- (XRRScreenResources *)randrScreenResources;
- (void)randrUpdateScreenResources;
- (RRCrtc)randrFindFreeCRTC;

- (NSSize)sizeInPixels;
- (NSSize)sizeInMilimeters;
- (NSUInteger)colorDepth;

/** Returns color saved in defaults with key NXDesktopBackgroundBolor */
- (BOOL)savedBackgroundColorRed:(CGFloat *)redComponent
                          green:(CGFloat *)greenComponent
                           blue:(CGFloat *)blueComponent;
/** Returns current color of root window. On failure returns saved color. */
- (BOOL)backgroundColorRed:(CGFloat *)redComponent
                     green:(CGFloat *)greenComponent
                      blue:(CGFloat *)blueComponent;
- (BOOL)setBackgroundColorRed:(CGFloat)redComponent
                        green:(CGFloat)greenComponent
                         blue:(CGFloat)blueComponent;
 
- (NSArray *)allDisplays;
- (NSArray *)activeDisplays;
- (NSArray *)connectedDisplays;

- (NXDisplay *)mainDisplay;
- (void)setMainDisplay:(NXDisplay *)display;

- (NXDisplay *)displayAtPoint:(NSPoint)point;
- (NXDisplay *)displayWithMouseCursor;
- (NXDisplay *)displayWithName:(NSString *)name;
- (NXDisplay *)displayWithID:(id)uniqueID;

- (void)activateDisplay:(NXDisplay *)display;
- (void)deactivateDisplay:(NXDisplay *)display;
- (void)setDisplay:(NXDisplay *)display resolution:(NSDictionary *)resolution;

- (NSArray *)defaultLayout:(BOOL)arrange;
- (NSArray *)currentLayout;
- (BOOL)validateLayout:(NSArray *)layout;
- (BOOL)applyDisplayLayout:(NSArray *)layout;
- (BOOL)saveCurrentDisplayLayout;
- (NSArray *)savedDisplayLayout;
- (BOOL)applySavedDisplayLayout;
- (NSDictionary *)descriptionOfDisplay:(NXDisplay *)display
                              inLayout:(NSArray *)layout;
- (id)objectForKey:(NSString *)key
        forDisplay:(NXDisplay *)display
          inLayout:(NSArray *)layout;

- (NSArray *)arrangedDisplayLayout;

@end

// Displays.config user path
#define DISPLAYS_CONFIG @"~/Library/Preferences/Displays.config"
#define LAYOUTS_DIR     @"~/Library/Preferences/.NextSpace"

// Displays.config field keys
extern NSString *NXDisplayIsActiveKey;
extern NSString *NXDisplayIsMainKey;
extern NSString *NXDisplayGammaKey;
extern NSString *NXDisplayGammaRedKey;
extern NSString *NXDisplayGammaGreenKey;
extern NSString *NXDisplayGammaBlueKey;
extern NSString *NXDisplayGammaBrightnessKey;
extern NSString *NXDisplayIDKey;
extern NSString *NXDisplayNameKey;
extern NSString *NXDisplayFrameKey;
extern NSString *NXDisplayHiddenFrameKey;
extern NSString *NXDisplayFrameRateKey;
extern NSString *NXDisplaySizeKey;
extern NSString *NXDisplayRateKey;
extern NSString *NXDisplayPhSizeKey;
extern NSString *NXDisplayPropertiesKey;

// Notifications
extern NSString *NXScreenDidChangeNotification;
extern NSString *NXScreenDidUpdateNotification;
