/*================================================================================================*/
/*
 *	Copyright 2011-2015, 2023-2024 Avid Technology, Inc.
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
/*================================================================================================*/


// Note: The way that this plug-in adjusts its algorithmic latency based on
// buffer size is fundamentally broken given the requirement for AAX Native
// plug-ins to support variable buffer sizes at run-time.  However, we have
// left DemoGain_DirectData.cpp and .h in place as an example of how to use
// the Direct Data interface until a better example is available.
// -rmajors 3/12


#include "DemoGain_DirectData.h"

#include "DemoGain_Alg.h"

#include "AAX_IPrivateDataAccess.h"
#include "AAX_IController.h"


// *******************************************************************************
// ROUTINE:	Create
// *******************************************************************************
AAX_CEffectDirectData *AAX_CALLBACK DemoGain_DirectData::Create()
{
	return new DemoGain_DirectData();
}

// *******************************************************************************
// METHOD:	Constructor
// *******************************************************************************
DemoGain_DirectData::DemoGain_DirectData () :
	AAX_CEffectDirectData(),
	mCachedDelay(-1)
{
}

// *******************************************************************************
// METHOD:	TimerWakeup_PrivateDataAccess
// *******************************************************************************
AAX_Result DemoGain_DirectData::TimerWakeup_PrivateDataAccess(AAX_IPrivateDataAccess* iPrivateDataAccess)
{
	AAX_Result result = AAX_SUCCESS;
	
	AAX_IController* controller = Controller();
	DelaySamp curdelay = 0;
	result = controller->GetSignalLatency(&curdelay);
	if (result != AAX_SUCCESS) return result;
	if (curdelay != mCachedDelay)
	{
		result = iPrivateDataAccess->WritePortDirect (eAlgPortID_DelaySamples,
													  offsetof (SDemoGain_Delay, mCurDelay),
													  sizeof (DelaySamp),
													  &curdelay);
		if (result != AAX_SUCCESS) return result;
		mCachedDelay = curdelay;
	}
	
	int32_t reqdelay;
	result = iPrivateDataAccess->ReadPortDirect (eAlgPortID_DelaySamples,
												 offsetof (SDemoGain_Delay, mReqDelay),
												 sizeof (DelaySamp),
												 &reqdelay);
	if (result != AAX_SUCCESS) return result;
	
	result = controller->SetSignalLatency (reqdelay);
	if (result != AAX_SUCCESS) return result;
	
	return result;
}
