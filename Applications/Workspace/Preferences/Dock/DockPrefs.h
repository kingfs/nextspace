/*
   "Dock" preferences.

   Copyright (C) 2018 Sergii Stoian

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.
   
   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.
   
   You should have received a copy of the GNU Library General Public
   License along with this library; if not, write to the Free
   Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#import <AppKit/AppKit.h>
#import <NXAppKit/NXAppKit.h>

#import <Preferences/PrefsModule.h>

@interface DockPrefsAppicon : NSButton
{
  NSCursor *_cursor;
}
- (void)setCursor:(NSCursor *)c;
@end

@interface DockPrefs : NSObject <PrefsModule>
{
  // Dock
  id window;
  id box;
  DockPrefsAppicon *iconBtn;
  id nameField;
  id appList;
  id pathField;
  id autostartBtn;
  id appLockedBtn;
  id showOnHiddenDockBtn;
  // Application
  id appPanel;
  id appIconView;
  id appIconBtn;
  id appNameField;
  id appCommandField;
  id appMiddleClickField;
  id appDndCommandField;
}

- (void)revert:sender;

@end

@interface DockPrefs (AppSettings)

- (void)appSettingsPanelUpdate;

@end
