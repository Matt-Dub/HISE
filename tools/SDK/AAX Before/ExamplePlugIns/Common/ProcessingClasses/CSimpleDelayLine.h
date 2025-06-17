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
 *	\file   CSimpleDelayLine.h
 *
 *  \author Rob Majors
 */ 
/*================================================================================================*/

#ifndef __DemoDelay__CSimpleDelayLine__
#define __DemoDelay__CSimpleDelayLine__

#include <stdint.h>


class CSimpleDelayLine
{
public:
	CSimpleDelayLine();
	~CSimpleDelayLine();
	
	static int32_t GetMaxDelay() { return sDelayLineLength; }
	
	void ProcessSamples(int32_t inNumSamples, uint32_t inDelaySamples, const float* inAudioInput, float* outAudioOutput);
	void Clear();
	
private:
	// 500 ms @ 192k = 57600. (fits in 2^16 samples)
	static const uint32_t sDelayLineLength = 2 << 15;
	static const uint32_t sDelayLineMask = sDelayLineLength - 1;
	
	int32_t mPos;
	float mDelayLine[sDelayLineLength];
};

#endif /* defined(__DemoDelay__CSimpleDelayLine__) */
