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
 *	\brief  Algorithm component definitions for DemoGain_LinkedParameters.
 *
 *  \author Rob Majors
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
	eMeterTap_PreGain_L = 0,
	eMeterTap_PreGain_R,
	eMeterTap_PostGain_L,
	eMeterTap_PostGain_R,

	eMeterTap_Count
};

// Gain type definitions
enum DemoGain_EType
{
	eType_Pan = 0,
	eType_Gain,
	
	eType_NumTypes
}; AAX_ENUM_SIZE_CHECK(DemoGain_EType); // Ensure 32-bit

// Gain side IDs
enum DemoGain_ESide
{
	eSide_Left = 0,
	eSide_Right,
	
	eSide_NumSides
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
		float	mGainL[2];
		float	mGainR[2];
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
	int32_t						* mCtrlBypassP;					// Control message destination

	SDemoGain_CoefsGain			* mCoefsGainP;					// Inter-component message destination
	
	float*						* mInputPP;						// Audio signal destination
	float*						* mOutputPP;					// Audio signal source
	int32_t						* mBufferSize;					// Buffer size

	float*						* mMetersPP;					// Meter taps
};


// Physical addresses within the context
enum EDemoGain_Alg_PortID
{
	 eAlgPortID_BypassIn					= AAX_FIELD_INDEX (SDemoGain_Alg_Context, mCtrlBypassP)
	,eAlgPortID_CoefsGainIn					= AAX_FIELD_INDEX (SDemoGain_Alg_Context, mCoefsGainP)
	
	,eAlgFieldID_AudioIn					= AAX_FIELD_INDEX (SDemoGain_Alg_Context, mInputPP)
	,eAlgFieldID_AudioOut					= AAX_FIELD_INDEX (SDemoGain_Alg_Context, mOutputPP)
	,eAlgFieldID_BufferSize					= AAX_FIELD_INDEX (SDemoGain_Alg_Context, mBufferSize)

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
