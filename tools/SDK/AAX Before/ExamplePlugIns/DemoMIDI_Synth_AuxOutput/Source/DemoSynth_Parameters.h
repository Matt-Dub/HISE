/*================================================================================================*/
/*
 *	Copyright 2012-2015, 2019, 2023-2024 Avid Technology, Inc.
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
 *	\file   DemoSynth_Parameters.h
 *
 *	\brief  DemoSynth_Parameters class declaration.
 *
 *  \author Andriy Goshko
 */ 
/*================================================================================================*/ 
#pragma once
#ifndef DEMOSYNTH_PARAMETERS_H
#define DEMOSYNTH_PARAMETERS_H

// DemoSynth Includes
#include "DemoSynth_Defs.h"

// AAX Includes
#include "AAX_CMonolithicParameters.h"
#include "AAX_CMutex.h"

// Standard Includes
#include <map>
#include <set>
#include <vector>
#include <list>
#include <utility>

class AAX_IParameter;
class CSimpleSynth;

//==============================================================================
class DemoSynth_Parameters : public AAX_CMonolithicParameters
{
public:
	DemoSynth_Parameters (void);
	~DemoSynth_Parameters (void) AAX_OVERRIDE;
	
	static AAX_CEffectParameters *AAX_CALLBACK	Create();
	
public:
	//Overrides from AAX_CMonolithicParameters
	AAX_Result	EffectInit() AAX_OVERRIDE;
	AAX_Result	UpdateParameterNormalizedValue(AAX_CParamID iParamID, double aValue, AAX_EUpdateSource inSource) AAX_OVERRIDE;
	void		RenderAudio(AAX_SInstrumentRenderInfo* ioRenderInfo, const TParamValPair* inSynchronizedParamValues[], int32_t inNumSynchronizedParamValues) AAX_OVERRIDE;
	
private:
	void		InitializeSynthesizerState(CSimpleSynth& ioSynth, int32_t inIndex);
	void		UpdateCoefficients(const TParamValPair* inSynchronizedParamValues[], int32_t inNumSynchronizedParamValues);
	void		ProcessInputMIDI(CSimpleSynth& ioSynth, uint32_t inSample, AAX_CMidiPacket*& ioPacket, uint32_t& ioPacketsRemaining);
	
	static const std::vector<AAX_IString*>& GetNodeAssignmentStateStrings();
	
private:
	enum ENodeAssignment
	{
		eNodeAssignment_None = 0 // Node is muted
		,eNodeAssignment_Direct = 1 // Assign to only the plug-in's immediate audio output
		,eNodeAssignment_All = 2 // Assign to the plug-in's immediate audio output and to all AOS stems
		,eNodeAssignment_SingleStemBegin = 3 // First index for single-AOS assignment selectors
		,eNodeAssignment_SingleStemEnd = eNodeAssignment_SingleStemBegin + kNumAuxOutputStems // One-past-the-last index for single-AOS assignment selectors
		
		,eNodeAssignment_NumStates = eNodeAssignment_SingleStemEnd
		,eNodeAssignment_Default = eNodeAssignment_Direct
	};
	
private:
	ENodeAssignment		mNodeAssignments[kNumAuxOutputStems];
	std::vector<CSimpleSynth> mSynthesizers;
};

#endif
