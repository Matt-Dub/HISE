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
/*================================================================================================*/

#import "DemoGain_SliderCocoa.h"

#include "DemoGain_SliderCellCocoa.h"
#include "DemoGain_Defs.h"

#include "AAX_IViewContainer.h"
#include "AAX_IEffectParameters.h"
#include "AAX.h"

@implementation DemoGain_SliderCocoa

// *******************************************************
// METHOD:	awakeFromNib
// *******************************************************
- (void)awakeFromNib
{
//	[DemoGain_SliderCocoa setCellClass:[DemoGain_SliderCellCocoa class]];
//	[self setCell:[[[DemoGain_SliderCellCocoa alloc] init] autorelease]];
	
	// General initialization
	// TODO: Is this the right place?
	[self SetDefaultCommandState:false];
}

// *******************************************************
// METHOD:	SetViewContainer
// *******************************************************
- (void) SetViewContainer:(AAX_IViewContainer *) iViewContainer
{
  	mViewContainer = iViewContainer;
}

// *******************************************************
// METHOD:	SetEffectParameters
// *******************************************************
- (void) SetEffectParameters:(AAX_IEffectParameters *) iEffectParameters
{
  	mEffectParameters = iEffectParameters;
}

// *******************************************************
// METHOD:	mouseDown
// *******************************************************
- (void)mouseDown:(NSEvent *)theEvent
{
	AAX_Result result = AAX_ERROR_UNIMPLEMENTED;
	
	uint32_t modifiers = 0;
	if (mViewContainer)
	{
		modifiers = [self GetAAXModifiersFromNSEvent:theEvent];
		result = mViewContainer->HandleParameterMouseDown (DemoGain_GainID, modifiers);
	}
	
	if (result != AAX_SUCCESS)
	{
		// Check for if we need to set the control to its default value.
		boolean_t settingToDefault = (modifiers == AAX_eModifiers_Option);
		[self BeginControlEditEvent:settingToDefault];
		
		[super mouseDown:theEvent];
	}
}

// *******************************************************
// METHOD:	rightMouseDown
// *******************************************************
- (void)rightMouseDown:(NSEvent *)theEvent
{
	AAX_Result result = AAX_ERROR_UNIMPLEMENTED;
	
	uint32_t modifiers = 0;
	if (mViewContainer)
	{
		modifiers = [self GetAAXModifiersFromNSEvent:theEvent];
		result = mViewContainer->HandleParameterMouseDown (DemoGain_GainID, modifiers);
	}
	
	if (result != AAX_SUCCESS)
	{	
		// Check for if we need to set the control to its default value.
		boolean_t settingToDefault = (modifiers == AAX_eModifiers_Option);
		[self BeginControlEditEvent:settingToDefault];
		
		[super mouseDown:theEvent];
	}
}

// *******************************************************
// METHOD:	BeginControlEditEvent
// *******************************************************
- (void)BeginControlEditEvent:(boolean_t)iDefaultCommandState
{
	[self SetDefaultCommandState:iDefaultCommandState];
	
	if (mViewContainer && mEffectParameters)
	{
		mEffectParameters->TouchParameter(DemoGain_GainID);
	}
}

// *******************************************************
// METHOD:	EndControlEditEvent
// *******************************************************
- (void)EndControlEditEvent
{
	mSetToDefault = false;
	
	if (mViewContainer && mEffectParameters)
	{
		mEffectParameters->ReleaseParameter(DemoGain_GainID);
	}
}

// *******************************************************
// METHOD:	GetDefaultCommandState
// *******************************************************
- (boolean_t)GetDefaultCommandState
{
	return mSetToDefault;
}

// *******************************************************
// METHOD:	SetDefaultCommandState
// *******************************************************
- (void)SetDefaultCommandState:(boolean_t)iDefaultCommandState
{
	mSetToDefault = iDefaultCommandState;
}

// *******************************************************
// METHOD:	GetAAXModifiersFromNSEvent
// *******************************************************
- (uint32_t)GetAAXModifiersFromNSEvent:(NSEvent *)theEvent
{
	uint32_t modifiers = 0;

	if (theEvent)
	{
		if ([theEvent modifierFlags] & NSControlKeyMask)
		{
			modifiers |= AAX_eModifiers_Control;
		}
		
		if ([theEvent modifierFlags] & NSAlternateKeyMask)
		{
			modifiers |= AAX_eModifiers_Option;
		}
		
		if ([theEvent modifierFlags] & NSCommandKeyMask)
		{
			modifiers |= AAX_eModifiers_Command;
		}
		
		if ([theEvent type] == NSRightMouseUp ||
			[theEvent type] == NSRightMouseDragged ||
			[theEvent type] == NSRightMouseDown)
		{
			modifiers |= AAX_eModifiers_SecondaryButton;
		}
		
		// It is best practice to always query the host as
		// well, since the host's key handler may have
		// prevented some modifier key states from reaching
		// the plug-in.
		if (mViewContainer)
		{
			uint32_t aaxViewMods = 0;
			mViewContainer->GetModifiers (&aaxViewMods);
			modifiers |= aaxViewMods;
		}
	}
			
	return modifiers;
}

@end
