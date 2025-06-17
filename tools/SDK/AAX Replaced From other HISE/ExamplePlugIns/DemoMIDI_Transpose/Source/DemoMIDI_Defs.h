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
 *	\file   DemoMIDI_Defs.h
 *
 *	\brief  Common definitions shared by the DemoMIDI_Transpose classes
 *
 *  \author Jakub Jankowski
 */ 
/*================================================================================================*/
#pragma once
#ifndef DEMOMIDI_DEFS_H
#define DEMOMIDI_DEFS_H

// AAX includes
#include "AAX.h"			// for AAX_CTypeID

// Other includes
#include <utility>			// for std::pair
#include <array>			// for std:array

/*===================================================================================================*/
// Miscellaneous

using						NoteDataSegment		 	= uint32_t;

static constexpr int32_t	cNumStemFormats			= 34;
static constexpr int32_t	cNumNoteSegments		= 4;
static constexpr int32_t	cNumNotesPerSegment		= sizeof(NoteDataSegment) * 8;
static constexpr int32_t	cStateFalse				= 0;

static constexpr int32_t	cTransposeDefaultVal	= 0;
static constexpr int32_t	cTransposeMaxVal		= 12;
static constexpr int32_t	cTransposeMinVal		= - cTransposeMaxVal;
static constexpr int32_t	cTransposeSteps			= 2 * cTransposeMaxVal + 1;

static constexpr int32_t	cMaxMidiPitch			= 127;
static constexpr int32_t	cMinMidiPitch			= 0;

/*===================================================================================================*/
// Type, product, and relation IDs

static const AAX_CTypeID 	cDemoMIDI_ManufacturerID = 'AVID';
static const AAX_CTypeID 	cDemoMIDI_ProductID		 = 'DmTR';
static AAX_CEffectID	 	cEffectID_DemoMIDI		 = "com.avid.aax.sdk.demomidi.transpose";

// An array that holds plugin stem formats and IDs for them
static const std::array<std::pair<AAX_EStemFormat, AAX_CTypeID>, cNumStemFormats> cStemFormatsAndIds
{{
	{ AAX_eStemFormat_Mono,			'DTMO' },	// Mono
	{ AAX_eStemFormat_Stereo,		'DTST' },	// Stereo
	{ AAX_eStemFormat_LCR,			'DTLC' },	// LCR
	{ AAX_eStemFormat_LCRS,			'DTLS' },	// LCRS
	{ AAX_eStemFormat_Quad,			'DRQU' },	// Quad
	{ AAX_eStemFormat_5_0,			'DTFZ' },	// 5.0
	{ AAX_eStemFormat_5_1,			'DTFO' },	// 5.1
	{ AAX_eStemFormat_6_0,			'DTsZ' },	// 6.0
	{ AAX_eStemFormat_6_1,			'DTsO' },	// 6.1
	{ AAX_eStemFormat_7_0_SDDS,		'DTSZ' },	// 7.0 SDDS
	{ AAX_eStemFormat_7_1_SDDS,		'DTSO' },	// 7.1 SDDS
	{ AAX_eStemFormat_7_0_DTS,		'DDZd' },	// 7.0 DTS
	{ AAX_eStemFormat_7_1_DTS,		'DDOd' },	// 7.1 DTS
	{ AAX_eStemFormat_7_0_2,		'DSZT' },	// 7.0.2
	{ AAX_eStemFormat_7_1_2,		'DSOT' },	// 7.1.2
	{ AAX_eStemFormat_5_0_2,		'DFZT' },	// 5.0.2
	{ AAX_eStemFormat_5_1_2,		'DFOT' },	// 5.1.2
	{ AAX_eStemFormat_5_0_4,		'DFZf' },	// 5.0.4
	{ AAX_eStemFormat_5_1_4,		'DFOf' },	// 5.1.4
	{ AAX_eStemFormat_7_0_4,		'DSZf' },	// 7.0.4
	{ AAX_eStemFormat_7_1_4,		'DSOf' },	// 7.1.4
	{ AAX_eStemFormat_7_0_6,		'DVZs' },	// 7.0.6
	{ AAX_eStemFormat_7_1_6,		'DVOS' },	// 7.1.6
	{ AAX_eStemFormat_9_0_4,		'DNZf' },	// 9.0.4
	{ AAX_eStemFormat_9_1_4,		'DNOf' },	// 9.1.4
	{ AAX_eStemFormat_9_0_6,		'DNZs' },	// 9.0.6
	{ AAX_eStemFormat_9_1_6,		'DNOs' },	// 9.1.7
	{ AAX_eStemFormat_Ambi_1_ACN,	'DTAO' },	// Ambisonics (1st order)
	{ AAX_eStemFormat_Ambi_2_ACN,	'DTAT' },	// Ambisonics (2nd order)
	{ AAX_eStemFormat_Ambi_3_ACN,	'DTAH' },	// Ambisonics (3rd order)
	{ AAX_eStemFormat_Ambi_4_ACN,	'DTAf' },	// Ambisonics (4th order)
	{ AAX_eStemFormat_Ambi_5_ACN,	'DTAF' },	// Ambisonics (5th order)
	{ AAX_eStemFormat_Ambi_6_ACN,	'DTAs' },	// Ambisonics (6th order)
	{ AAX_eStemFormat_Ambi_7_ACN,	'DTAS' }	// Ambisonics (7th order)
}};

/*===================================================================================================*/
// Parameter IDs

static AAX_CParamID cDemoMIDI_TransposeID   = "Transpose";
static AAX_CParamID cDemoMIDI_PassthroughID = "Passthrough";
static AAX_CParamID cDemoMIDI_Coefficients  = "Coefficients";

#endif // DEMOMIDI_DEFS_H
