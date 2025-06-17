/*================================================================================================*/
/*
 *	Copyright 2011-2015, 2017, 2023-2024 Avid Technology, Inc.
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
#include "AAX_JuceContentView_Cache.h"
#include "AAX_CEffectGUI_Juce.h"

#include "AAX_IController.h"

static AAX_JuceContentView_Cache *	sCache = 0;

// *******************************************************************************
// METHOD: ~AAX_JuceContentView_Cache
// *******************************************************************************
AAX_JuceContentView_Cache::~AAX_JuceContentView_Cache ()
{
	JUCE_AUTORELEASEPOOL
	
	sCache = 0;
	TContentMap::iterator iter = mContentViews.begin ();
	for ( ; iter != mContentViews.end (); ++iter )
	{
		AAX_JuceContentView * contentView = iter->second;
		deleteAndZero ( contentView );
	}

	if (AAX_CEffectGUI_Juce::sTooltipWindow)
	{
		delete AAX_CEffectGUI_Juce::sTooltipWindow;
		AAX_CEffectGUI_Juce::sTooltipWindow = NULL;
	}
}

// *******************************************************************************
// METHOD: add
// *******************************************************************************
bool AAX_JuceContentView_Cache::add ( AAX_CEffectGUI * inEffectGUI, AAX_JuceContentView * inContentView )
{
	if ( ! sCache )
		sCache = new AAX_JuceContentView_Cache;
	
	if ( sCache )
	{
		if ( inEffectGUI )
		{
			AAX_EStemFormat	inputStemFormat, outputStemFormat;
			if ( sCache->getStemFormats ( inEffectGUI, & inputStemFormat, & outputStemFormat ) )
			{
				sCache->doAdd ( inputStemFormat, outputStemFormat, inContentView );
				inContentView->SetEffectGUI ( 0 );
				return true;
			}
		}
	}
	
	return false;
}

// *******************************************************************************
// METHOD: getStemFormats
// *******************************************************************************
AAX_JuceContentView * AAX_JuceContentView_Cache::get ( AAX_CEffectGUI * inEffectGUI )
{
	if ( sCache )
	{
		if ( inEffectGUI )
		{
			AAX_EStemFormat	inputStemFormat, outputStemFormat;
			if ( sCache->getStemFormats ( inEffectGUI, & inputStemFormat, & outputStemFormat ) )
				return sCache->doGet ( inputStemFormat, outputStemFormat );
		}
	}
	
	return 0;
}
	
// *******************************************************************************
// METHOD: getStemFormats
// *******************************************************************************
void AAX_JuceContentView_Cache::doAdd ( AAX_EStemFormat inInputStemFormat, AAX_EStemFormat inOutputStemFormat, AAX_JuceContentView * inContentView )
{
	TStemPair	stemPair ( inInputStemFormat, inOutputStemFormat );
	mContentViews.insert ( std::pair<TStemPair,AAX_JuceContentView *> ( stemPair, inContentView ) );
}
	
// *******************************************************************************
// METHOD: getStemFormats
// *******************************************************************************
AAX_JuceContentView * AAX_JuceContentView_Cache::doGet ( AAX_EStemFormat inInputStemFormat, AAX_EStemFormat inOutputStemFormat )
{
	AAX_JuceContentView *	result = 0;
	TStemPair	stemPair ( inInputStemFormat, inOutputStemFormat );
	TContentMap::iterator iter = mContentViews.find ( stemPair );
	if ( iter != mContentViews.end () )
	{
		result = iter->second;
		result->clearControlHighlightInfo ();
		
		mContentViews.erase ( iter );
	}
	
	return result;
}

// *******************************************************************************
// METHOD: getStemFormats
// *******************************************************************************
bool AAX_JuceContentView_Cache::getStemFormats ( AAX_CEffectGUI * inEffectGUI, AAX_EStemFormat * outInputStemFormat, AAX_EStemFormat * outOutputStemFormat )
{
	if ( inEffectGUI )
	{
		AAX_IController * controller = inEffectGUI->GetController ();
		if ( controller )
		{
			if ( controller->GetInputStemFormat ( outInputStemFormat ) != AAX_SUCCESS )
				return false;
			
			if ( controller->GetOutputStemFormat ( outOutputStemFormat ) != AAX_SUCCESS )
				return false;
			
			return true;
		}
	}
	
	return false;
}
