/*================================================================================================*/
/*
 *	Copyright 2009-2015, 2019, 2023-2024 Avid Technology, Inc.
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
 *	\file   DemoGain_GUI_Cocoa.h
 *
  *	\brief	DemoGain_GUI class definition.
 */ 
/*================================================================================================*/
#pragma once
#ifndef DEMOGAIN_GUI_COCOA_H
#define DEMOGAIN_GUI_COCOA_H

#include "AAX_CEffectGUI_Cocoa.h"

#ifdef __OBJC__
#import <Cocoa/Cocoa.h>
#import "DemoGain_ViewController.h"
#else
class DemoGain_ViewController;
#endif

//==============================================================================
class DemoGain_GUI : public AAX_CEffectGUI_Cocoa
{
public:
	static AAX_IEffectGUI *		AAX_CALLBACK Create ();

	DemoGain_GUI();
	~DemoGain_GUI() AAX_OVERRIDE;

	void				CreateViewContents () AAX_OVERRIDE;
	AAX_Result			ParameterUpdated ( AAX_CParamID iParameterID ) AAX_OVERRIDE;
	AAX_Result			TimerWakeup() AAX_OVERRIDE;
	
protected:
	void				CreateViewContainer () AAX_OVERRIDE; // AAX_CEffectGUI_Cocoa

private:
	DemoGain_ViewController	*	mDemoGainViewController;
};

#endif
