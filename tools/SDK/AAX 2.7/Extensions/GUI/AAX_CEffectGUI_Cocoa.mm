/*================================================================================================*/
/*
 *	Copyright 2013-2015, 2023-2024 Avid Technology, Inc.
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

#include "AAX_CEffectGUI_Cocoa.h"
#include "AAX_IParameter.h"

// *******************************************************************************
// METHOD:	AAX_CEffectGUI_Cocoa
// *******************************************************************************
AAX_CEffectGUI_Cocoa::AAX_CEffectGUI_Cocoa()
:   mNSView(0),
    mViewController(0)
{
}

// *******************************************************************************
// METHOD:	~AAX_CEffectGUI_Cocoa
// *******************************************************************************
AAX_CEffectGUI_Cocoa::~AAX_CEffectGUI_Cocoa()
{
	this->DeleteViewContainer ();
}

// *******************************************************************************
// METHOD:	CreateViewContainer
// *******************************************************************************
void AAX_CEffectGUI_Cocoa::CreateViewContainer ()
{
	if ( this->GetViewContainerType ()  == AAX_eViewContainer_Type_NSView )
	{
		mNSView = (NSView *) this->GetViewContainerPtr ();
		this->AddViewContents ();
	}
}

// *******************************************************************************
// ROUTINE:	AddViewContents
// *******************************************************************************
void AAX_CEffectGUI_Cocoa::AddViewContents ()
{	
	if ( mNSView && mViewController )
	{
		if ( mViewController && mViewController.view )
			[mNSView addSubview:mViewController.view];
	}
}

// *******************************************************************************
// ROUTINE:	DeleteViewContainer
// *******************************************************************************
void AAX_CEffectGUI_Cocoa::DeleteViewContainer ()
{	
	if ( mNSView && mViewController && mViewController.view )
	{
		[mViewController.view removeFromSuperview];
		[mViewController release];
		mViewController = 0;
	}
}	

// *******************************************************************************
// METHOD:	GetViewSize
// *******************************************************************************
AAX_Result AAX_CEffectGUI_Cocoa::GetViewSize ( AAX_Point *oEffectViewSize ) const
{
	if ( mViewController && mViewController.view )
	{
		oEffectViewSize->horz = mViewController.view.frame.size.width;
		oEffectViewSize->vert = mViewController.view.frame.size.height;
	}

	return AAX_SUCCESS;
}
