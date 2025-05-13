/*================================================================================================*/
/*
 *	Copyright 2013-2015, 2019, 2023-2024 Avid Technology, Inc.
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
 *	\file  AAX_FastInterpolatedTableLookup.h
 *
 *	\brief A set of functions that provide lookup table functionality. Not necessarily
 *	optimized for TI, but used internally.
 *
 */ 
/*================================================================================================*/
#pragma once

#ifndef AAX_FASTINTERPOLATEDTABLELOOKUP_H
#define AAX_FASTINTERPOLATEDTABLELOOKUP_H

#include "AAX_Quantize.h"

//==============================================================================
//
//  NOTE:
//  Construtors and destructors are not call because state and coefficientrs blocks 
//  are not allocated as classes
//

#include AAX_ALIGN_FILE_BEGIN
#include AAX_ALIGN_FILE_ALG
#include AAX_ALIGN_FILE_END

template<class TFLOAT, class DFLOAT>
class AAX_FastInterpolatedTableLookup
{
public:
	
	/*!
	 *  \brief Set the table lookup parameters
	 *  
	 *  
	 *  \param[in] iTableSize
	 *		Size of the lookup table
	 *  \param[in] iMin
	 *		Minimum input value
	 *  \param[in] iMax
	 *		Maximum input value
	 *  \param[in] iNumTables
	 *		Number of tables to index
	 *		\note For future use...
	 */	
	void SetParameters(int iTableSize, TFLOAT iMin=0.0, TFLOAT iMax=1.0, int iNumTables=1)
	{
		mTableSizeM1=(TFLOAT)(iTableSize-1);
		mTableSize=(TFLOAT)iTableSize;
		mIntTableSizeM1=iTableSize-1;
		mMin=iMin;
		mMax=iMax;
		mMaxMinusMin=iMax-iMin;
		mTableSizeM1DivMaxMinusMin=TFLOAT(iTableSize-1)/(iMax-iMin); //Two divides??
		mTableSizeDivMaxMinusMin=TFLOAT(iTableSize)/(iMax-iMin);
		mNumTables=iNumTables;
	}
	
	/*!
	 *  \brief Perform an extra fast table lookup :)
	 *  
	 *
	 *  \param[in] iTable
	 *		Lookup table
	 *  \param[in] iValue
	 *		Table value
	 *
	 *  \note This version requires that the lookup table is padded with one
	 *	extra location so we can avoid one of the checks to see if our pointers
	 *	are out of bounds.
	 */	
	DFLOAT  DoTableLookupExtraFast(const TFLOAT* const iTable, DFLOAT iValue) const;
	void    DoTableLookupExtraFastMulti(const TFLOAT* iTable, DFLOAT iValue, DFLOAT* oValues) const;

	void    DoTableLookupExtraFast(const TFLOAT* const iTable, const TFLOAT* const inpBuf, DFLOAT* const outBuf, int blockSize);

	TFLOAT GetMin()         { return mMin; };
	TFLOAT GetMaxMinusMin() { return mMaxMinusMin; };

private:

	TFLOAT  mTableSizeM1;
	int     mIntTableSizeM1;
	TFLOAT  mTableSizeM1DivMaxMinusMin;
	TFLOAT  mMin;
	TFLOAT  mMax;
	TFLOAT  mMaxMinusMin;
	TFLOAT  mTableSize;
	TFLOAT  mTableSizeDivMaxMinusMin;
	int     mNumTables;				//This is used for multi-element lookups
};

#include AAX_ALIGN_FILE_BEGIN
#include AAX_ALIGN_FILE_RESET
#include AAX_ALIGN_FILE_END

// Template implementation
#include "AAX_FastInterpolatedTableLookup.hpp"

#endif // AAX_FASTINTERPOLATEDTABLELOOKUP_H
