/*================================================================================================*/
/*
 *
 *    Copyright 2023-2024 Avid Technology, Inc.
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

/**
 *    \file AAX_CTask.h
 *
 *    \brief A default implementation of the \ref AAX_IACFTask interface.
 *
 */
/*================================================================================================*/

#pragma once

#ifndef AAX_CTask_H
#define AAX_CTask_H

#include "AAX_IACFTask.h"
#include "CACFUnknown.h"

class AAX_CTask : public AAX_IACFTask, CACFUnknown {
public:
    ACF_DECLARE_STANDARD_UNKNOWN()
    ACFMETHOD(InternalQueryInterface)(const acfIID& riid, void** ppvObjOut) AAX_OVERRIDE;
    // CACFUnknown does not support operator=()
    AAX_DELETE(AAX_CTask& operator=(const AAX_CTask&));

    explicit AAX_CTask(AAX_CTypeID iType);
    AAX_DEFAULT_DTOR_OVERRIDE(AAX_CTask);

    AAX_Result                GetType(AAX_CTypeID* oType) const AAX_OVERRIDE;
    AAX_IACFDataBuffer const* GetArgumentOfType(AAX_CTypeID iType) const AAX_OVERRIDE;
    AAX_Result
    SetProgress(float iProgress) AAX_OVERRIDE;
    float      GetProgress() const AAX_OVERRIDE;
    AAX_Result AddResult(AAX_IACFDataBuffer const* iResult)
        AAX_OVERRIDE; // NOTE: This needs to change to non-const so that intrusive reference counting works, or
                      // implementations always need to copy all of the data out to their own objects rather than
                      // retaining this object, which also works OK.
    AAX_Result SetDone(AAX_TaskCompletionStatus iStatus) AAX_OVERRIDE;

public:
    AAX_TaskCompletionStatus Status() const { return mStatus; }

private:
    AAX_CTypeID              mType{ 0 };			
    float                    mProgress { 0.f };
    AAX_TaskCompletionStatus mStatus { AAX_TaskCompletionStatus::None };
};


#endif
