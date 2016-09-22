/*
  Class:               ClockViewTest
  Inherits from:       NSObject
  Class descritopn:    NXClockView demo for testing purposes.

  Copyright (C) 2016 Sergii Stoian

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#import "ClockViewTest.h"

@implementation ClockViewTest : NSObject

- (id)init
{
  self = [super init];

  if (![NSBundle loadNibNamed:@"ClockView" owner:self])
    {
      NSLog (@"ClockViewTest: Could not load nib, aborting.");
      return nil;
    }

  return self;
}

- (void)awakeFromNib
{
  [window center];
  [hour24Btn setState:![clockView shows12HourFormat]];
  [showYearBtn setState:[clockView showsYear]];
  [showColonBtn setState:[clockView showsLEDColon]];
  [clockView setCalendarDate:[NSCalendarDate calendarDate]];

  [languageList
    addItemsWithTitles:[[NSUserDefaults standardUserDefaults]
                         objectForKey:@"NSLanguages"]];
}

- (void)show
{
  [window makeKeyAndOrderFront:self];
}

- (void)setDate:(id)sender
{
  year = [yearField integerValue];
  month = [monthField integerValue];
  day = [dayField integerValue];

  hour = [hourField integerValue];
  minute = [minuteField integerValue];
  second = [secondField integerValue];

  [clockView setCalendarDate:[NSCalendarDate dateWithYear:year
                                                    month:month
                                                      day:day
                                                     hour:hour
                                                   minute:minute
                                                   second:second
                                                 timeZone:[NSTimeZone localTimeZone]]];
}

// --- Actions ---

- (void)set24Hour:(id)sender
{
  [clockView setShows12HourFormat:![sender state]];
}
- (void)setShowYear:(id)sender
{
  [clockView setShowsYear:[sender state]];
}
- (void)setShowColon:(id)sender
{
  [clockView setShowsLEDColon:[sender state]];
}

- (void)setLanguage:(id)sender
{
  [clockView loadImageForLanguage:[[languageList selectedItem] title]];
  [clockView setNeedsDisplay:YES];
}

@end