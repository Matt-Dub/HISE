/*================================================================================================*/
/*
 *	Copyright 2013-2015, 2019, 2023-2024 Avid Technology, Inc.
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
#import <Cocoa/Cocoa.h>

#include "DemoGain_ViewController.h"
#include "DemoGain_ViewControllerFactory.h"

#include "DemoGain_GUI_Cocoa.h"
#include "DemoGain_Defs.h"

#include "AAX_UtilsNative.h"


// *******************************************************************************
// ROUTINE:	Create
// *******************************************************************************
AAX_IEffectGUI * AAX_CALLBACK DemoGain_GUI::Create ()
{
	AAX_IEffectGUI * effectGUI = new DemoGain_GUI;
	return effectGUI;
}

// *******************************************************************************
// METHOD:	DemoGain_GUI
// *******************************************************************************
DemoGain_GUI::DemoGain_GUI ()
:   mDemoGainViewController(0)
{
}

// *******************************************************************************
// METHOD:	~DemoGain_GUI
// *******************************************************************************
DemoGain_GUI::~DemoGain_GUI ()
{
}

// *******************************************************************************
// METHOD:	CreateViewContents
// *******************************************************************************
void DemoGain_GUI::CreateViewContents ()
{
	NSBundle *			demoGainBundle = [NSBundle bundleWithIdentifier:@"com.avid.aax-sdk-example.DemoGain-Cocoa"];
	if ( demoGainBundle )
	{
		// The plug-in's Cocoa elements are all contained in a separate
		// bundle, DemoGain_CocoaGUI.  Once the DemoGain_CocoaGUI bundle
		// is loaded here it is never unloaded, even if the host unloads
		// the main DemoGain bundle
		
		NSString* cocoaUIPath = [[demoGainBundle resourcePath] stringByAppendingPathComponent:@"DemoGain_CocoaGUI.bundle"];		
		NSBundle* cocoaUIBundle = [NSBundle bundleWithPath:cocoaUIPath];
		
		NSError* error;
		BOOL result = [cocoaUIBundle preflightAndReturnError:&error];
		NSLog(@"%d", result);
		
		DemoGain_ViewControllerFactory* factory = [[[cocoaUIBundle principalClass] alloc] init];
		mDemoGainViewController = (DemoGain_ViewController*)[factory viewControllerFromBundle:cocoaUIBundle
		                                                     effectParameters:this->GetEffectParameters()
		                                                     controller:this->GetController()];
		this->SetViewController ( mDemoGainViewController );
	}
}

// *******************************************************************************
// METHOD:	AddViewContents
// *******************************************************************************
void DemoGain_GUI::CreateViewContainer ()
{	
	AAX_CEffectGUI_Cocoa::CreateViewContainer(); // Call inherited
	[mDemoGainViewController SetViewContainerOnViews:this->GetViewContainer()];
	[mDemoGainViewController SetEffectParametersOnViews:this->GetEffectParameters()];
}

// *******************************************************************************
// METHOD:	ParameterUpdated
// *******************************************************************************
AAX_Result DemoGain_GUI::ParameterUpdated ( AAX_CParamID iParameterID )
{
	if ( mDemoGainViewController && AAX::IsParameterIDEqual( iParameterID, DemoGain_GainID ) )
		[mDemoGainViewController UpdateGainValues];
	
	return AAX_SUCCESS;
}

// *******************************************************************************
// METHOD:	TimerWakeup
// *******************************************************************************
AAX_Result DemoGain_GUI::TimerWakeup (void)
{
	if ( mDemoGainViewController )
	{
		[mDemoGainViewController UpdateMeters];
	}
	
	return AAX_SUCCESS;
}
