/*================================================================================================*/
/*
 *	Copyright 2012-2015, 2023-2024 Avid Technology, Inc.
 *	All rights reserved.
 *	
 *	This file is part of the Avid AAX SDK.
 *	
 *	The AAX SDK is subject to commercial or open-source licensing.
 *	
 *	By using the AAX SDK, you agree to the terms of both the Avid AAX SDK License
 *	Agreement and Avid Privacy Policy.
 *	
 *	AAX SDK License: https://developer.avid.com/aax
 *	Privacy Policy: https://www.avid.com/legal/privacy-policy-statement
 *	
 *	Or: You may also use this code under the terms of the GPL v3 (see
 *	www.gnu.org/licenses).
 *	
 *	THE AAX SDK IS PROVIDED "AS IS" WITHOUT ANY WARRANTY, AND ALL WARRANTIES, WHETHER
 *	EXPRESSED OR IMPLIED, INCLUDING MERCHANTABILITY AND FITNESS FOR PURPOSE, ARE
 *	DISCLAIMED.
 */
/*================================================================================================*/

#import "DemoGain_SliderCellCocoa.h"

#include "DemoGain_SliderCocoa.h"

@implementation DemoGain_SliderCellCocoa

- (BOOL)continueTracking:(NSPoint)lastPoint at:(NSPoint)currentPoint inView:(NSView *)controlView
{
	// HACK? We all know that this is the right class for
	// this object, and other solutions seem too obtuse.
	DemoGain_SliderCocoa* sliderView;
	sliderView = (DemoGain_SliderCocoa* )[self controlView];
	if ([sliderView GetDefaultCommandState])
	{
		return YES;
	}
	else
	{
		return [super continueTracking:lastPoint at:currentPoint inView:controlView];
	}
}

- (void)stopTracking:(NSPoint)lastPoint at:(NSPoint)stopPoint inView:(NSView *)controlView mouseIsUp:(BOOL)flag
{
	// Call inherited first in order to release the control after the final update has been submitted
	[super stopTracking:lastPoint at:stopPoint inView:controlView mouseIsUp:flag];
	
	// HACK? We all know that this is the right class for
	// this object, and other solutions seem too obtuse.
	DemoGain_SliderCocoa* sliderView;
	sliderView = (DemoGain_SliderCocoa* )[self controlView];
	[sliderView EndControlEditEvent];
}

@end
