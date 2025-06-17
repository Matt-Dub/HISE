/*================================================================================================*/
/*
 *	Copyright 2013-2017, 2019, 2023-2024 Avid Technology, Inc.
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
 *	\file   DemoMIDI_Alg.h
 *
 *	\brief  Algorithm component definitions for DemoMIDI_NoteOn.
 *
 *  \author Danny Plazas
 */ 
/*================================================================================================*/
#pragma once
#ifndef DEMOMIDI_ALG_H
#define DEMOMIDI_ALG_H

// AAX includes
#include "AAX.h"
#include "AAX_IMIDINode.h"

//==============================================================================
// General definitions
//==============================================================================

// Meter layout
enum EDemoMIDI_MeterTaps
{
	eMeterTap_PreGain = 0,
	eMeterTap_PostGain,
	
	eMeterTap_Count
};

//==============================================================================
// Component context definitions
//==============================================================================

#include AAX_ALIGN_FILE_BEGIN
#include AAX_ALIGN_FILE_ALG
#include AAX_ALIGN_FILE_END

// Structure that holds data persisting between algorithm callbacks
struct SDemoMIDI_NoteBits
{
	uint32_t mIsOn[4]; // one bit flag for each of the 128 possible note values
	uint32_t mIsHeld[4]; // one bit flag for each of the 128 possible note values
	bool	 mHoldState; // current state of the note hold
	bool	 mBypassState; // holds the bypass state of the previous interation
};

// Context structure
struct SDemoMIDI_Alg_Context
{
	int32_t						* mCtrlBypassP;					// Control message destination
	float						* mGainP;						// Coefficient message destination
	int32_t						* mCtrlHoldP;
	
	AAX_IMIDINode				* mMIDINodeInP;					// Buffered local MIDI input node Pointer
	AAX_IMIDINode				* mMIDINodeOutPassThroughP;		// Buffered local MIDI output node Pointer
	
	SDemoMIDI_NoteBits			* mNoteData;					// Private data
	
	float*						* mInputPP;						// Audio signal destination
	float*						* mOutputPP;					// Audio signal source
	int32_t						* mBufferSizeP;					// Buffer size
	float*						* mMetersPP;					// Meter taps
};

#include AAX_ALIGN_FILE_BEGIN
#include AAX_ALIGN_FILE_RESET
#include AAX_ALIGN_FILE_END

// Physical addresses within the context
enum EDemoMIDI_Alg_PortID
{
	eAlgPortID_BypassIn				= AAX_FIELD_INDEX( SDemoMIDI_Alg_Context, mCtrlBypassP )
	,eAlgPortID_CoefsGainIn			= AAX_FIELD_INDEX( SDemoMIDI_Alg_Context, mGainP )
	,eAlgPortID_HoldIn				= AAX_FIELD_INDEX( SDemoMIDI_Alg_Context, mCtrlHoldP )
	,eAlgPortID_MIDINodeIn			= AAX_FIELD_INDEX( SDemoMIDI_Alg_Context, mMIDINodeInP )
	,eAlgPortID_MIDINodeOutPT		= AAX_FIELD_INDEX( SDemoMIDI_Alg_Context, mMIDINodeOutPassThroughP )
	,eAlgPortID_NoteData			= AAX_FIELD_INDEX( SDemoMIDI_Alg_Context, mNoteData )
	,eAlgFieldID_AudioIn			= AAX_FIELD_INDEX( SDemoMIDI_Alg_Context, mInputPP )
	,eAlgFieldID_AudioOut			= AAX_FIELD_INDEX( SDemoMIDI_Alg_Context, mOutputPP )
	,eAlgFieldID_BufferSize			= AAX_FIELD_INDEX( SDemoMIDI_Alg_Context, mBufferSizeP ) 
	,eAlgFieldID_Meters				= AAX_FIELD_INDEX( SDemoMIDI_Alg_Context, mMetersPP )
};

//==============================================================================
// Helper functions and utilities
//==============================================================================
namespace alg_utils
{
	constexpr uint32_t cStateFalse		 = 0;
	constexpr int	   cNumNotesPerSegment = 32;

	// Clears the note on bits
	inline void ClearNoteOnBits( SDemoMIDI_NoteBits* oNoteBits )
	{
		if ( oNoteBits )
		{
			oNoteBits->mIsOn[0] = 0x00000000;
			oNoteBits->mIsOn[1] = 0x00000000;
			oNoteBits->mIsOn[2] = 0x00000000;
			oNoteBits->mIsOn[3] = 0x00000000;
		}
	}

	// Clears the held note bits
	inline void ClearHeldNoteBits( SDemoMIDI_NoteBits* oNoteBits )
	{
		if ( oNoteBits )
		{
			oNoteBits->mIsHeld[0] = 0x00000000;
			oNoteBits->mIsHeld[1] = 0x00000000;
			oNoteBits->mIsHeld[2] = 0x00000000;
			oNoteBits->mIsHeld[3] = 0x00000000;
		}
	}
} // namespace

//==============================================================================
// Callback declarations
//==============================================================================
/*
 void
 AAX_CALLBACK
 DemoMIDI_AlgorithmProcessFunction (
 SDemoMIDI_Alg_Context * const	inInstancesBegin [],
 const void *					inInstancesEnd);
 */

#endif
