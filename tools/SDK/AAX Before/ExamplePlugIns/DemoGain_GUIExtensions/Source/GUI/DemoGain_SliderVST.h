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

/**  
 *	\file   DemoGain_SliderVST.h
 *
 *	\author Rob Majors
 */ 
/*================================================================================================*/
#pragma once
#ifndef DEMOGAIN_SLIDERVST_H
#define DEMOGAIN_SLIDERVST_H

#include "AAX.h"

#include "lib/vstguibase.h"

#include "lib/controls/cslider.h"
#include "lib/controls/ccontrol.h"

class AAX_IViewContainer;

class DemoGain_SliderVST : public VSTGUI::CVerticalSlider
{
public:
	DemoGain_SliderVST (const VSTGUI::CRect& size, VSTGUI::IControlListener* listener, long tag, long iMinPos, long iMaxPos, VSTGUI::CBitmap* handle, VSTGUI::CBitmap* background, const VSTGUI::CPoint& offset = VSTGUI::CPoint (0, 0), const long style = VSTGUI::kBottom);
	DemoGain_SliderVST (const VSTGUI::CRect& rect, VSTGUI::IControlListener* listener, long tag, const VSTGUI::CPoint& offsetHandle, long rangeHandle, VSTGUI::CBitmap* handle, VSTGUI::CBitmap* background, const VSTGUI::CPoint& offset = VSTGUI::CPoint(0, 0), const long style = VSTGUI::kBottom);
	DemoGain_SliderVST (const VSTGUI::CVerticalSlider& slider);	
	
public: // VSTGUI::CVerticalSlider
	virtual VSTGUI::CMouseEventResult onMouseDown (VSTGUI::CPoint& where, const VSTGUI::CButtonState& buttons);
	virtual VSTGUI::CMouseEventResult onMouseUp (VSTGUI::CPoint& where, const VSTGUI::CButtonState& buttons);
	virtual VSTGUI::CMouseEventResult onMouseMoved (VSTGUI::CPoint& where, const VSTGUI::CButtonState& buttons);
	virtual bool checkDefaultValue (VSTGUI::CButtonState button);
	
public:
	void SetViewContainer (AAX_IViewContainer* viewContainer);
	void SetParamID (AAX_CParamID paramID);
	
private:
	AAX_IViewContainer* mViewContainer;
	AAX_CParamID mParamID;
};

#endif // DEMOGAIN_SLIDERVST_H
