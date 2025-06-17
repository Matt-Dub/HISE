/*================================================================================================*/
/*
 *	Copyright 2009-2015, 2023-2024 Avid Technology, Inc.
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
 *	\file   DemoGain_ViewController.h
 *
 *	\brief  DemoGain_ViewController class definition.
 */ 
/*================================================================================================*/
#import <Cocoa/Cocoa.h>

#import "DemoGain_SliderCocoa.h"

#import <AppKit/NSTextField.h>
#import <AppKit/NSLevelIndicator.h>

class AAX_IEffectParameters;
class AAX_IController;
class AAX_IViewContainer;

// *******************************************************
// INTERFACE:	DemoGain_ViewController
// *******************************************************
@interface DemoGain_ViewController : NSViewController <NSTextFieldDelegate>
{	
	IBOutlet DemoGain_SliderCocoa *	mGainSlider;
	IBOutlet NSTextField *		mGainText;
	IBOutlet NSLevelIndicator * mInputLevelIndicator;
	IBOutlet NSLevelIndicator * mOutputLevelIndicator;
	
	AAX_IEffectParameters *		mEffectParameters;
	AAX_IController *			mController;
}

@property (nonatomic, retain) DemoGain_SliderCocoa *		mGainSlider;
@property (nonatomic, retain) NSTextField *			mGainText;
@property (nonatomic, retain) NSLevelIndicator *	mInputLevelIndicator;
@property (nonatomic, retain) NSLevelIndicator *	mOutputLevelIndicator;

- (void)		SetParameters:(AAX_IEffectParameters *) iEffectParameters;
- (void)		SetController:(AAX_IController *) iController;
- (void)		SetViewContainerOnViews:(AAX_IViewContainer *) iViewContainer; // Should be called after views have been created
- (void)		SetEffectParametersOnViews:(AAX_IEffectParameters *) iEffectParameters; // Should be called after views have been created
- (void)		UpdateGainValues;
- (void)		UpdateMeters;
- (void)		controlTextDidEndEditing:(NSNotification *)obj;
- (IBAction)	ChangeGainSlider:(id) iSender;
//- (IBAction)	ChangeGainText:(id) iSender;

@end
