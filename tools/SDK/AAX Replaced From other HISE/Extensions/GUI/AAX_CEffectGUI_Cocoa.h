/*================================================================================================*/
/*
 *	Copyright 2010-2015, 2019, 2023-2024 Avid Technology, Inc.
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
 *  \file AAX_CEffectGUI_Cocoa.h
 *
 */
/*================================================================================================*/

#ifndef AAX_CEFFECTGUI_COCOA_H
#define AAX_CEFFECTGUI_COCOA_H

#ifdef __OBJC__
#import <Cocoa/Cocoa.h>
#else
class NSWindow;
class NSViewController;
class NSView;
#endif

#include "AAX_CEffectGUI.h"

#include <string>
#include <vector>

class AAX_CEffectGUI_Cocoa : public AAX_CEffectGUI
{
public:
	AAX_CEffectGUI_Cocoa ();
	~AAX_CEffectGUI_Cocoa () AAX_OVERRIDE;

protected:
	AAX_Result	GetViewSize ( AAX_Point * oEffectViewSize ) const AAX_OVERRIDE;
	void		CreateViewContainer () AAX_OVERRIDE;
	void		DeleteViewContainer () AAX_OVERRIDE;

	void		SetViewController ( NSViewController * iViewController ) { mViewController = iViewController; }
	void		AddViewContents ();

protected:
	NSView *			mNSView;	
	NSViewController *	mViewController;
};

#endif //AAX_CEFFECTGUI_COCOA_H
