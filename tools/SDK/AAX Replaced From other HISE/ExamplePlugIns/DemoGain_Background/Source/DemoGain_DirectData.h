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

/**  
 *	\file   DemoGain_DirectData.h
 */ 
/*================================================================================================*/
#pragma once
#ifndef _DEMOGAIN_DIRECTDATA_H_
#define _DEMOGAIN_DIRECTDATA_H_


#include "AAX_CEffectDirectData.h"

#include "DemoGain_Alg.h"


class AAX_IPrivateDataAccess;


class DemoGain_DirectData : public AAX_CEffectDirectData
{
public:
	//Constructor
	DemoGain_DirectData (void);
	
	//Overrides from AAX_CEffectDirectData
	AAX_Result			TimerWakeup_PrivateDataAccess(AAX_IPrivateDataAccess* iPrivateDataAccess);
	
	static AAX_CEffectDirectData *AAX_CALLBACK Create();
	
private:
	DelaySamp mCachedDelay;
};

#endif // _DEMOGAIN_DIRECTDATA_H_
