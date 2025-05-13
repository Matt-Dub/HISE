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
 *	\file   DemoDist_Parameters.h
 *
 *	\brief  DemoDist_Parameters class declaration.
 */ 
/*================================================================================================*/ 

#pragma once
#ifndef DEMODIST_PARAMETERS_H
#define DEMODIST_PARAMETERS_H

#include "AAX_CEffectParameters.h"


//==============================================================================
class DemoDist_Parameters : public AAX_CEffectParameters
{
public:
	DemoDist_Parameters ();
	AAX_DEFAULT_DTOR_OVERRIDE (DemoDist_Parameters);
	
	// Create callback
	static AAX_CEffectParameters * AAX_CALLBACK Create();
	
public:
	//Overrides from AAX_CEffectParameters
	AAX_Result EffectInit() AAX_OVERRIDE;
	AAX_Result ResetFieldData (AAX_CFieldIndex inFieldIndex, void * oData, uint32_t iDataSize) const AAX_OVERRIDE;
	
private:
	AAX_Result UpdatePacket_Filter( AAX_CPacket& ioPacket );
	AAX_Result UpdatePacket_Distort( AAX_CPacket& ioPacket );
};


#endif
