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

#include "DemoGain_SliderJuce.h"



DemoGain_SliderJuce::DemoGain_SliderJuce (const juce::String& componentName)
  : juce::Slider (componentName),
    mViewContainer (NULL),
    mParamID (0),
	mDefaultValue (0.0)
{
//	mDefaultValue.addListener (this);
}

DemoGain_SliderJuce::~DemoGain_SliderJuce (void)
{
//	mDefaultValue.removeListener (this);
}

void DemoGain_SliderJuce::mouseDown (const juce::MouseEvent& e)
{
	AAX_Result err = AAX_ERROR_UNIMPLEMENTED;
	
	uint32_t mods = GetAAXModifiersFromJuceMouseEvent (e);
	if (mViewContainer)
	{
		err = mViewContainer->HandleParameterMouseDown ( mParamID, mods );
	}
	
	if (err != AAX_SUCCESS)
	{
		juce::Slider::mouseDown (e);
	}
}

void DemoGain_SliderJuce::mouseUp (const juce::MouseEvent& e)
{
	AAX_Result err = AAX_ERROR_UNIMPLEMENTED;
	
	uint32_t mods = GetAAXModifiersFromJuceMouseEvent (e);
	if (mViewContainer)
	{
		err = mViewContainer->HandleParameterMouseUp ( mParamID, mods );
	}
	
	if (err != AAX_SUCCESS)
	{
		juce::Slider::mouseUp (e);
	}
}

void DemoGain_SliderJuce::mouseDrag (const juce::MouseEvent& e)
{
	AAX_Result err = AAX_ERROR_UNIMPLEMENTED;
	
	uint32_t mods = GetAAXModifiersFromJuceMouseEvent (e);
	if (mViewContainer)
	{
		err = mViewContainer->HandleParameterMouseDrag ( mParamID, mods );
	}
	
	if (err != AAX_SUCCESS)
	{
		if (mods == AAX_eModifiers_Option)
		{
			juce::Slider::setValue (mDefaultValue.getValue () );
		}
		else
		{
			juce::Slider::mouseDrag (e);
		}
	}
}

void DemoGain_SliderJuce::SetViewContainer (AAX_IViewContainer* viewContainer)
{
	mViewContainer = viewContainer;
}

void DemoGain_SliderJuce::SetParamID (AAX_CParamID paramID)
{
	mParamID = paramID;
}

void DemoGain_SliderJuce::SetDefaultValue (double value)
{
	mDefaultValue = value;
}

uint32_t DemoGain_SliderJuce::GetAAXModifiersFromJuceMouseEvent (const juce::MouseEvent& e)
{
	uint32_t aax_mods = 0;
	
	const juce::ModifierKeys m = e.mods;
	
	if (m.isAltDown())
		aax_mods |= AAX_eModifiers_Option;
	if (m.isCommandDown())
		aax_mods |= AAX_eModifiers_Command;
	if (m.isCtrlDown())
		aax_mods |= AAX_eModifiers_Control;
	
	if (m.isShiftDown())
		aax_mods |= AAX_eModifiers_Shift;
	if (m.isRightButtonDown())
		aax_mods |= AAX_eModifiers_SecondaryButton;
	
	// It is best practice to always query the host as
	// well, since the host's key handler may have
	// prevented some modifier key states from reaching
	// the plug-in.
	if (mViewContainer)
	{
		uint32_t aaxViewMods = 0;
		mViewContainer->GetModifiers (&aaxViewMods);
		aax_mods |= aaxViewMods;
	}
	
	return aax_mods;
}
