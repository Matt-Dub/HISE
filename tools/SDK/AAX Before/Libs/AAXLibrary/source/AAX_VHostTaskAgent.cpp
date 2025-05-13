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

#include "AAX_VHostTaskAgent.h"
#include "AAX_Assert.h"
#include "AAX_IACFTaskAgent.h"
#include "AAX_UIDs.h"

AAX_VHostTaskAgent::AAX_VHostTaskAgent(IACFUnknown* iUnknown)
{
    if (iUnknown) {
        AAX_Result res = iUnknown->QueryInterface(IID_IAAXTaskAgentV1, (void**) &mTaskAgentV1);
        AAX_ASSERT(res == AAX_SUCCESS);
    }
}

AAX_VHostTaskAgent::~AAX_VHostTaskAgent()
{
    this->Teardown();
}

AAX_Result AAX_VHostTaskAgent::Initialize(IACFUnknown* iController)
{
    if (mTaskAgentV1) {
        return mTaskAgentV1->Initialize(iController);
    }
    return AAX_ERROR_NULL_OBJECT;
}

AAX_Result AAX_VHostTaskAgent::Uninitialize()
{
    if (mTaskAgentV1) {
        return mTaskAgentV1->Uninitialize();
    }
    return AAX_ERROR_NULL_OBJECT;
}

AAX_Result AAX_VHostTaskAgent::AddTask(IACFUnknown* iTask)
{
    if (mTaskAgentV1) {
        return mTaskAgentV1->AddTask(iTask);
    }
    return AAX_ERROR_NULL_OBJECT;
}

AAX_Result AAX_VHostTaskAgent::CancelAllTasks()
{
    if (mTaskAgentV1) {
        return mTaskAgentV1->CancelAllTasks();
    }
    return AAX_ERROR_NULL_OBJECT;
}

void AAX_VHostTaskAgent::Teardown()
{
    mTaskAgentV1 = nullptr;
}
