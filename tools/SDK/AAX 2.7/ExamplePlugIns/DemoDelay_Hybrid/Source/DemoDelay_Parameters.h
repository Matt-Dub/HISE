/*================================================================================================*/
/*
 *	Copyright 2013-2015, 2019, 2023-2024 Avid Technology, Inc.
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
 *	\file   DemoDelay_Parameters.h
 *
 *	\brief  DemoDelay_Parameters class declaration.
 *
 *  \author Dave Tremblay
 */ 
/*================================================================================================*/  
#pragma once
#ifndef DEMODELAY_PARAMETERS_H
#define DEMODELAY_PARAMETERS_H

#include "AAX_CEffectParameters.h"

#include "CSimpleDelayLine.h"


class DemoDelay_Parameters : public AAX_CEffectParameters
{
public:
	//Construction and destruction
	static AAX_CEffectParameters *AAX_CALLBACK	Create();
	/* default constructor */					DemoDelay_Parameters (void);
	virtual /* destructor */					~DemoDelay_Parameters();

	//Overrides from AAX_CEffectParameters
	virtual AAX_Result  EffectInit();
	virtual AAX_Result  RenderAudio_Hybrid(AAX_SHybridRenderInfo* ioRenderInfo);

private:
	enum EConversionDirection
	{
		eConversionDirection_MSToSamples,
		eConversionDirection_SamplesToMS
	};
	
	// Data model helper methods
	//
	// Retrieves the number of samples of delay implied by the current data model state
	AAX_Result	GetDelaySamples(int32_t& oSamples) const;
	// Converts between ms and samples
	AAX_Result	ConvertBetweenMSAndSamples(EConversionDirection iConversionDirection, float& ioMS, int32_t& ioSamples) const;
	// Returns true if the plug-in is currently bypassed
	bool		BypassEnabled() const;
	
	// Packet generation methods
	AAX_Result  GenerateCoefficientPacket(AAX_CPacket& ioPacket);
	
private:
	CSimpleDelayLine	mDelayLine;
};

#endif
