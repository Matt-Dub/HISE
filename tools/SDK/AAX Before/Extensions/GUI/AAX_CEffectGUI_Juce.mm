/*================================================================================================*/
/*
 *	Copyright 2010-2015, 2023-2024 Avid Technology, Inc.
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

#include "AAX_CEffectGUI_Juce.h"

#ifdef __OBJC__
#import <Cocoa/Cocoa.h>
#endif

// *******************************************************************************
// METHOD:	AAX_CEffectGUI_Juce::CreateViewContainer
// *******************************************************************************
void AAX_CEffectGUI_Juce::CreateViewContainer ()
{
	void* nativeViewToAttachTo = NULL;
	
	if ( this->GetViewContainerType () == AAX_eViewContainer_Type_NSView )
	{
		nativeViewToAttachTo = ((NSView *) this->GetViewContainerPtr () );
	}
	
	if ( nativeViewToAttachTo && mViewComponent )
	{
		mViewComponent->SetViewContainer ( this->GetViewContainer () );
		mViewComponent->addToDesktop ( 0, nativeViewToAttachTo );
	}
}

// *******************************************************************************
// METHOD:	AAX_CEffectGUI_Juce::DeleteViewContainer
// *******************************************************************************
void AAX_CEffectGUI_Juce::DeleteViewContainer ()
{
	NSAutoreleasePool* autoreleasePool = [[NSAutoreleasePool alloc] init];
	if (mViewComponent)
	{
		mViewComponent->SetViewContainer ( 0 );
		mViewComponent->removeFromDesktop ();
	}
	
	[autoreleasePool release];
}
