/*================================================================================================*/
/*
 *	Copyright 2014-2015, 2018-2019, 2023-2024 Avid Technology, Inc.
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
 *	\file   CSimpleTone.h
 *
 *  \author Rob Majors
 */ 
/*================================================================================================*/

#ifndef __DemoMIDI_Synth__CSimpleTone__
#define __DemoMIDI_Synth__CSimpleTone__

// C99 Includes
#include <stdint.h>


class ISimpleTone;
class IToneGeneratorDelegate;


// *******************************************************************************
// IToneGeneratorDelegate
// Pure virtual base class
// *******************************************************************************
class IToneGeneratorDelegate
{
public:
	virtual ~IToneGeneratorDelegate() {}
	virtual float Sample(const ISimpleTone& inDelegator) const = 0;
};


// *******************************************************************************
// ISimpleTone
// Pure virtual base class
// *******************************************************************************
class ISimpleTone
{
public:
	virtual ~ISimpleTone() {}
	
	virtual bool IsEnabled() const = 0;
	virtual float Amplitude() const = 0;
	virtual float Hz() const = 0;
	virtual float Tuning() const = 0;
	virtual float CurPos() const = 0; // Range is [0.0, 2.0]
	virtual void SetMIDINote(unsigned char inMIDINoteVal, unsigned char inMIDIVelocity) = 0; // Use velocity 0 to disable
	virtual void SetFrequency(float inHz) = 0;
	virtual void SetAmplitude(float inAmplitude) = 0; // Range is in [0.0, 1.0]
	virtual void SetTuning(float inAHz) = 0;
	virtual float ProcessOneSample(const IToneGeneratorDelegate& inDelegate) = 0;
};


// *******************************************************************************
// CSimpleTone
// *******************************************************************************
class CSimpleTone : public ISimpleTone
{
public:
	~CSimpleTone() override = default;
	
	CSimpleTone();
	CSimpleTone(int32_t inSampleRateHz, float inAHz);
	CSimpleTone(unsigned char inMIDINoteVal, unsigned char inMIDIVelocity, int32_t inSampleRateHz, float inAHz);
	
	bool IsEnabled() const override;
	float Amplitude() const override { return mAmplitude; }
	float Hz() const override { return mHz; }
	float Tuning() const override { return mAHz; }
	float CurPos() const override { return mCurPos; }
	void SetMIDINote(unsigned char inMIDINoteVal, unsigned char inMIDIVelocity) override;
	void SetFrequency(float inHz) override;
	void SetAmplitude(float inAmplitude) override;
	void SetTuning(float inAHz) override;
	float ProcessOneSample(const IToneGeneratorDelegate& inDelegate) override;
	
private:
	int32_t mSampleRateHz;
	unsigned char mMIDINoteVal;
	float mCurPos;
	float mAHz;
	float mHz;
	float mAmplitude;
};


// *******************************************************************************
// CSawToneGeneratorDelegate
// *******************************************************************************

class CSawToneGeneratorDelegate : public IToneGeneratorDelegate
{
public:
	~CSawToneGeneratorDelegate() override = default;
	CSawToneGeneratorDelegate() {}
	
	float Sample(const ISimpleTone& inDelegator) const override;
};


// *******************************************************************************
// CTriangleToneGeneratorDelegate
// *******************************************************************************

class CTriangleToneGeneratorDelegate : public IToneGeneratorDelegate
{
public:
	~CTriangleToneGeneratorDelegate() override = default;
	CTriangleToneGeneratorDelegate() {}
	
	float Sample(const ISimpleTone& inDelegator) const override;
};


// *******************************************************************************
// CSquareToneGeneratorDelegate
// *******************************************************************************

class CSquareToneGeneratorDelegate : public IToneGeneratorDelegate
{
public:
	~CSquareToneGeneratorDelegate() override = default;
	CSquareToneGeneratorDelegate() {}
	
	float Sample(const ISimpleTone& inDelegator) const override;
};


#endif /* defined(__DemoMIDI_Synth__CSimpleTone__) */
