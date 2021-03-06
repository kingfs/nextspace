/** @class NXIcon
    @brief An icon with an image and a label.

    This class is a typical icon as we know it from the
    workspace manager and simmilar apps. It consists of three
    components: the icon itself, the short label view and
    the long label view.

    Unless not configured not do so, when the icon is selected
    (which can happen a variety of ways), it will be showing
    the long (full) label and when deselected a short (collapsed)
    label is shown. The short label's string is created by
    abbreviating the string in the long label to the maximum
    defined width.

    @author Saso Kiselkov, Sergii Stoian
*/

#import <AppKit/NSView.h>
#import <AppKit/NSDragging.h>

static inline float absolute_value(float v)
{
  if (v < 0)
    return -v;
  else
    return v;
}

@class NXIconLabel, NSImage, NSEvent, NSString, NSColor;

@protocol NSDraggingInfo;

@interface NXIcon : NSView
{
  NXIconLabel *shortLabel; // The short (collapsed) label.
  NXIconLabel *longLabel;  // The long (expanded) label.

  NSString    *labelString;
  NSImage     *iconImage;

  BOOL isSelected;
  BOOL isDimmed;
  BOOL isSelectable;
  BOOL isEditable;

  BOOL showsExpandedLabelWhenSelected;
  
  float maximumCollapsedLabelWidth;

  id       target;
  id       delegate;
  SEL      action;
  SEL      doubleAction;
  SEL      dragAction;
  unsigned modifierFlags;

  unsigned dragEnteredResult;

  NSColor *bgColor;
}

/** Sets the default icon size.
    All subsequently created icons will have this size set up when created.*/
+ (void)setDefaultIconSize:(NSSize)newSize;
+ (NSSize)defaultIconSize;

/** Sets the default maximum collapsed label width.
    All subsequently created icons will have this maximum collapsed
    label width set after creation. */
+ (void)setDefaultMaximumCollapsedLabelWidth:(float)newWidth;
+ (float)defaultMaximumCollapsedLabelWidth;
- (void)dealloc;

/** Designated initializer. Do not use "-initWithFrame:".
    This method initializes the icon to the default size,
    creates the labels and sets up all other stuff. */
- init;

/** Draws the receiver. */
- (void)drawRect:(NSRect)r;

/** Sets a new size of the receiver. This also automatically repositions the
    labels as needed. */
- (void)setIconSize:(NSSize)newIconSize;
- (NSSize)iconSize;

/** Puts the receiver into the selected view, centering it at the sepecified
    point. Do not use the target view's "-addSubview:" method for this
    purpose, because the receiver will also want to take it's labels along. */
- (void)putIntoView:(NSView *)newSuperview 
            atPoint:(NSPoint)centerPoint;
/** Removes the receiver from it's superview. 
    Do not use the superview's "-removeSubview:" method for this purpose, 
    because the labels would not get removed. */
- (void)removeFromSuperview;

/** Returns the receiver's long label view. */
- (NXIconLabel *)label;
/** Returns the receiver's short label view. */
- (NXIconLabel *)shortLabel;

/** Sets the image the receiver is to display. */
- (void)setIconImage:(NSImage *)newImage;
- (NSImage *)iconImage;

/** Sets the label string that's associated with this icon.
    You should not set labels by setting the contents of the
    icon label's directly, but instead use this method, since
    it also respects the maximum width constrains for the
    collapsed label and updates everything correctly. */
- (void)setLabelString:(NSString *)aLabel;
/** Returns the label string of the icon. The returned string
    is the full label. */
- (NSString *)labelString;

/** Sets whether the receiver is to display itself as selected. If you
    pass YES in the argument and unless you specify the receiver not
    to display it's expanded label when selected (using -[NXIcon
    setShowsExpandedLabelWhenSelected:]), the receiver will also
    remove it's short label from display and replace it with
    the expanded label. If you pass NO, the opposite happens. */
- (void)setSelected:(BOOL)sel;
/** Returns YES if the receiver is selected, and NO otherwise. */
- (BOOL)isSelected;

/** An IB action to select the receiver. */
- (void)select:(id)sender;
/** An IB action to deselect the receiver. */
- (void)deselect:(id)sender;

/** Sets whether the receiver draws it's image in a dimmed way.*/
- (void)setDimmed:(BOOL)dimm;
/** Returns whether the receiver is drawing in a dimmed way. */
- (BOOL)isDimmed;

