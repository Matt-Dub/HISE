/*================================================================================================*/
/*
 *
 *	Copyright 2023-2024 Avid Technology, Inc.
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
 *
 */
/*================================================================================================*/

#include "AAX_CTaskAgent.h"

#include "AAX_IEffectParameters.h"
#include "AAX_VController.h"
#include "AAX_VTask.h"
#include "AAX_UIDs.h"

AAX_CTaskAgent::~AAX_CTaskAgent()
{
	this->ReleaseObjects();
}

AAX_Result AAX_CTaskAgent::Initialize ( IACFUnknown * iController )
{
	if (!iController) {
		return AAX_ERROR_NULL_ARGUMENT;
	}

	mController = new AAX_VController(iController);
	if (!mController) {
		return AAX_ERROR_NOT_INITIALIZED;
	}
		
	iController->QueryInterface(IID_IAAXEffectParametersV1, (void **)&mEffectParameters);
	if (!mEffectParameters) {
		return AAX_ERROR_NOT_INITIALIZED;
	}
	
	return AAX_SUCCESS;
}

AAX_Result AAX_CTaskAgent::Uninitialize (void)
{
	this->ReleaseObjects();
	return AAX_SUCCESS;
}

AAX_Result AAX_CTaskAgent::AddTask(IACFUnknown * iTask)
{
	// TODO: Remove the AddTask helper method
	std::unique_ptr<AAX_ITask> task = std::make_unique<AAX_VTask>(iTask);
	AAX_Result err = this->AddTask(std::move(task));
	if (AAX_ERROR_UNIMPLEMENTED == err) {
		std::unique_ptr<AAX_ITask> task2 = std::make_unique<AAX_VTask>(iTask);
		err = this->ReceiveTask(std::move(task2));
	}
	return err;
}

AAX_Result AAX_CTaskAgent::CancelAllTasks()
{
	return AAX_SUCCESS;
}

AAX_Result AAX_CTaskAgent::AddTask(std::unique_ptr<AAX_ITask> iTask)
{
	// Deprecated
	return AAX_ERROR_UNIMPLEMENTED;
}

AAX_Result AAX_CTaskAgent::ReceiveTask(std::unique_ptr<AAX_ITask> iTask)
{
	return AAX_SUCCESS;
}

void AAX_CTaskAgent::ReleaseObjects()
{
	if (mEffectParameters)
	{
		mEffectParameters->Release();
		mEffectParameters = nullptr;
	}
	
	if ( mController )
	{
		delete ( mController );
		mController = nullptr;
	}
}


