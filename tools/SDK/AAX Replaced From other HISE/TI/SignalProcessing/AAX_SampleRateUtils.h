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
 *	\file  AAX_SampleRateUtils.h
 *
 *	\brief Description
 *
 */ 
/*================================================================================================*/
#pragma once

enum ESRUtils
{
	eSRUtils_48kRangeCoarse		= 48000,
	eSRUtils_96kRangeCoarse		= 96000,
	eSRUtils_192kRangeCoarse	= 192000,
	eSRUtils_48kRangeMin		= 0,
	eSRUtils_48kRangeMax		= 51000,
	eSRUtils_96kRangeMin		= eSRUtils_48kRangeMax+1,
	eSRUtils_96kRangeMax		= 102000,
	eSRUtils_192kRangeMin		= eSRUtils_96kRangeMax+1,
	eSRUtils_192kRangeMax		= 204000,
	eSRUtils_48kIndex		= 0,
	eSRUtils_96kIndex		= 1,
	eSRUtils_192kIndex		= 2
};
	
inline int CoarseSampleRate (int iRate)
{
	const int aCoarseRate =

		((iRate >= eSRUtils_48kRangeMin) && (iRate <= eSRUtils_48kRangeMax)) ?  eSRUtils_48kRangeCoarse :
		((iRate >= eSRUtils_96kRangeMin) && (iRate <= eSRUtils_96kRangeMax)) ?  eSRUtils_96kRangeCoarse :
		((iRate >= eSRUtils_192kRangeMin) && (iRate <= eSRUtils_192kRangeMax)) ? eSRUtils_192kRangeCoarse :
		0;

	if (aCoarseRate == 0)
	{
//		throw std::runtime_error ("unrecognized sample rate");
	}
	return aCoarseRate;
}

//Returns 1 for 48k, 2 for 96k, and 4 for 192k gross samples rate.
inline int CoarseSampleRateFactor (int iRate)
{
	const int kMinCoarseSampleRate=eSRUtils_48kRangeCoarse;

	int aCoarseRateFactor = CoarseSampleRate (iRate)/kMinCoarseSampleRate;

	return aCoarseRateFactor;
}

//Returns 0 for 48k, 1 for 96k, and 2 for 192k gross samples rate.
inline int CoarseSampleRateIndex (int iRate)
{
//	const long kMinGrossSampleRate=eSRUtils_48kRangeCoarse;
	int aGrossRateIndex = 0;

	switch ( CoarseSampleRate (iRate) )
	{
	default:
		case eSRUtils_48kRangeCoarse:
			aGrossRateIndex = 0;
			break;
		case eSRUtils_96kRangeCoarse:
			aGrossRateIndex = 1;
			break;
		case eSRUtils_192kRangeCoarse:
			aGrossRateIndex = 2;
			break;
//		default:
//			throw std::runtime_error ("unrecognized sample rate");
	}

	return aGrossRateIndex;
}
