/*================================================================================================*/
/*
 *	Copyright 2008-2015, 2019, 2023-2024 Avid Technology, Inc.
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
 *	\file   DemoGain_Alg.h
 *
 *	\brief  Algorithm component definitions for DemoGain_Smoothed.
 */ 
/*================================================================================================*/
#pragma once
#ifndef DEMOGAIN_ALG_H
#define DEMOGAIN_ALG_H



// AAX includes
#include "AAX.h"


//==============================================================================
// General definitions
//==============================================================================

// Meter layout
enum EDemoGain_MeterTaps
{
	eMeterTap_PreGain = 0,
	eMeterTap_PostGain,

	eMeterTap_Count
};


//==============================================================================
// Memory block structure definitions
//==============================================================================

#include AAX_ALIGN_FILE_BEGIN
#include AAX_ALIGN_FILE_ALG
#include AAX_ALIGN_FILE_END
	// Gain coefficient structure (extend this to add more coeffs)
	struct SDemoGain_CoefsGain
	{
		float	mGain;
	};
#include AAX_ALIGN_FILE_BEGIN
#include AAX_ALIGN_FILE_RESET
#include AAX_ALIGN_FILE_END

//==============================================================================
// Component context definitions
//==============================================================================

// Context structure
struct SDemoGain_Alg_Context
{
	const int32_t				* mCtrlBypassP;					// Control message destination
	const SDemoGain_CoefsGain	* mTargetCoefsGainP;			// Inter-component message destination

	SDemoGain_CoefsGain			* mCurCoefsGainP;				// Private data
	
	const float* const			* mInputPP;						// Audio signal destination
	float* const				* mOutputPP;					// Audio signal source
	const int32_t				* mBufferSize;					// Buffer size
	const AAX_CSampleRate		* mSampleRate;					// Sample rate

	float* const				* mMetersPP;					// Meter taps
};


// Physical addresses within the context
enum EDemoGain_Alg_PortID
{
	 eAlgPortID_BypassIn					= AAX_FIELD_INDEX (SDemoGain_Alg_Context, mCtrlBypassP)
	,eAlgPortID_TargetCoefsGainIn			= AAX_FIELD_INDEX (SDemoGain_Alg_Context, mTargetCoefsGainP)
	
	,eAlgPortID_CurCoefsGain				= AAX_FIELD_INDEX (SDemoGain_Alg_Context, mCurCoefsGainP)
	
	,eAlgFieldID_AudioIn					= AAX_FIELD_INDEX (SDemoGain_Alg_Context, mInputPP)
	,eAlgFieldID_AudioOut					= AAX_FIELD_INDEX (SDemoGain_Alg_Context, mOutputPP)
	,eAlgFieldID_BufferSize					= AAX_FIELD_INDEX (SDemoGain_Alg_Context, mBufferSize)
	,eAlgFieldID_SampleRate					= AAX_FIELD_INDEX (SDemoGain_Alg_Context, mSampleRate)

	,eAlgFieldID_Meters						= AAX_FIELD_INDEX (SDemoGain_Alg_Context, mMetersPP)
};


//==============================================================================
// Callback declarations
//==============================================================================

void
AAX_CALLBACK
DemoGain_AlgorithmProcessFunction (
    SDemoGain_Alg_Context * const	inInstancesBegin [],
    const void *					inInstancesEnd);

#endif //DEMOGAIN_ALG_H
