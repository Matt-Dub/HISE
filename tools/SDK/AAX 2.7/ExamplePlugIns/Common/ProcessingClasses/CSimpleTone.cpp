/*================================================================================================*/
/*
 *	Copyright 2014-2015, 2018, 2023-2024 Avid Technology, Inc.
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

// Self Include
#include "CSimpleTone.h"

// Standard Includes
#include <cmath>
#include <climits>
#include <algorithm>



// *******************************************************************************
// Private utility functions
// *******************************************************************************

static float MIDINoteToHz(unsigned char inMIDINoteVal, float inAHz)
{
	static const float sOneOverTwelve = (1.f/12.f);
	return (inAHz * powf(2.f, sOneOverTwelve * (inMIDINoteVal-69))); // 69 == Reference A
}

static unsigned char HzToMIDINote(float inHz, float inAHz)
{
	static const float sThirtyTwoTimesTwoToTheThreeQuarters = 32.f * powf(2.f, 0.75f);
	static const float sTwelveOverLogTwo = 12.f / log(2.f);
	const float noteFlt = sTwelveOverLogTwo * log((sThirtyTwoTimesTwoToTheThreeQuarters * inHz)/inAHz);
	return (unsigned char)((noteFlt > (UCHAR_MAX-0.5f)) ? UCHAR_MAX : noteFlt + 0.5f); // Rounding
}

static float MIDIVelocityToAmplitude(unsigned char inMIDIVelocity)
{
	static const float sOneOverOneTwentySeven = (1.f/127.f);
	return (sOneOverOneTwentySeven * inMIDIVelocity); // Linear amplitude scaling
}


// *******************************************************************************
// CSimpleTone
// *******************************************************************************
CSimpleTone::CSimpleTone()
: mSampleRateHz(0)
, mMIDINoteVal(0)
, mCurPos(0.0f)
, mAHz(440.0f)
, mHz(MIDINoteToHz(mMIDINoteVal, mAHz))
, mAmplitude(MIDIVelocityToAmplitude(0))
{
}

CSimpleTone::CSimpleTone(int32_t inSampleRateHz, float inAHz)
: mSampleRateHz(inSampleRateHz)
, mMIDINoteVal(0)
, mCurPos(0.0f)
, mAHz(inAHz)
, mHz(MIDINoteToHz(mMIDINoteVal, mAHz))
, mAmplitude(MIDIVelocityToAmplitude(0))
{
}

CSimpleTone::CSimpleTone(unsigned char inMIDINoteVal, unsigned char inMIDIVelocity, int32_t inSampleRateHz, float inAHz)
: mSampleRateHz(inSampleRateHz)
, mMIDINoteVal(inMIDINoteVal)
, mCurPos(0.0f)
, mAHz(inAHz)
, mHz(MIDINoteToHz(mMIDINoteVal, mAHz))
, mAmplitude(MIDIVelocityToAmplitude(inMIDIVelocity))
{
}

bool CSimpleTone::IsEnabled() const
{
	return (0.0f < mAmplitude && 0.0f < mSampleRateHz);
}

void CSimpleTone::SetMIDINote(unsigned char inMIDINoteVal, unsigned char inMIDIVelocity)
{
	mMIDINoteVal = inMIDINoteVal;
	mHz = MIDINoteToHz(mMIDINoteVal, mAHz);
	mAmplitude = MIDIVelocityToAmplitude(inMIDIVelocity);
}

void CSimpleTone::SetFrequency(float inHz)
{
	mMIDINoteVal = HzToMIDINote(inHz, mAHz);
	mHz = inHz;
}

void CSimpleTone::SetAmplitude(float inAmplitude)
{
	mAmplitude = std::max(0.f, std::min(1.f, inAmplitude));
}

void CSimpleTone::SetTuning(float inAHz)
{
	mAHz = inAHz;
	mHz = MIDINoteToHz(mMIDINoteVal, mAHz);
}

float CSimpleTone::ProcessOneSample(const IToneGeneratorDelegate& inDelegate)
{
	// Increment internal position
	mCurPos = ((0 == mSampleRateHz) ? mCurPos : fmodf(mCurPos + (mHz / mSampleRateHz), 2.f));
	
	// Compute a sample using the delegate
	return (inDelegate.Sample(*this) * mAmplitude);
}


// *******************************************************************************
// CSawToneGeneratorDelegate
// *******************************************************************************
float CSawToneGeneratorDelegate::Sample(const ISimpleTone& inDelegator) const
{
	return (inDelegator.CurPos() - 1.0f);
}


// *******************************************************************************
// CTriangleToneGeneratorDelegate
// *******************************************************************************
float CTriangleToneGeneratorDelegate::Sample(const ISimpleTone& inDelegator) const
{
	const float doubleRampValue = (inDelegator.CurPos()*2.0f);
	return (doubleRampValue > 2.0f ? (2.0f - doubleRampValue) + 1.0f : doubleRampValue - 1.0f);
			
}


// *******************************************************************************
// CSquareToneGeneratorDelegate
// *******************************************************************************
float CSquareToneGeneratorDelegate::Sample(const ISimpleTone& inDelegator) const
{
	return (inDelegator.CurPos() > 1.0f ? 1.0f : -1.0f);
}
