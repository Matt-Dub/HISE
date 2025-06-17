/*================================================================================================*/
/*
 *	Copyright 2016-2017, 2019, 2023-2024 Avid Technology, Inc.
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
 *	\brief  Algorithm component definitions for DemoGain.
 *
 *  \author Rob Majors
 */ 
/*================================================================================================*/

#pragma once
#ifndef DEMOGAIN_ALG_H
#define DEMOGAIN_ALG_H

#include "DemoGain_Defs.h"

// Standard includes
#include <math.h>		// for fabsf()
#include <algorithm>	// for max()

//==============================================================================
// Memory block structure definitions
//==============================================================================

#include AAX_ALIGN_FILE_BEGIN
#include AAX_ALIGN_FILE_ALG
#include AAX_ALIGN_FILE_END
	struct SDemoGain_CoefsGain
	{
        SDemoGain_CoefsGain()
		{
			for (int i = 0; i < cMaxNumChannels; ++i)
			{
				mGain[i] = 0.f;
			}
		}
		
		float mGain[cMaxNumChannels];
	};

    struct SDemoGain_RoutingMap
    {
        SDemoGain_RoutingMap()
        {
            for (int32_t routingIndex = 0; routingIndex < cMaxNumChannels; ++routingIndex)
                mRoutingMap[routingIndex] = routingIndex;
        }
        int32_t mRoutingMap[cMaxNumChannels];
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
	float*						* mInputPP;						// Audio signal destination
	float*						* mOutputPP;					// Audio signal source
	int32_t						* mBufferSizeP;					// Buffer size

	int32_t						* mCtrlBypassP;					// Control message destination
	SDemoGain_CoefsGain			* mCoefsGainP;					// Inter-component message destination
    SDemoGain_RoutingMap        * mRoutingMapP;

	float*						* mMetersPP;					// Meter taps
};

// Physical addresses within the context
enum EDemoGain_Alg_PortID
{
	 eAlgPortID_AudioIn						= AAX_FIELD_INDEX (SDemoGain_Alg_Context, mInputPP)
	,eAlgPortID_AudioOut					= AAX_FIELD_INDEX (SDemoGain_Alg_Context, mOutputPP)
	,eAlgPortID_BufferSize					= AAX_FIELD_INDEX (SDemoGain_Alg_Context, mBufferSizeP)

	,eAlgPortID_BypassIn					= AAX_FIELD_INDEX (SDemoGain_Alg_Context, mCtrlBypassP)
	,eAlgPortID_CoefsGainIn					= AAX_FIELD_INDEX (SDemoGain_Alg_Context, mCoefsGainP)
    ,eAlgPortID_RoutingMapIn                = AAX_FIELD_INDEX (SDemoGain_Alg_Context, mRoutingMapP)
    
	,eAlgPortID_Meters						= AAX_FIELD_INDEX (SDemoGain_Alg_Context, mMetersPP)
};

//==============================================================================
// Callback declarations
//==============================================================================
template <uint16_t kNumChannelsIn, uint16_t kNumChannelsOut>
void inline AAX_CALLBACK DemoGain_AlgorithmProcessFunction (
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
        const SDemoGain_CoefsGain * const AAX_RESTRICT coefsGainP = instance->mCoefsGainP;	// Input (const)
        const SDemoGain_RoutingMap * const AAX_RESTRICT routingP = instance->mRoutingMapP;  // Input (const)
        const int32_t	bypass		= *instance->mCtrlBypassP; // 'int' not 'bool' for optimization
        const int32_t	buffersize	= *instance->mBufferSizeP;
        
        // Meter taps
        float* const AAX_RESTRICT meterTaps = *instance->mMetersPP;
        float cmpLimMeterSum = 0;
        float expGateMeterSum = 0;

        for (uint16_t channel = 0; channel < kNumChannelsOut; ++channel)
        {
            // Audio channels
            // Route appropriate input channels to output ones
            const float* const AAX_RESTRICT pdI = instance->mInputPP [ routingP->mRoutingMap[channel] ];
            float* const AAX_RESTRICT pdO = instance->mOutputPP [channel];  
            // Gain
            const float gain = coefsGainP->mGain [channel];
            
            //--------- Run processing loop over each sample ---------//
            //
            for (int t = 0; t < buffersize; ++t)
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
            float inMeter = meterTaps [channel];
            float outMeter = meterTaps [channel + kNumChannelsIn];
            for (int t = 0; t < buffersize; ++t)
            {
                inMeter = std::max( fabsf(pdI [t]), inMeter );
                outMeter = std::max( fabsf(pdO [t]), outMeter );
            } // Go to the next sample

			meterTaps [channel] = inMeter;
			meterTaps [channel + kNumChannelsIn] = outMeter;
        } // End channel iteration loop

		meterTaps [kNumChannelsIn + kNumChannelsOut] = std::max( cmpLimMeterSum / kNumChannelsOut, meterTaps [kNumChannelsIn + kNumChannelsOut] );
        meterTaps [kNumChannelsIn + kNumChannelsOut + 1] = std::max( expGateMeterSum / kNumChannelsOut, meterTaps [kNumChannelsIn + kNumChannelsOut + 1] );

    } // End instance-iteration loop
}

#endif //DEMOGAIN_ALG_H
