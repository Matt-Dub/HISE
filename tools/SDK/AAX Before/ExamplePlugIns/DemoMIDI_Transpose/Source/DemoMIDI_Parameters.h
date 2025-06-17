/*================================================================================================*/
/*
 *	Copyright 2024 Avid Technology, Inc.
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
 *	\file   DemoMIDI_Parameters.h
 *
 *	\brief  DemoMIDI_Parameters class declaration.
 *
 *  \author Jakub Jankowski
 */ 
/*================================================================================================*/ 
#pragma once
#ifndef DEMOMIDI_PARAMETERS_H
#define DEMOMIDI_PARAMETERS_H

#include "AAX_CEffectParameters.h"

//==============================================================================
class DemoMIDI_Parameters : public AAX_CEffectParameters
{
public:
	DemoMIDI_Parameters (void);
	AAX_DEFAULT_DTOR_OVERRIDE(DemoMIDI_Parameters);
	
	static AAX_CEffectParameters *AAX_CALLBACK	Create();

	// Overrides from AAX_CEffectParameters
	AAX_Result	EffectInit() AAX_OVERRIDE;
	AAX_Result	GenerateCoefficients()	AAX_OVERRIDE;
	AAX_Result	ResetFieldData( AAX_CFieldIndex inFieldIndex,
								void* oData,
								uint32_t inDataSize ) const AAX_OVERRIDE;
};

#endif // DEMOMIDI_PARAMETERS_H
