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
 * \brief Interface to access an AAX_IACFTaskAgent object implemented by the host.
 */
/*================================================================================================*/

#pragma once

#ifndef AAX_IHostTaskAgent_H
#define AAX_IHostTaskAgent_H

#include "AAX.h"
#include "CACFUnknown.h"

/** \brief Interface to access an AAX_IACFTaskAgent object implemented by the host.
    
    \details
    
    The plugin may use this interface to add tasks to the host's agent, requesting that the host perform actions.
 
    \sa \ref AAX_IACFTaskAgent
*/

class AAX_IHostTaskAgent {
public:
    virtual ~AAX_IHostTaskAgent() = default;

    virtual AAX_Result Initialize(IACFUnknown* iController) = 0;
    virtual AAX_Result Uninitialize()                       = 0;
    virtual AAX_Result AddTask(IACFUnknown* iTask)          = 0;
    virtual AAX_Result CancelAllTasks()                     = 0;
};

#endif
