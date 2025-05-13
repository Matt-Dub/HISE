/*================================================================================================*/
/*
 *	Copyright 2013-2015, 2023-2024 Avid Technology, Inc.
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
 *	\file  AAX_RandomGen.h
 *
 *	\brief Functions for calculating pseudo-random numbers 
 *
 */ 
/*================================================================================================*/
#pragma once

#ifndef AAX_RANDOMGEN_H
#define AAX_RANDOMGEN_H

// Standard headers
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#include "AAX_PlatformOptimizationConstants.h"
#include "AAX_Constants.h"

namespace AAX
{

const float cSeedDivisor = 1/127773.0f;

const int32_t cInitialSeedValue=0x00F54321;

/*===================================================================================================*/
inline int32_t GetInt32RPDF(int32_t* iSeed)
{
    // Requirement: iSeed param must be a static in the calling function.
    int64_t seed = *iSeed;
    int64_t k = static_cast<int64_t>(seed*cSeedDivisor);
    seed = 16807 * (seed - k * 127773LL) - 2836 * k + 7395;
    *iSeed = static_cast<int32_t>(seed);
    if (*iSeed < 0) 
        *iSeed += 2147483647;
    return (*iSeed - 1073741824) * 2;       // -2147483647..+2147483647
}

/*===================================================================================================*/


/*!
 *  \brief CALL: Calculate pseudo-random 32 bit number based on linear congruential method.  
 *
 *	This is required if you want our master bypass functionality in the host to hook up to 
 *	your bypass parameters.
 *
 *	\param[in] iSeed
 *		Seed for random generator
 *
 *	\note This method produces lower quality random numbers (i.e. less random) than plain old 
 *	GetInt32RPDF, but in many cases it should be plenty good.
 */
inline int32_t GetFastInt32RPDF(int32_t* iSeed)
{
   *iSeed = (*iSeed * 196314165) + 907633515;
   return *iSeed;
}

/*===================================================================================================*/
inline float GetRPDFWithAmplitudeOneHalf(int32_t* iSeed)		//An amplitude of 0.5 = 1 LSBs
{
	// Requirement: iSeed param must be a static in the calling function.
	return float(cNormalizeLongToAmplitudeOneHalf) * float(GetInt32RPDF(iSeed));
}

/*===================================================================================================*/
inline float GetRPDFWithAmplitudeOne(int32_t* iSeed)			//An amplitude of 1.0 = 2 LSBs
{
	// Requirement: iSeed param must be a static in the calling function.
	return float(cNormalizeLongToAmplitudeOne) * float(GetInt32RPDF(iSeed));
}

/*===================================================================================================*/
inline float GetFastRPDFWithAmplitudeOne(int32_t* iSeed)			//An amplitude of 1.0 = 2 LSBs
{
	// Requirement: iSeed param must be a static in the calling function.
	return float(cNormalizeLongToAmplitudeOne) * float(GetFastInt32RPDF(iSeed));
}

/*===================================================================================================*/
inline float GetTPDFWithAmplitudeOne(int32_t* iSeed)			//An amplitude of 1.0 = 2 LSBs
{
	// Generate a random number with a triangular pdf (tpdf) using two 
	// separate rectangular pdf noise sources.

	// We are using only one seed input for both rect pdf noise generators, 
	// but because they are of course executed sequentially independent noise 
	// will be produced.

	return float(cNormalizeLongToAmplitudeOne) * (float(GetFastInt32RPDF(iSeed) + float(GetFastInt32RPDF(iSeed))));
}

} // namespace AAX

#endif // AAX_RANDOMGEN_H

