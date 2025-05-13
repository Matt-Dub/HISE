/*================================================================================================*/
/*
 *	Copyright 2014-2015, 2023-2024 Avid Technology, Inc.
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
// Host Alg wrapper shim headers
#include "DemoDist_Alg.h"
#include "DemoDist_AlgProc.cpp"		// Needed for templates
#include "AAX.h"

#include "../TI/CCSv5/elf_linkage_aax_ccsv5.h"

const AAX_EStemFormat kStemFormat = AAX_eStemFormat_Mono;
const int kNumChannels = AAX_STEM_FORMAT_CHANNEL_COUNT(kStemFormat);

// The main algorithm entry point
extern "C"
TI_EXPORT
void AlgEntry(	SDemoDist_Alg_Context * const		inInstancesBegin [],
				const void *						inInstancesEnd)
{
	DemoDist_AlgorithmProcessFunction<kNumChannels, kNumChannels>(
		inInstancesBegin,
		inInstancesEnd);
}
