/*================================================================================================*/
/*
 *    Copyright 2023-2024, 2023-2024 Avid Technology, Inc.
 *    All rights reserved.
 *
 *    This file is part of the Avid AAX SDK.
 *
 *    The AAX SDK is subject to commercial or open-source licensing.
 *
 *    By using the AAX SDK, you agree to the terms of both the Avid AAX SDK License
 *    Agreement and Avid Privacy Policy.
 *
 *    AAX SDK License: https://developer.avid.com/aax
 *    Privacy Policy: https://www.avid.com/legal/privacy-policy-statement
 *
 *    Or: You may also use this code under the terms of the GPL v3 (see
 *    www.gnu.org/licenses).
 *
 *    THE AAX SDK IS PROVIDED "AS IS" WITHOUT ANY WARRANTY, AND ALL WARRANTIES, WHETHER
 *    EXPRESSED OR IMPLIED, INCLUDING MERCHANTABILITY AND FITNESS FOR PURPOSE, ARE
 *    DISCLAIMED.
 *
 */
/*================================================================================================*/

#include "AAX_CTask.h"
#include "AAX_UIDs.h"
#include "AAX_VDataBufferWrapper.h"
#include "acfextras.h"

ACFMETHODIMP AAX_CTask::InternalQueryInterface(const acfIID& riid, void** ppvObjOut)
{
    if (riid == IID_IAAXTaskV1) {
        *ppvObjOut = static_cast<IACFUnknown*>(this);
        (static_cast<IACFUnknown*>(*ppvObjOut))->AddRef();
        return ACF_OK;
    }
    return this->CACFUnknown::InternalQueryInterface(riid, ppvObjOut);
}

AAX_CTask::AAX_CTask(AAX_CTypeID iType)
    : mType { iType }
{
}

AAX_Result AAX_CTask::GetType(AAX_CTypeID* oType) const
{
    if (oType) {
        *oType = mType;
    }
    return AAX_SUCCESS;
}

AAX_IACFDataBuffer const* AAX_CTask::GetArgumentOfType(AAX_CTypeID) const
{
    return nullptr;
}

AAX_Result AAX_CTask::SetProgress(float iProgress)
{
    mProgress = iProgress;
    return AAX_SUCCESS;
}

float AAX_CTask::GetProgress() const
{
    return mProgress;
}

AAX_Result AAX_CTask::AddResult(AAX_IACFDataBuffer const*)
{
    // No generic implementation is provided here; the subclass
    // should determine what kinds of results it expects and
    // capture the data into an appropriate container.
    //
    // Returning success from the base class since the default
    // behavior is to simply discard the result.
    return AAX_SUCCESS;
}

AAX_Result AAX_CTask::SetDone(AAX_TaskCompletionStatus iStatus)
{
    mStatus = iStatus;
    return AAX_SUCCESS;
}
