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
#include "DemoGain_GUI_Juce.h"
#include "DemoGain_ViewComponent.h"
#include "DemoGain_Defs.h"

// *******************************************************************************
// ROUTINE:	Create
// *******************************************************************************
AAX_IEffectGUI * AAX_CALLBACK DemoGain_GUI::Create ()
{
	return new DemoGain_GUI;
}

// *******************************************************************************
// METHOD:	CreateViewContents
// *******************************************************************************
void DemoGain_GUI::CreateViewContents ()
{
	mViewComponent = new DemoGain_ViewComponent ( this );
}

// *******************************************************************************
// METHOD:	ParameterUpdated
// *******************************************************************************
AAX_Result DemoGain_GUI::ParameterUpdated ( AAX_CParamID iParameterID )
{
	DemoGain_ViewComponent* viewComponent = dynamic_cast<DemoGain_ViewComponent *>(mViewComponent);
	if (viewComponent && ! strcmp( iParameterID, DemoGain_GainID ) )
	{
		viewComponent->UpdateGainParameter();
	}
	return AAX_SUCCESS;
}

// *******************************************************************************
// METHOD:	setControlHighlightInfo
// *******************************************************************************
AAX_Result DemoGain_GUI::SetControlHighlightInfo (AAX_CParamID iParameterID, AAX_CBoolean iIsHighlighted, AAX_EHighlightColor iColor)
{
	DemoGain_ViewComponent* viewComponent = dynamic_cast<DemoGain_ViewComponent *>(mViewComponent);
	if ( viewComponent )
		return viewComponent->setControlHighlightInfo ( iParameterID, iIsHighlighted != 0, (AAX_EHighlightColor) iColor );
	
	return AAX_SUCCESS;
}
