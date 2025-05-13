/*================================================================================================*/
/*
 *	Copyright 2013-2015, 2019, 2023-2024 Avid Technology, Inc.
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
 *	\file   DemoDelay_Alg.h
 *
 *	\brief  Algorithm component definitions for DemoDelay_Hybrid.
 *
 *  \author Dave Tremblay
 */ 
/*================================================================================================*/
#pragma once
#ifndef DemoDelay_ALG_H
#define DemoDelay_ALG_H



// AAX includes
#include "AAX.h"


//==============================================================================
// General definitions
//==============================================================================

// Meter layout
enum EDemoDelay_MeterTaps
{
	eMeterTap_Input = 0,
	eMeterTap_Output,

	eMeterTap_Count
};


//==============================================================================
// Algorithm Structures
//==============================================================================

#include AAX_ALIGN_FILE_BEGIN
#include AAX_ALIGN_FILE_ALG
#include AAX_ALIGN_FILE_END

// Gain coefficient structure (extend this to add more coeffs)
struct SDemoDelay_Coefs
{
    bool    mBypass;
    float	mDryGain;
    float   mWetGain;
};

// Context structure
struct SDemoDelayHybrid_LowLatency_Context
{
	SDemoDelay_Coefs		* mCoefsDelayP;					// Inter-component message destination
	
	float*					* mInputPP;						// Audio signal destination
	float*					* mOutputPP;					// Audio signal source
	int32_t					* mBufferLengthP;				// Buffer size

	float*					* mMeterOutputPP;				// Meter taps
};
#include AAX_ALIGN_FILE_BEGIN
#include AAX_ALIGN_FILE_RESET
#include AAX_ALIGN_FILE_END


//==============================================================================
// Callback declarations
//==============================================================================

void
AAX_CALLBACK
DemoDelay_AlgorithmProcessFunction (
    SDemoDelayHybrid_LowLatency_Context * const	inInstancesBegin [],
    const void *					inInstancesEnd);

#endif //DemoDelay_ALG_H
