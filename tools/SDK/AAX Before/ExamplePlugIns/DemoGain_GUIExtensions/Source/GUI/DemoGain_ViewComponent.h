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
 *	\file   DemoGain_ViewComponent.h
 *
 *	\brief  DemoGain_ViewComponent class definition.
 */ 
/*================================================================================================*/
#pragma once
#ifndef DEMOGAIN_VIEWCOMPONENT_H
#define DEMOGAIN_VIEWCOMPONENT_H

#include "AAX_CEffectGUI_Juce.h"

class DemoGain_SliderJuce;

//==============================================================================
class DemoGain_ViewComponent	: public AAX_JuceContentView
								, public juce::SliderListener
								, public juce::LabelListener
								, public juce::ButtonListener
{
public:	
	DemoGain_ViewComponent ( AAX_CEffectGUI * inEffectGUI );
	~DemoGain_ViewComponent() override;
	
public: ///////////////////////////////////////////// DemoGain_ViewComponent
	virtual void UpdateGainParameter();
	virtual void UpdateGainDefaultValue();

public: ///////////////////////////////////////////// AAX_JuceContentView
	AAX_Result	setControlHighlightInfo (AAX_CParamID iParameterID, AAX_CBoolean iIsHighlighted, AAX_EHighlightColor iColor) AAX_OVERRIDE;
	AAX_Result	TimerWakeup() AAX_OVERRIDE;
	
	void SetViewContainer ( AAX_IViewContainer * inViewContainer ) AAX_OVERRIDE; //TODO: notification hook would be better
	
protected:
	void sliderDragStarted (juce::Slider* inSlider) override;
	void sliderValueChanged (juce::Slider * inSlider) override;
	void sliderDragEnded (juce::Slider* inSlider) override;
	void labelTextChanged (juce::Label * labelThatHasChanged) override;
	void buttonClicked (juce::Button* button) override;
	
private:
	DemoGain_SliderJuce		* mGainSlider;
	juce::Label		* mGainText;
	juce::Label		* mMonoText;
	juce::TextButton	* mResizeButton;
	juce::Label		* mInputMeterText;
	juce::Label		* mOutputMeterText;
	juce::Slider		* mInputMeter;
	juce::Slider 	* mOutputMeter;
};	

#endif
