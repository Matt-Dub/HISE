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
/*================================================================================================*/

#include "AAX_VTask.h"
#include "AAX_UIDs.h"
#include "acfunknown.h"


AAX_VTask::AAX_VTask( IACFUnknown* pUnknown )
{
	if ( pUnknown )
	{
		pUnknown->QueryInterface(IID_IAAXTaskV1, (void **)&mTaskV1);
	}
}

AAX_VTask::~AAX_VTask() = default;

AAX_Result AAX_VTask::GetType(AAX_CTypeID * oType) const
{
	if (mTaskV1) {
		return mTaskV1->GetType(oType);
	}
	return AAX_ERROR_NULL_OBJECT;
}

AAX_IACFDataBuffer const * AAX_VTask::GetArgumentOfType(AAX_CTypeID iType) const
{
	if (mTaskV1) {
		return mTaskV1->GetArgumentOfType(iType);
	}
	return nullptr;
}

AAX_Result AAX_VTask::SetProgress(float iProgress)
{
	if (mTaskV1) {
		return mTaskV1->SetProgress(iProgress);
	}
	return AAX_ERROR_NULL_OBJECT;
}

float AAX_VTask::GetProgress() const
{
	if (mTaskV1) {
		return mTaskV1->GetProgress();
	}
	return AAX_ERROR_NULL_OBJECT;
}

AAX_Result AAX_VTask::AddResult(AAX_IACFDataBuffer const * iResult)
{
	if (mTaskV1) {
		return mTaskV1->AddResult(iResult);
	}
	return AAX_ERROR_NULL_OBJECT;
}

AAX_ITask * AAX_VTask::SetDone(AAX_TaskCompletionStatus iStatus)
{
	if (mTaskV1) {
		if (AAX_SUCCESS == mTaskV1->SetDone(iStatus)) {
			mTaskV1 = nullptr;
			return nullptr;
		}
	}
	return this;
}
