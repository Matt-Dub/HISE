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
 * \file  AAX_IHostTaskAgent.h
 *
 * \brief Version-managed concrete HostTaskAgent class
 */
/*================================================================================================*/

#pragma once

#ifndef AAX_VHostTaskAgent_H
#define AAX_VHostTaskAgent_H

#include "AAX_IHostTaskAgent.h"
#include "ACFPtr.h"

class AAX_IACFTaskAgent;

class AAX_VHostTaskAgent : public AAX_IHostTaskAgent {
public:
    explicit AAX_VHostTaskAgent(IACFUnknown* iUnknown);
    ~AAX_VHostTaskAgent() override;

    AAX_Result Initialize(IACFUnknown* iController) override;
    AAX_Result Uninitialize() override;
    AAX_Result AddTask(IACFUnknown* iTask) override;
    AAX_Result CancelAllTasks() override;

private:
    void Teardown();

    ACFPtr<AAX_IACFTaskAgent> mTaskAgentV1;
};

#endif
