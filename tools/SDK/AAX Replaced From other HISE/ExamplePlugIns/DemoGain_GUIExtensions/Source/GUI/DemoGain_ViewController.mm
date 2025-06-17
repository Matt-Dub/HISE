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
#import  "DemoGain_ViewController.h"

#include "DemoGain_String.h"
#include "DemoGain_Defs.h"

#include "AAX_IEffectParameters.h"
#include "AAX_IController.h"

class AAX_IViewContainer;

@implementation DemoGain_ViewController

@synthesize mGainSlider;
@synthesize mGainText;
@synthesize mInputLevelIndicator;
@synthesize mOutputLevelIndicator;

// *******************************************************
// METHOD:	SetParameters
// *******************************************************
- (void) SetParameters:(AAX_IEffectParameters *) iEffectParameters
{
  	mEffectParameters = iEffectParameters;
}

// *******************************************************
// METHOD:	SetController
// *******************************************************
- (void) SetController:(AAX_IController *) iController
{
  	mController = iController;
}

// *******************************************************
// METHOD:	SetViewContainerOnViews
// *******************************************************
- (void) SetViewContainerOnViews:(AAX_IViewContainer *) iViewContainer
{
	if ( mGainSlider )
	{
		[mGainSlider SetViewContainer:iViewContainer];
	}
}

// *******************************************************
// METHOD:	SetEffectParametersOnViews
// *******************************************************
- (void) SetEffectParametersOnViews:(AAX_IEffectParameters *) iEffectParameters
{
	if ( mGainSlider )
	{
		[mGainSlider SetEffectParameters:iEffectParameters];
	}
}

// *******************************************************
// METHOD:	ChangeGainSlider
// *******************************************************
-(IBAction) ChangeGainSlider:(id) iSender
{
	if ( mEffectParameters )
	{
		if ( mGainSlider )
		{
			double normalizedValue = 0.0;
			if ([mGainSlider GetDefaultCommandState])
			{
				AAX_Result err = mEffectParameters->GetParameterDefaultNormalizedValue (DemoGain_GainID, &normalizedValue );
				if (err != AAX_SUCCESS)
				{
					normalizedValue = 0.0;
				}
			}
			else
			{
				normalizedValue = [mGainSlider floatValue];
			}
			mEffectParameters->SetParameterNormalizedValue( DemoGain_GainID, normalizedValue );
		}
	}
}

// *******************************************************
// METHOD:	controlTextDidEndEditing
// *******************************************************
- (void) controlTextDidEndEditing:(NSNotification *)obj;
{
	if ( mEffectParameters )
	{
		if ( mGainText == [obj object] )
		{
			NSString * stringVal = [mGainText stringValue];
			double value;
			
			DemoGain_String textString;
			textString.Set((char *) [stringVal UTF8String]);
			
			mEffectParameters->GetParameterValueFromString ( DemoGain_GainID, &value, textString );
			mEffectParameters->SetParameterNormalizedValue( DemoGain_GainID, value );
		}
	}
}

// *******************************************************
// METHOD:	UpdateGainValues
// *******************************************************
- (void) UpdateGainValues
{
	if ( mEffectParameters )
	{
		if ( mGainSlider )
		{
			double	normalizedValue = 0;
			if ( mEffectParameters->GetParameterNormalizedValue( DemoGain_GainID, &normalizedValue ) == 0 )
			{
				[mGainSlider setFloatValue:normalizedValue];
			}
		}
		
		if ( mGainText )
		{				
			DemoGain_String valueString;
			if ( mEffectParameters->GetParameterValueString( DemoGain_GainID, &valueString, 29 ) == 0 )
			{
				[mGainText setStringValue:[NSString stringWithUTF8String:valueString.Get()]];
			}
		}
	}
}

// *******************************************************
// METHOD:	UpdateMeters
// *******************************************************
- (void) UpdateMeters
{
	if (mEffectParameters)
	{
		if (mInputLevelIndicator)
		{
			float meterVal;
			if (mController->GetCurrentMeterValue(cDemoGain_MeterID[0], &meterVal) == AAX_SUCCESS)
				[mInputLevelIndicator setFloatValue:meterVal];
		}
		
		if (mOutputLevelIndicator)
		{
			float meterVal;
			if (mController->GetCurrentMeterValue(cDemoGain_MeterID[1], &meterVal) == AAX_SUCCESS)
				[mOutputLevelIndicator setFloatValue:meterVal];			
		}
	}
}

// *******************************************************
// METHOD:	dealloc
// *******************************************************
- (void) dealloc 
{
    [super dealloc];
}


@end
