/*================================================================================================*/
/*
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

#include "AAX_CSessionDocumentClient.h"
#include "AAX_VController.h"
#include "AAX_VSessionDocument.h"
#include "AAX_IEffectParameters.h"
#include "AAX_UIDs.h"
#include "acfunknown.h"
#include "acfextras.h"

AAX_CSessionDocumentClient::AAX_CSessionDocumentClient() :
	mController{},
	mEffectParameters{nullptr},
	mSessionDocument{}
{
}

AAX_CSessionDocumentClient::~AAX_CSessionDocumentClient()
{
	this->ClearInternalState(); // Guarantee
}

AAX_Result AAX_CSessionDocumentClient::Initialize(IACFUnknown * iUnknown)
{
	mController = std::make_unique<AAX_VController>(iUnknown);
	
	if (iUnknown) {
		iUnknown->QueryInterface(IID_IAAXEffectParametersV1, (void **)&mEffectParameters);
	}

	return AAX_SUCCESS;
}

AAX_Result AAX_CSessionDocumentClient::Uninitialize(void)
{
	this->ClearInternalState();
	return AAX_SUCCESS;
}

AAX_Result AAX_CSessionDocumentClient::SetSessionDocument(IACFUnknown * inSessionDocument)
{
	this->SessionDocumentWillChange();

	if (mSessionDocument) {
		mSessionDocument->Clear();
	}

	if (!inSessionDocument) {
		mSessionDocument.reset();
	}
	else {
		mSessionDocument.reset(new AAX_VSessionDocument(inSessionDocument));
	}

	this->SessionDocumentChanged();

	return AAX_SUCCESS;
}

AAX_IController* AAX_CSessionDocumentClient::GetController (void)
{
    return mController.get();
}
const AAX_IController* AAX_CSessionDocumentClient::GetController (void) const
{
    return mController.get();
}

AAX_IEffectParameters* AAX_CSessionDocumentClient::GetEffectParameters (void)
{
    return mEffectParameters;
}
const AAX_IEffectParameters* AAX_CSessionDocumentClient::GetEffectParameters (void) const
{
    return mEffectParameters;
}

std::shared_ptr<AAX_ISessionDocument> AAX_CSessionDocumentClient::GetSessionDocument(void)
{
    return mSessionDocument;
}
std::shared_ptr<const AAX_ISessionDocument> AAX_CSessionDocumentClient::GetSessionDocument (void) const
{
    return mSessionDocument;
}

void AAX_CSessionDocumentClient::ClearInternalState()
{
	if (nullptr != this->GetSessionDocument()) {
		this->SetSessionDocument(nullptr);
	}
	
	if (mEffectParameters) {
		mEffectParameters->Release();
		mEffectParameters = nullptr;
	}
	
	mController.reset();
}

