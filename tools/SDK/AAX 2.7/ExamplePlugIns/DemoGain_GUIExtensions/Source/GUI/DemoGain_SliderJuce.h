/*================================================================================================*/
/*
 *	Copyright 2011-2015, 2019, 2023-2024 Avid Technology, Inc.
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
 *	\file   DemoGain_SliderJuce.h
 *
 *	\author Rob Majors
 */ 
/*================================================================================================*/
#pragma once
#ifndef DEMOGAIN_SLIDERJUCE_H
#define DEMOGAIN_SLIDERJUCE_H

#include "DemoGain_Defs.h"
#include "AAX_IViewContainer.h"
#include "juce.h"

class DemoGain_SliderJuce : public juce::Slider
{
public: ///////////////////////////////////////// constructor/destructor
	explicit DemoGain_SliderJuce (const juce::String& componentName = juce::String::empty);
	~DemoGain_SliderJuce() override;
	
protected: ////////////////////////////////////// juce::Slider
	void mouseDown (const juce::MouseEvent& e) override; // HACK: Non-virtual in juce::Slider
    void mouseUp (const juce::MouseEvent& e) override;   // HACK: Non-virtual in juce::Slider
    void mouseDrag (const juce::MouseEvent& e) override; // HACK: Non-virtual in juce::Slider

public: ///////////////////////////////////////// DemoGain_SliderJuce
	void SetViewContainer (AAX_IViewContainer* viewContainer);
	void SetParamID (AAX_CParamID paramID);
	void SetDefaultValue (double value);
	
private: //////////////////////////////////////// DemoGain_SliderJuce
	uint32_t GetAAXModifiersFromJuceMouseEvent (const juce::MouseEvent& e);
	
private: //////////////////////////////////////// DemoGain_SliderJuce
	AAX_IViewContainer* mViewContainer;
	AAX_CParamID mParamID;
	juce::Value mDefaultValue;
};

#endif // DEMOGAIN_SLIDERJUCE_H
