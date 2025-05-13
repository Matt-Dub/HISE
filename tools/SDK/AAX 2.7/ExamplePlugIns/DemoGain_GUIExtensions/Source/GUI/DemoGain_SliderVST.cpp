/*================================================================================================*/
/*
 *	Copyright 2011-2015, 2018, 2023-2024 Avid Technology, Inc.
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
#include "DemoGain_SliderVST.h"
#include "AAX_CEffectGUI_VST.h"
#include "AAX_IViewContainer.h"


DemoGain_SliderVST::DemoGain_SliderVST (const VSTGUI::CRect& size, VSTGUI::IControlListener* listener, long tag, long iMinPos, long iMaxPos, VSTGUI::CBitmap* handle, VSTGUI::CBitmap* background, const VSTGUI::CPoint& offset, const long style)
: VSTGUI::CVerticalSlider (size, listener, tag, iMinPos, iMaxPos, handle, background, offset, style),
  mViewContainer (NULL),
  mParamID (0)
{
}

DemoGain_SliderVST::DemoGain_SliderVST (const VSTGUI::CRect& rect, VSTGUI::IControlListener* listener, long tag, const VSTGUI::CPoint& offsetHandle, long rangeHandle, VSTGUI::CBitmap* handle, VSTGUI::CBitmap* background, const VSTGUI::CPoint& offset, const long style)
: VSTGUI::CVerticalSlider (rect, listener, tag, offsetHandle, rangeHandle, handle, background, offset, style),
  mViewContainer (NULL),
  mParamID (0)
{
}

DemoGain_SliderVST::DemoGain_SliderVST (const VSTGUI::CVerticalSlider& slider)
: VSTGUI::CVerticalSlider (slider),
  mViewContainer (NULL),
  mParamID (0)
{
}

VSTGUI::CMouseEventResult DemoGain_SliderVST::onMouseDown (VSTGUI::CPoint& where, const VSTGUI::CButtonState& buttons)
{
	VSTGUI::CMouseEventResult result = VSTGUI::kMouseEventNotHandled;
	const AAX_CVSTGUIButtonState aax_buttons(buttons, mViewContainer);
	
	if (mViewContainer && mParamID)
	{
		if (mViewContainer->HandleParameterMouseDown ( mParamID, aax_buttons.AsAAX() ) == AAX_SUCCESS)
		{
			result = VSTGUI::kMouseEventHandled;
		}
	}
	
	if (result == VSTGUI::kMouseEventNotHandled)
	{
		result = VSTGUI::CVerticalSlider::onMouseDown (where, aax_buttons.AsVST());
	}
	
	return result;
}

VSTGUI::CMouseEventResult DemoGain_SliderVST::onMouseUp (VSTGUI::CPoint& where, const VSTGUI::CButtonState& buttons)
{
	VSTGUI::CMouseEventResult result = VSTGUI::kMouseEventNotHandled;
	const AAX_CVSTGUIButtonState aax_buttons(buttons, mViewContainer);
	
	if (mViewContainer && mParamID)
	{
		if (mViewContainer->HandleParameterMouseUp ( mParamID, aax_buttons.AsAAX() ) == AAX_SUCCESS)
		{
			result = VSTGUI::kMouseEventHandled;
		}
	}
	
	if (result == VSTGUI::kMouseEventNotHandled)
	{
		result = VSTGUI::CVerticalSlider::onMouseUp (where, aax_buttons.AsVST());
	}
	
	return result;
}

VSTGUI::CMouseEventResult DemoGain_SliderVST::onMouseMoved (VSTGUI::CPoint& where, const VSTGUI::CButtonState& buttons)
{
	VSTGUI::CMouseEventResult result = VSTGUI::kMouseEventNotHandled;
	const AAX_CVSTGUIButtonState aax_buttons(buttons, mViewContainer);
	
	if (mViewContainer && mParamID && (buttons & VSTGUI::kLButton)) // Drag
	{
		if (mViewContainer->HandleParameterMouseDrag ( mParamID, aax_buttons.AsAAX() ) == AAX_SUCCESS)
		{
			result = VSTGUI::kMouseEventHandled;
		}
	}
	
	if (result == VSTGUI::kMouseEventNotHandled)
	{
		VSTGUI::CButtonState buttonHack = aax_buttons.AsVST();
		if (buttonHack & VSTGUI::kControl)
		{
			// HACK: The fine-adjustment modifier is shift for VST
			// but command/control for Pro Tools.  We emulate the
			// shift key and call inherited rather than re-writing
			// the whole onMouseMoved method to handle kControl
			// as the fine-adjustment modifier.
			buttonHack |= VSTGUI::kShift;
		}
		result = VSTGUI::CVerticalSlider::onMouseMoved (where, buttonHack);
	}
	
	return result;
}

bool DemoGain_SliderVST::checkDefaultValue (VSTGUI::CButtonState button)
{
	// By default, VSTGUI controls use kControl rather
	// than kAlt as their set-to-default modifier.  We
	// override this method and re-implement it entirely,
	// since it's a simple change.
	if (button == (VSTGUI::kAlt|VSTGUI::kLButton))
	{
		// begin of edit parameter
		beginEdit ();
		
		value = getDefaultValue ();
		if (isDirty () && listener)
			listener->valueChanged (this);
		
		// end of edit parameter
		endEdit ();
		return true;
	}
	return false;
}

void DemoGain_SliderVST::SetViewContainer (AAX_IViewContainer* viewContainer)
{
	mViewContainer = viewContainer;
}

void DemoGain_SliderVST::SetParamID (AAX_CParamID paramID)
{
	mParamID = paramID;
}
