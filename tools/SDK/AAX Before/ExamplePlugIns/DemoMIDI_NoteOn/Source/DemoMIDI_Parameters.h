/*================================================================================================*/
/*
 *	Copyright 2013-2015, 2023-2024 Avid Technology, Inc.
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
	
	//Constructor
	DemoMIDI_Parameters( void );
	
	// Static method that creates and returns a new instance of the class
	static AAX_CEffectParameters *AAX_CALLBACK	Create();
	
	// Override from AAX_CEffectParameters, use to initilize parameters, packets, meters, etc.
	AAX_Result									EffectInit() AAX_OVERRIDE;
	
	// Override from AAX_CEffectParameters, use to handle MIDI packages in the Data Model
	AAX_Result									UpdateMIDINodes( AAX_CFieldIndex inFieldIndex,
																 AAX_CMidiPacket& inPacket ) AAX_OVERRIDE;
	
	// Override from AAX_CEffectParameters, use to initialise the field data
	AAX_Result								  	ResetFieldData( AAX_CFieldIndex inFieldIndex,
																void* oData,
																uint32_t inDataSize ) const AAX_OVERRIDE;
};

#endif
