/*================================================================================================*/
/*
 *
 * Copyright 2023-2024 Avid Technology, Inc.
 * All rights reserved.
 * 
 * This file is part of the Avid AAX SDK.
 * 
 * The AAX SDK is subject to commercial or open-source licensing.
 * 
 * By using the AAX SDK, you agree to the terms of both the Avid AAX SDK License
 * Agreement and Avid Privacy Policy.
 * 
 * AAX SDK License: https://developer.avid.com/aax
 * Privacy Policy: https://www.avid.com/legal/privacy-policy-statement
 * 
 * Or: You may also use this code under the terms of the GPL v3 (see
 * www.gnu.org/licenses).
 * 
 * THE AAX SDK IS PROVIDED "AS IS" WITHOUT ANY WARRANTY, AND ALL WARRANTIES, WHETHER
 * EXPRESSED OR IMPLIED, INCLUDING MERCHANTABILITY AND FITNESS FOR PURPOSE, ARE
 * DISCLAIMED.
 *
 */

/**  
 * \file  AAX_VDataBufferWrapper.cpp
 */ 
/*================================================================================================*/

#include "AAX_VDataBufferWrapper.h"

#include "AAX_IACFDataBuffer.h"
#include "AAX_UIDs.h"
#include "acfextras.h"

AAX_VDataBufferWrapper::AAX_VDataBufferWrapper(IACFUnknown * iUnknown)
{
	if (iUnknown) {
		iUnknown->QueryInterface(IID_IAAXDataBufferV1, (void **)&mDataBufferV1);
	}
}

AAX_VDataBufferWrapper::~AAX_VDataBufferWrapper() = default;

AAX_Result AAX_VDataBufferWrapper::Type(AAX_CTypeID * oType) const
{
	if (mDataBufferV1) {
		return mDataBufferV1->Type(oType);
	}
	return AAX_ERROR_NULL_OBJECT;
}

AAX_Result AAX_VDataBufferWrapper::Size(int32_t * oSize) const
{
	if (mDataBufferV1) {
		return mDataBufferV1->Size(oSize);
	}
	return AAX_ERROR_NULL_OBJECT;
}

AAX_Result AAX_VDataBufferWrapper::Data(void const ** oBuffer) const
{
	if (mDataBufferV1) {
		return mDataBufferV1->Data(oBuffer);
	}
	return AAX_ERROR_NULL_OBJECT;
}
