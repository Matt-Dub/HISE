/*================================================================================================*/
/*
 *	Copyright 2015, 2023-2024 Avid Technology, Inc.
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
#include "CSimpleSynth.h"

// Standard Includes
#include <cstddef>


CSimpleSynth::CSimpleSynth()
: mVoices()
, mBypassed(false)
, mGain(1.f)
, mToneGenerator(NULL)
{
}


void CSimpleSynth::SetBypass(bool inBypass) { mBypassed = inBypass; }
void CSimpleSynth::SetGain(float inGain) { mGain = inGain; }
void CSimpleSynth::SetWaveType(EWaveType inWaveType) { mToneGenerator = GetToneGenerator(inWaveType); }

void CSimpleSynth::SetTuning(float inAHz)
{
	for (size_t voiceNum = MaxNumVoices(); voiceNum > 0; --voiceNum)
	{
		mVoices[voiceNum-1].SetTuning(inAHz);
	}
}

void CSimpleSynth::InitializeVoices(float inSampleRate, float inAHz)
{
	for (size_t voiceNum = MaxNumVoices(); voiceNum > 0; --voiceNum)
	{
		mVoices[voiceNum-1] = CSimpleTone((int32_t)inSampleRate, inAHz);
	}
}

int32_t CSimpleSynth::MaxNumVoices() const
{
	// size of mVoices will always be the same
	static const int32_t sVoices = static_cast<int32_t>(sizeof(mVoices) / sizeof(CSimpleTone));
	return sVoices;
}

/* static */ const char* CSimpleSynth::GetWaveTypeName(EWaveType inWaveType)
{
	switch (inWaveType)
	{
		case eWaveType_Saw: return "Saw";
		case eWaveType_Tri: return "Tri";
		case eWaveType_Square: return "Square";
		default: return "<unknown>";
	}
}

void CSimpleSynth::GetSamples(float* outBuffer, int32_t outBufferSize)
{
	// Count the active voices
	size_t numActiveVoices = 0;
	for (size_t voiceNum = MaxNumVoices(); voiceNum > 0; --voiceNum)
	{
		if (mVoices[voiceNum-1].IsEnabled())
		{
			++numActiveVoices;
		}
	}
	
	// Generate samples using a simple sample-by-sample procedure
	for (int32_t i = 0; i < outBufferSize; ++i)
	{
		float sample = 0.f;
		for (size_t voiceNum = MaxNumVoices(); voiceNum > 0; --voiceNum)
		{
			ISimpleTone& curVoice = mVoices[voiceNum-1];
			if (curVoice.IsEnabled())
			{
				const float curNormalizedSample = (curVoice.ProcessOneSample(*mToneGenerator));
				sample += curNormalizedSample;
			}
		}
		
		// Scale output by the number of active voices to avoid overload
		sample = (mBypassed || 0 == numActiveVoices) ? 0.f : mGain * (sample / numActiveVoices);
		outBuffer[i] = sample;
	}
}

void CSimpleSynth::HandleNoteOn(unsigned char inNote, unsigned char inVelocity)
{
	if (inNote < MaxNumVoices())
	{
		// Use inNote as the key into the mVoices array
		mVoices[inNote].SetMIDINote(inNote, inVelocity);
	}
}

void CSimpleSynth::HandleNoteOff(unsigned char inNote, unsigned char inVelocity)
{
	if (inNote < MaxNumVoices())
	{
		// Use inNote as the key into the mVoices array
		mVoices[inNote].SetMIDINote(0, 0);
	}
}

void CSimpleSynth::HandleAllNotesOff()
{
	for (unsigned char note = 0; note < MaxNumVoices(); ++note)
	{
		HandleNoteOff(note, 0);
	}
}

/* static */
const IToneGeneratorDelegate* CSimpleSynth::GetToneGenerator(EWaveType inWaveType)
{
	static const CSawToneGeneratorDelegate sSawToneGenerator;
	static const CTriangleToneGeneratorDelegate sTriangeToneGenerator;
	static const CSquareToneGeneratorDelegate sSquareToneGenerator;
	
	switch (inWaveType)
	{
		case eWaveType_Saw: return &sSawToneGenerator;
		case eWaveType_Tri: return &sTriangeToneGenerator;
		case eWaveType_Square: return &sSquareToneGenerator;
		default: return NULL;
	}
}

