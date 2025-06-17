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

#include "DemoDelay_HostProcessor.h"
#include "DemoDelay_Parameters.h"
#include "CSimpleDelayLine.h"


// *******************************************************************************
#pragma mark - Local constants

// Custom error values
const AAX_Result cDemoDelay_Error_InvalidRenderParams =			-9989;


// *******************************************************************************
#pragma mark - DemoDelay_HostProcessor ctor/dtor and factory methods

AAX_CHostProcessor *AAX_CALLBACK DemoDelay_HostProcessor::Create()
{
	return new DemoDelay_HostProcessor();
}

DemoDelay_HostProcessor::DemoDelay_HostProcessor() :
AAX_CHostProcessor(),
mDelayLines(NULL),
mDelaySamples(0)
{
}

DemoDelay_HostProcessor::~DemoDelay_HostProcessor()
{
	DeleteDelayLines();
}


// *******************************************************************************
#pragma mark - DemoDelay_HostProcessor public methods

AAX_Result DemoDelay_HostProcessor::RenderAudio (const float * const inAudioIns [], int32_t inAudioInCount, float * const inAudioOuts [], int32_t inAudioOutCount, int32_t * ioWindowSize)
{
	AAX_Result result = AAX_SUCCESS;
	
	if ((inAudioInCount == inAudioOutCount) && (NULL != ioWindowSize))
	{
		for (int32_t i = 0; i < inAudioInCount; ++i)
		{
			const float * const	inputBuffer  = inAudioIns [i];
			float       * const	outputBuffer = inAudioOuts [i];
			
			if ( inputBuffer && outputBuffer )
			{
				mDelayLines[i].ProcessSamples(*ioWindowSize, mDelaySamples, inputBuffer, outputBuffer);
			}
		}
    }
	else
	{
		result = cDemoDelay_Error_InvalidRenderParams;
	}
	
	return result;
}

AAX_Result DemoDelay_HostProcessor::PreRender (int32_t iAudioInCount, int32_t /*iAudioOutCount*/, int32_t /*iWindowSize*/)
{
	AAX_Result result = AAX_SUCCESS;
	
	CreateDelayLines(iAudioInCount);
	
	// Initialize mDelaySamples
	result = GetEffectParameters()->GetCustomData(DemoDelay_Parameters::sDataBlockID_DelaySamples, sizeof(int32_t), &mDelaySamples, NULL);
	
	return result;
}

AAX_Result DemoDelay_HostProcessor::PostRender ()
{
	DeleteDelayLines();
	return AAX_SUCCESS;
}

void DemoDelay_HostProcessor::CreateDelayLines(int32_t inNumDelayLines)
{
	DeleteDelayLines();
	mDelayLines = new CSimpleDelayLine[inNumDelayLines];
}

void DemoDelay_HostProcessor::DeleteDelayLines()
{
	if (NULL != mDelayLines)
	{
		delete[] mDelayLines;
		mDelayLines = NULL;
	}
}

