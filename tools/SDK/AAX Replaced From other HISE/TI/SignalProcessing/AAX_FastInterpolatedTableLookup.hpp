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
/*================================================================================================*/

#ifndef AAX_FASTINTERPOLATEDTABLELOOKUP_HPP
#define AAX_FASTINTERPOLATEDTABLELOOKUP_HPP

#include "AAX_Quantize.h"

//This version requires that the lookup table is padded with one extra location so we 
//can avoid one of the checks to see if ours pointers are out of bounds.
template<class TFLOAT, class DFLOAT>
inline DFLOAT AAX_FastInterpolatedTableLookup<TFLOAT,DFLOAT>::DoTableLookupExtraFast(const TFLOAT* iTable, DFLOAT iValue) const
{
	const TFLOAT aScaledValue=(iValue - mMin)*mTableSizeM1DivMaxMinusMin;

	//Clamp between 0.0 and table size, so we don't go out of the table bounds.  One thing that's not obvious is this clamp was written 
	//so that it will return 0.0 if a NaN is given as the table input.  This keeps us within bounds even if we're feed garbage.;
	const TFLOAT aScaledValueLimited = aScaledValue > mTableSizeM1 ? mTableSizeM1 : (aScaledValue > 0.0f ? aScaledValue : 0.0f);

	int aTableIndex=AAX::FastTrunc2Int32(aScaledValueLimited);

	TFLOAT aFracIndex=aScaledValueLimited - TFLOAT(aTableIndex);
	TFLOAT aFracIndexM1=1.0f-aFracIndex;

	return (DFLOAT)(iTable[aTableIndex]*aFracIndexM1 + iTable[aTableIndex+1]*aFracIndex);
}

//This version requires that the lookup table is padded with one extra location so we
//can avoid one of the checks to see if ours pointers are out of bounds.
template<class TFLOAT, class DFLOAT>
inline void AAX_FastInterpolatedTableLookup<TFLOAT,DFLOAT>::DoTableLookupExtraFastMulti(const TFLOAT* iTable, DFLOAT iValue, DFLOAT* oValues) const
{
	TFLOAT aScaledValue=(iValue - mMin)*mTableSizeM1DivMaxMinusMin;
    
	//Clamp between 0.0 and table size, so we don't go out of the table bounds.  One thing that's not obvious is this clamp was written
	//so that it will return 0.0 if a NaN is given as the table input.  This keeps us within bounds even if we're feed garbage.
	const TFLOAT aScaledValueLimited = aScaledValue > mTableSizeM1 ? mTableSizeM1 : (aScaledValue > 0.0f ? aScaledValue : 0.0f);
    
	int aTableIndex=AAX::FastTrunc2Int32(aScaledValueLimited);
    
	TFLOAT aFracIndex=aScaledValueLimited - TFLOAT(aTableIndex);
	TFLOAT aFracIndexM1=1.0f-aFracIndex;
    
	aTableIndex=aTableIndex*mNumTables;
	int aTableIndexPlus1=aTableIndex+mNumTables;
    
	for(int i=0; i<mNumTables; i++)
	{
		oValues[i]=(DFLOAT)(iTable[aTableIndex++]*aFracIndexM1 + iTable[aTableIndexPlus1++]*aFracIndex);
	}
}

//Block version of table lookup
template<class TFLOAT, class DFLOAT>
inline void AAX_FastInterpolatedTableLookup<TFLOAT,DFLOAT>::DoTableLookupExtraFast(const TFLOAT* const iTable, const TFLOAT* const inpBuf, DFLOAT* const outBuf, int blockSize)
{
#if defined( _TMS320C6700 )
	const int r = 16;
	#pragma MUST_ITERATE(r, , r);
#endif
	for (int i = 0; i < blockSize; i++)
	{
		outBuf[i] = DoTableLookupExtraFast(iTable, inpBuf[i]);
	}
	return;
}

#endif // AAX_FASTINTERPOLATEDTABLELOOKUP_HPP