/** Sets whether the user can select the receiver by clicking on it.*/
- (void)setSelectable:(BOOL)sel;
/** Returns YES if the user can select the receiver by clicking on it,
    and NO otherwise. */
- (BOOL)isSelectable;
/** Sets whether the user can edit the receiver's long label.*/
- (void)setEditable:(BOOL)edit;
/** Returns YES if the user can edit the receiver's long label,
  and NO otherwise. */
- (BOOL)isEditable;

/** Sets whether the receiver shows it's expanded full label when
    selected or not. */
- (void)setShowsExpandedLabelWhenSelected:(BOOL)flag;
/** Returns YES if the receiver shows the expanded label when selected,
    and NO otherwise. */
- (BOOL)showsExpandedLabelWhenSelected;

/** Sets the color with which to draw the icon's tile when it's selected.*/
- (void)setBackgroundColor:(NSColor *)aColor;
- (NSColor *)backgroundColor;

/** Sets the target of the receiver.*/
- (void)setTarget:aTarget;
/** Returns the target of the receiver. */
- target;

/** Sets the action to send to the target when the receiver is clicked. */
- (void)setAction:(SEL)anAction;
/** Returns the action. See "-[NXIcon setAction:]". */
- (SEL)action;

/** Sets the action to send to the target when the receiver is 
    double-clicked.*/
- (void)setDoubleAction:(SEL)anAction;
/** Returns the double action. See "-[NXIcon setDoubleAction:]". */
- (SEL)doubleAction;

/** Sets the action to send to the target when the receiver is dragged.
    There are two arguments passed in this message: the receiver of this
    message and the event which invoked the drag. */
- (void)setDragAction:(SEL)anAction;
/** Returns the drag action. See "-[NXIcon setDragAction:]". */
- (SEL)dragAction;

/** Sets the delegate for dragging operations. The messages sent to
    to the delegate during an icon-drag operation are declared in
    the "NXIconDragging" protocol. */
- (void)setDelegate:aDelegate;
/** Returns the receiver's delegate. See "-[NXIcon setDelegate:]". */
- delegate;

/** When an action or double-action is invoked, the target can query the
    receiver with this method to see what modifier flags were pressed
    when the action occured. */
- (NSUInteger)modifierFlags;

/** Sets the maximum size the short label can have when the receiver
    is deselected. When the maximum label width is reached, the label
    string in the short label is automatically trimmed and an ellipsis
    ("...") string is appended to it to shows that it has been abbreviated.
*/
- (void)setMaximumCollapsedLabelWidth:(float)newWidth;
/** Returns the maximum collapsed label width.
    See -[NXIcon setMaximumCollapsedLabelWidth:]". */
- (float)maximumCollapsedLabelWidth;

/** Returns the dragging source operation mask as queried from the delegate. */
// - (unsigned int)draggingSourceOperationMaskForLocal:(BOOL)isLocal;

@end

/** This protocol declares the messages that are sent to the icon delegate
    when the icon is the dragging destination. The messages are actually
    the same as those declared in the "NSDraggingSource" protocol, except
    that they have an additional "icon" argument appended at the end
    so that the delegate can determine which icon they are comming from. */

@protocol NXIconDraggingDestination

- (unsigned int)draggingEntered:(id <NSDraggingInfo>)sender
                           icon:(NXIcon *)anIcon;
- (unsigned int)draggingUpdated:(id <NSDraggingInfo>)sender
                           icon:(NXIcon *)anIcon;
- (void)draggingExited:(id <NSDraggingInfo>)sender
                  icon:(NXIcon *)anIcon;
		   
- (BOOL)prepareForDragOperation:(id <NSDraggingInfo>)sender
                           icon:(NXIcon *)anIcon;

- (BOOL)performDragOperation:(id <NSDraggingInfo>)sender
                        icon:(NXIcon *)anIcon;

- (void)concludeDragOperation:(id <NSDraggingInfo>)sender
                         icon:(NXIcon *)anIcon;

- (void)draggingEnded:(id <NSDraggingInfo>)sender
                 icon:(NXIcon *)anIcon;

- (unsigned int)draggingSourceOperationMaskForLocal:(BOOL)isLocal
                                               icon:(NXIcon *)anIcon;

@end

/** The same as the "NXIconDraggingDestination" protocol, but for
    the dragging source. */
@protocol NXIconDraggingSource

- (unsigned int)draggingSourceOperationMaskForLocal:(BOOL)isLocal
                                               icon:(NXIcon *)anIcon;

@end
