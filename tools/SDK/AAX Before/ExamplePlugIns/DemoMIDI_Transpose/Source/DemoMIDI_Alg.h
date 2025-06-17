/*================================================================================================*/
/*
 *	Copyright 2024 Avid Technology, Inc.
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
 *	\brief  Algorithm component definitions for DemoMIDI_Transpose.
 *
 *  \author Jakub Jankowski
 */ 
/*================================================================================================*/
#pragma once
#ifndef DEMOMIDI_ALG_H
#define DEMOMIDI_ALG_H

// DemoMIDI includes
#include "DemoMIDI_Defs.h"

// AAX includes
#include "AAX.h"
#include "AAX_IMIDINode.h"

//==============================================================================
// Component context definitions
//==============================================================================

#include AAX_ALIGN_FILE_BEGIN
#include AAX_ALIGN_FILE_ALG
#include AAX_ALIGN_FILE_END


// Structure that represents plugins coefficients
struct SCoefficients
{
	bool	mBypass;
	bool	mPassthrough;
	int32_t mTransposeValue;
	
	bool operator!=( const SCoefficients& inOther ) const;
	
	bool IsBypassDifferent( const SCoefficients& inOther ) const;
	bool IsPassthroughDifferent( const SCoefficients& inOther ) const;
	bool IsTransposeDifferent( const SCoefficients& inOther ) const;
};

// Structure that represents internal plugin data passed between callbacks
struct SPrivateData
{
	SCoefficients   mCoefficients; // Structure that holds coefficient data of previous iteration
	NoteDataSegment mIsTransposed[cNumNoteSegments]; // An array that represents transposed notes, one bit for each of the 128 notes
	NoteDataSegment mIsNoteOn[cNumNoteSegments]; // An array that represents notes that are currently "on"
};

// Context structure
struct SDemoMIDI_Alg_Context
{
	int32_t			* mpBufferSize;		 	// Buffer size
	int32_t			* mpNumAudioChannels;   // Runtime stem format information
	
	float*			* mppInput;			 	// Audio signal destination
	float*			* mppOutput;			// Audio signal source
	
	SCoefficients	* mpCoefficients;	   	// Current coefficients values
	
	AAX_IMIDINode	* mpMIDINodeIn;			// Buffered local MIDI input node
	AAX_IMIDINode	* mpMIDINodeOut;		// Buffered local MIDI output node
	
	SPrivateData	* mpPrivateData;		// Private data passed between instance callbacks
};

#include AAX_ALIGN_FILE_BEGIN
#include AAX_ALIGN_FILE_RESET
#include AAX_ALIGN_FILE_END

// Physical addresses within the context
enum EDemoMIDI_Alg_PortID
{
	eAlgFieldID_BufferSize			= AAX_FIELD_INDEX( SDemoMIDI_Alg_Context, mpBufferSize )
	,eAlgPortID_NumAudioChannels	= AAX_FIELD_INDEX( SDemoMIDI_Alg_Context, mpNumAudioChannels )
	,eAlgFieldID_AudioIn			= AAX_FIELD_INDEX( SDemoMIDI_Alg_Context, mppInput )
	,eAlgFieldID_AudioOut			= AAX_FIELD_INDEX( SDemoMIDI_Alg_Context, mppOutput )
	,eAlgPortID_Coefficients		= AAX_FIELD_INDEX( SDemoMIDI_Alg_Context, mpCoefficients )
	,eAlgPortID_MIDINodeIn			= AAX_FIELD_INDEX( SDemoMIDI_Alg_Context, mpMIDINodeIn )
	,eAlgPortID_MIDINodeOut			= AAX_FIELD_INDEX( SDemoMIDI_Alg_Context, mpMIDINodeOut )
	,eAlgPortID_PrivateData			= AAX_FIELD_INDEX( SDemoMIDI_Alg_Context, mpPrivateData )
};

//==============================================================================
// Callback declarations
//==============================================================================
void AAX_CALLBACK DemoMIDI_AlgorithmProcessFunction( SDemoMIDI_Alg_Context * const	inInstancesBegin [],
													 const void *					inInstancesEnd );
 
#endif // DEMOMIDI_ALG_H
