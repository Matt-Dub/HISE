/*================================================================================================*/
/*
 *	Copyright 2009-2015, 2023-2024 Avid Technology, Inc.
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
 *	\file  AAX_Constants.h
 *
 *	\brief Signal processing constants
 *
 */ 
/*================================================================================================*/
#pragma once

#ifndef AAX_CONSTANTS_H
#define AAX_CONSTANTS_H


/* the following lines were re-introduced on 6/11/09 because
	the FFmt project still uses SInt32 types	*/
#ifdef _TMS320C6X
	typedef   signed int  SInt32;
#else
//	#include "DigiPublicTypes.h"
#endif
/* end 6/11/09 changes */


// Standard headers
#include <cmath>

namespace AAX
{

#if __BIG_ENDIAN__
	const int cBigEndian=1;
	const int cLittleEndian=0;
#else
	const int cBigEndian=0;
	const int cLittleEndian=1;
#endif

const double cPi			= 3.1415926535897932384626433832795;
const double cTwoPi			= 6.2831853071795862319959269370884;  //2.0*3.1415926535897932384626433832795;
const double cHalfPi		= 1.5707963267948965579989817342721;  //0.5*3.1415926535897932384626433832795;
const double cQuarterPi		= 0.78539816339744827899949086713605; //0.25*3.1415926535897932384626433832795;
const double cRootTwo		= 1.4142135623730950488016887242097;
const double cOneOverRootTwo= 0.70710678118654752440084436210485;


//Obviously these numbers are are not exact.
const double cPos3dB=1.4142135623730950488016887242097;
const double cNeg3dB=0.70710678118654752440084436210485;
const double cPos6dB=2.0;
const double cNeg6dB=0.5;

const double cNormalizeLongToAmplitudeOneHalf	= 0.00000000023283064365386962890625; //1.0/double(1LL<<32LL);
const double cNormalizeLongToAmplitudeOne		= 1.0/double(1<<31); //-0.0000000004656612873077392578125;  

const double cMilli=0.001;
const double cMicro=0.001*0.001;
const double cNano=0.001*0.001*0.001;
const double cPico=0.001*0.001*0.001*0.001;

const double cKilo=1000.0;
const double cMega=1000.0*1000.0;
const double cGiga=1000.0*1000.0*1000.0;

enum ESampleRates
{
	e44100SampleRate = 44100,
	e48000SampleRate = 48000,
	e88200SampleRate = 88200,
	e96000SampleRate = 96000,
	e176400SampleRate = 176400,
	e192000SampleRate = 192000
};

} // namespace AAX

#endif // AAX_CONSTANTS_H

