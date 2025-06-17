/*================================================================================================*/
/*
 *	Copyright 2009-2015, 2019, 2023-2024 Avid Technology, Inc.
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
 *	\file   DemoGain_Parameters.h
 *
 *	\brief  DemoGain_Parameters class declaration.
 */ 
/*================================================================================================*/ 
#pragma once
#ifndef DEMOGAIN_PARAMETERS_H
#define DEMOGAIN_PARAMETERS_H

#include "DemoGain_Alg.h"
#include "AAX_CEffectParameters.h"
#include <map>
#include <string>


class DemoGain_Parameters : public AAX_CEffectParameters
{
public:
	DemoGain_Parameters (void);
	AAX_DEFAULT_DTOR_OVERRIDE (DemoGain_Parameters);
	
	// Create callback
	static AAX_CEffectParameters *AAX_CALLBACK Create();

public:
	//Overrides from AAX_CEffectParameters
	AAX_Result EffectInit() AAX_OVERRIDE;
	AAX_Result SetChunk (AAX_CTypeID chunkID, const AAX_SPlugInChunk * iChunk ) AAX_OVERRIDE;
	AAX_Result UpdateParameterNormalizedValue ( AAX_CParamID inParameterID, double inValue, AAX_EUpdateSource inSource ) AAX_OVERRIDE;
	AAX_Result UpdateParameterTouch ( AAX_CParamID inParameterID, AAX_CBoolean inTouchState ) AAX_OVERRIDE;
	
private:
	AAX_Result UpdatePacket_Gains(AAX_CPacket& ioPacket);
	AAX_CParamID GetLinkedControl ( AAX_CParamID inParameterID );
	void SetGains ( SDemoGain_CoefsGain * ioGains, bool inType, double inValue, DemoGain_ESide inSide );

private:
	std::multimap<std::string,std::string>	mLinkTouchMap;
};


#endif
