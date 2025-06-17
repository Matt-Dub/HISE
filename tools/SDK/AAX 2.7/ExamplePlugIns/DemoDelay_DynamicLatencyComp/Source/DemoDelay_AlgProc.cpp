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

// Component includes
#include "DemoDelay_Alg.h"

// DemoDelay includes
#include "CSimpleDelayLine.h"

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
DemoDelay_AlgorithmProcessFunction (
	SDemoDelay_AlgContext * const	inInstancesBegin [],
	const void *					inInstancesEnd)
{
	// Iterate over plug-in instances
    SDemoDelay_AlgContext* AAX_RESTRICT instance = inInstancesBegin [0];
	for (SDemoDelay_AlgContext * const * walk = inInstancesBegin; walk < inInstancesEnd; ++walk)
	{
		instance = *walk;
		
		//
		// Cache the context pointers
		//
		
		const SDemoDelay_Coefs* const AAX_RESTRICT coefsGainP = instance->mCoefsDelayP;
		const int32_t delaySamples = *instance->mDelaySamplesP;
		const int32_t numSamples = *instance->mBufferLengthP;
		CSimpleDelayLine* const AAX_RESTRICT delayLineP = instance->mDelayLineP;
        const float* const AAX_RESTRICT audioInput = instance->mInputPP[0];
		float* const AAX_RESTRICT audioOutput = instance->mOutputPP[0];
		
		// Coefficients
		const float dryGain = coefsGainP->mDryGain;
        const float wetGain = coefsGainP->mWetGain;
		
		
		//
		// Process audio samples
		//
		
		// Calculate the wet (delayed) signal
		delayLineP->ProcessSamples(numSamples, delaySamples, audioInput, audioOutput);
		
		// Apply gain processing and mix in the dry signal
        for (int32_t n = 0; n < numSamples; n++)
        {
            audioOutput[n] *= wetGain;					// Trim the wet signal
            audioOutput[n] += dryGain * audioInput[n];	// Trim and mix in the dry signal
        }
		
		// Do metering
		float* const AAX_RESTRICT	meterOutput	= *instance->mMeterOutputPP;
		for (int32_t n = 0; n < numSamples; n++)
		{
			meterOutput[eMeterTap_Input] = std::max(fabsf(audioInput[n]), meterOutput[eMeterTap_Input]);
			meterOutput[eMeterTap_Output] = std::max(fabsf(audioOutput[n]), meterOutput[eMeterTap_Output]);
		} 
	} 
}
