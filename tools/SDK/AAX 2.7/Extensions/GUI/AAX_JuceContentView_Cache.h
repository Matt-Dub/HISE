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

/**	
 *  \file AAX_JuceContentView_Cache.h
 *
 */
/*================================================================================================*/
#pragma once
#ifndef AAX_JuceContentView_Cache_H
#define AAX_JuceContentView_Cache_H

#include "AAX.h"

#if AAX_SDK_JUCE_MAJOR_VERSION >= 7
#include "juce_core/juce_core.h"
#include "juce_gui_basics/juce_gui_basics.h"
#else
#include "juce.h"
#endif

#include <map>

class AAX_CEffectGUI;
class AAX_JuceContentView;

//==============================================================================
// CLASS:	AAX_JuceContentView_Cache
//==============================================================================
class AAX_JuceContentView_Cache : public juce::DeletedAtShutdown
{
public:
	virtual ~AAX_JuceContentView_Cache ();
	
	static bool add ( AAX_CEffectGUI * inEffectGUI, AAX_JuceContentView * inContentView );
	static AAX_JuceContentView * get ( AAX_CEffectGUI * inEffectGUI );
	
private:
	void doAdd ( AAX_EStemFormat inInputStemFormat, AAX_EStemFormat inOutputStemFormat, AAX_JuceContentView * inContentView );
	AAX_JuceContentView * doGet ( AAX_EStemFormat inInputStemFormat, AAX_EStemFormat inOutputStemFormat );
	bool getStemFormats ( AAX_CEffectGUI * inEffectGUI, AAX_EStemFormat * outInputStemFormat, AAX_EStemFormat * outOutputStemFormat );
	
private:
	typedef std::pair<AAX_EStemFormat,AAX_EStemFormat>		TStemPair;
	typedef std::multimap<TStemPair,AAX_JuceContentView *>	TContentMap;
	TContentMap												mContentViews;
};

#endif
