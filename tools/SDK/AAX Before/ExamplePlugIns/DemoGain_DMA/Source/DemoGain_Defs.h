/*================================================================================================*/
/*
 *	Copyright 2008-2015, 2023-2024 Avid Technology, Inc.
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
 *	\brief  Definitions shared by the DemoDist_DMA classes in one easy-to-maintain file.
 */ 
/*================================================================================================*/

#pragma once
#ifndef DEMOGAIN_DEFS_H
#define DEMOGAIN_DEFS_H

#include "AAX.h"			// for AAX_CTypeID

// Effect IDs
const AAX_CEffectID kEffectID_DemoGain			= "com.avid.aax.sdk.demogain.dma";
const AAX_CEffectID kEffectID_DemoGain_DMASG	= "com.avid.aax.sdk.demogain.dma.scattergather";
const AAX_CEffectID kEffectID_DemoGain_DMABurst	= "com.avid.aax.sdk.demogain.dma.burst";

// Type, product, and relation IDs
const AAX_CTypeID cDemoGain_ManufactureID =                 'AVID';
const AAX_CTypeID cDemoGain_ProductID =                     'DGDM';
const AAX_CTypeID cDemoGain_DMASG_PlugInID_Native =         'GsgN';
const AAX_CTypeID cDemoGain_DMASG_PlugInID_AudioSuite =     'GsgA';
const AAX_CTypeID cDemoGain_DMASG_PlugInID_TI =             'GsgT';
const AAX_CTypeID cDemoGain_DMABurst_PlugInID_Native =      'GbrN';
const AAX_CTypeID cDemoGain_DMABurst_PlugInID_AudioSuite =  'GbrA';
const AAX_CTypeID cDemoGain_DMABurst_PlugInID_TI =          'GbrT';


// Meter layout
enum EDemoGain_MeterTaps
{
	eMeterTap_PreGain = 0,
	eMeterTap_PostGain,
	
	eMeterTap_Count
};

const AAX_CTypeID cDemoGain_MeterID [2] =			{'mtrI','mtrO'};


#define DemoGain_GainID		"Gain"

#endif // DEMOGAIN_DEFS_H
