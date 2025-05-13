/*================================================================================================*/
/*
 *	Copyright 2008-2015, 2018, 2023-2024 Avid Technology, Inc.
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
 *	\file   DemoGain_Defs.h
 *
 *	\brief  Definitions shared by the DemoGain_LinkedParameters classes in one easy-to-maintain file.
 */ 
/*================================================================================================*/
#pragma once
#ifndef DEMOGAIN_DEFS_H
#define DEMOGAIN_DEFS_H

#include "AAX.h"			// for AAX_CTypeID

// Effect IDs
const AAX_CEffectID kEffectID_DemoGain =			"com.avid.aax.sdk.demogain.link";

// Type, product, and relation IDs
const AAX_CTypeID cDemoGain_ManufactureID =			'AVID';
const AAX_CTypeID cDemoGain_ProductID =				'DmGL';
const AAX_CTypeID cDemoGain_PlugInID_Native =		'DGDR';
const AAX_CTypeID cDemoGain_PlugInID_AudioSuite =	'DGDA';
const AAX_CTypeID cDemoGain_PlugInID_TI =			'DGDT';

const AAX_CTypeID cDemoGain_MeterID [4] =			{'mtIL','mtIR','mtOL','mtOR'};

#define DemoGain_GainLeftID		"Gain Left"
#define DemoGain_GainRightID	"Gain Right"
#define DemoGain_LinkToggleID	"Link"
#define DemoGain_TypeToggleID	"Type"

#endif // DEMOGAIN_DEFS_H
