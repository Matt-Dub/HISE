/*================================================================================================*/
/*
 *	Copyright 2011-2015, 2023-2024 Avid Technology, Inc.
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

/**  
 *	\file   DemoGain_SliderCocoa.h
 *
 *	\brief	DemoGain_SliderCocoa class definition.
 *
 *  \author Rob Majors
 */ 
/*================================================================================================*/
#import <Cocoa/Cocoa.h>
#import <AppKit/NSSlider.h>

class AAX_IViewContainer;
class AAX_IEffectParameters;

@interface DemoGain_SliderCocoa : NSSlider
{
	AAX_IViewContainer *		mViewContainer;
	AAX_IEffectParameters *		mEffectParameters;
	
	boolean_t					mSetToDefault;
}

- (void)		SetViewContainer:(AAX_IViewContainer *) iViewContainer;
- (void)		SetEffectParameters:(AAX_IEffectParameters *) iEffectParameters;
- (void)		BeginControlEditEvent:(boolean_t) iDefaultCommandState;
- (void)		EndControlEditEvent;
- (boolean_t)	GetDefaultCommandState;
- (void)		SetDefaultCommandState:(boolean_t) iDefaultCommandState;
- (uint32_t)	GetAAXModifiersFromNSEvent:(NSEvent *) theEvent;

@end
