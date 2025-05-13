/*================================================================================================*/
/*
 *	Copyright 2008-2015, 2023-2024 Avid Technology, Inc.
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


// Component includes
#include "DemoGain_Alg.h"

// AAX includes
#include "AAX.h"

// Standard includes
#include <math.h>		// for fabsf()
#include <algorithm>	// for max()



//==============================================================================
// Processing function definition
//==============================================================================

void
AAX_CALLBACK
DemoGain_AlgorithmProcessFunction (
	SDemoGain_Alg_Context * const	inInstancesBegin [],
	const void *					inInstancesEnd)
{
	// Get a pointer to the beginning of the memory block table
	SDemoGain_Alg_Context* AAX_RESTRICT instance = inInstancesBegin [0];


	//--------- Iterate over plug-in instances ---------//
	//
	for (SDemoGain_Alg_Context * const * walk = inInstancesBegin; walk < inInstancesEnd; ++walk)
	{
		instance = *walk;

		//--------- Retrieve instance-specific information ---------//
		//
		// Memory blocks
		const SDemoGain_CoefsGain* const AAX_RESTRICT	coefsGainP =	instance->mCoefsGainP;	// Input (const)		
		const int32_t	bypass		= *instance->mCtrlBypassP; // 'int' not 'bool' for optimization
		const float		gain		= coefsGainP->mGain;
		const int32_t	buffersize	= *instance->mBufferSize;
		// Audio channels
		const float* const AAX_RESTRICT pdI = instance->mInputPP [0]; // First channel
		float* const AAX_RESTRICT pdO = instance->mOutputPP [0]; // First channel
		// Meter taps
		float* const AAX_RESTRICT	meterTaps	= *instance->mMetersPP;

		//--------- Run processing loop over each sample ---------//
		//
		for (int t = 0; t < buffersize; t++)
		{
			// Process audio samples
			//
			pdO [t] = gain * pdI [t];
			if (bypass) { pdO [t] = pdI [t]; }
		} // Go to the next sample

		// Do metering
		//
		// Accumulate the max value for metering. This will get cleared for us by the shell
		// when it sends the accumulated value up to the host.
		for (int t = 0; t < buffersize; t++)
		{
			meterTaps[eMeterTap_PreGain] = std::max(fabsf(pdI [t]), meterTaps[eMeterTap_PreGain]);
			meterTaps[eMeterTap_PostGain] = std::max(fabsf(pdO [t]), meterTaps[eMeterTap_PostGain]);
		} // Go to the next sample
	} // End instance-iteration loop
}
