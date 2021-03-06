/*
  Mouse.m

  Controller class for Mouse preferences bundle

  Author:	Sergii Stoian <stoyan255@ukr.net>
  Date:		2015

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License as
  published by the Free Software Foundation; either version 2 of
  the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

  See the GNU General Public License for more details.

  You should have received a copy of the GNU General Public
  License along with this program; if not, write to:

  Free Software Foundation, Inc.
  59 Temple Place - Suite 330
  Boston, MA  02111-1307, USA
*/
#import <AppKit/NSMatrix.h>
#import <AppKit/NSImage.h>
#import <Preferences.h>

@interface Mouse: NSObject <PrefsModule>
{
  NXMouse *mouse;
  NSImage *image;
  NSImage *handImage;
  
  id view;
  id window;
  id speedMtrx;
  id doubleClickMtrx;
  id tresholdField;
  id tresholdSlider;
  id menuMtrx;
  id menuLeftBtn;
  id menuRightBtn;
  id handImageView;
  id wheelScrollField;
  id wheelControlScrollField;
  id cursorsBtn;
}

@end
