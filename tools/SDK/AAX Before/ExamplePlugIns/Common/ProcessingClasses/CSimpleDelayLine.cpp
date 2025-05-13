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
/*================================================================================================*/

#include "CSimpleDelayLine.h"

#include <cstring>


//==============================================================================
// CSimpleDelayLine definition
//==============================================================================

CSimpleDelayLine::CSimpleDelayLine()
: mPos(0)
{
	Clear();
}

CSimpleDelayLine::~CSimpleDelayLine()
{
}

void CSimpleDelayLine::ProcessSamples(int32_t inNumSamples, uint32_t inDelaySamples, const float* inAudioInput, float* outAudioOutput)
{
    //Write the new values into the delay line and pull the output values out.
    for (int32_t index=0; index < inNumSamples; ++index, ++mPos)
    {
        mDelayLine[mPos & sDelayLineMask] = inAudioInput[index];
        outAudioOutput[index] = mDelayLine[(mPos-inDelaySamples) & sDelayLineMask];
    }
}

void CSimpleDelayLine::Clear()
{
	std::memset(mDelayLine, 0, sDelayLineLength*sizeof(float));
}
