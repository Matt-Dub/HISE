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
		const int32_t	buffersize	= *instance->mBufferSize;
		// Audio channels
		const float* const AAX_RESTRICT pdI_L = instance->mInputPP [0]; // First channel
		const float* const AAX_RESTRICT pdI_R = instance->mInputPP [1]; // Second channel
		float* const AAX_RESTRICT pdO_L = instance->mOutputPP [0]; // First channel
		float* const AAX_RESTRICT pdO_R = instance->mOutputPP [1]; // Second channel
		// Meter taps
		float* const AAX_RESTRICT	meterTaps	= *instance->mMetersPP;
		// Coefficients
		float	gainL[2];
		float	gainR[2];
		gainL[eSide_Left] = coefsGainP->mGainL [ eSide_Left ];
		gainR[eSide_Left] = coefsGainP->mGainR [ eSide_Left ];
		gainL[eSide_Right] = coefsGainP->mGainL [ eSide_Right ];
		gainR[eSide_Right] = coefsGainP->mGainR [ eSide_Right ];
		
		//--------- Run processing loop over each sample ---------//
		//
		for (int t = 0; t < buffersize; t++)
		{
			// Process audio samples
			//
			pdO_L [t] = (gainL [eSide_Left] * pdI_L [t]) + (gainL [eSide_Right] * pdI_R [t]);
			pdO_R [t] = (gainR [eSide_Left] * pdI_L [t]) + (gainR [eSide_Right] * pdI_R [t]);
			
			if (bypass)
			{
				pdO_L [t] = pdI_L [t];
				pdO_R [t] = pdI_R [t];
			}
		} // Go to the next sample

		// Do metering
		//
		// Accumulate the max value for metering. This will get cleared for us by the shell
		// when it sends the accumulated value up to the host.
		for (int t = 0; t < buffersize; t++)
		{
			meterTaps[eMeterTap_PreGain_L] = std::max(fabsf(pdI_L [t]), meterTaps[eMeterTap_PreGain_L]);
			meterTaps[eMeterTap_PreGain_R] = std::max(fabsf(pdI_R [t]), meterTaps[eMeterTap_PreGain_R]);
			meterTaps[eMeterTap_PostGain_L] = std::max(fabsf(pdO_L [t]), meterTaps[eMeterTap_PostGain_L]);
			meterTaps[eMeterTap_PostGain_R] = std::max(fabsf(pdO_R [t]), meterTaps[eMeterTap_PostGain_R]);
		} // Go to the next sample
	} // End instance-iteration loop
}
