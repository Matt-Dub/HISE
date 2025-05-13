/*================================================================================================*/
/*
 *	Copyright 2012-2016, 2018, 2023-2024 Avid Technology, Inc.
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
 *	\brief  Definitions shared by the DemoDist_ParamValueInfo classes in one easy-to-maintain file.
 *
 *  \author Rob Majors
 */ 
/*================================================================================================*/
#pragma once
#ifndef DEMOGAIN_DEFS_H
#define DEMOGAIN_DEFS_H

#include "AAX.h"			// for AAX_CTypeID

// Effect IDs and names
const AAX_CEffectID kEffectID_DemoGain	= "com.avid.aax.sdk.demogain.paramvalueinfo";
const AAX_CEffectID kEffectName_DemoGain[] = { "Demo Gain Param Value Info", "DmGnPVI", "DGvi", "Di", 0 };

// Type, product, and relation IDs
const AAX_CTypeID cDemoGain_ManufactureID			= 'AVID';
const AAX_CTypeID cDemoGain_ProductID				= 'DmGn';
const AAX_CTypeID cDemoGain_PlugInID_Native			= 'DGVI';

const AAX_CTypeID cDemoGain_MeterID [2]				= {'mtrI','mtrO'};

const char* const DemoGain_GainID					= "Gain";
const char* const DemoGain_FilterTypeID				= "EQ Type";
const char* const DemoGain_Q						= "Q";
const char* const DemoGain_Slope					= "Slope";

const char* const DemoGain_HighPassStatus			= "High Pass Status";
const char* const DemoGain_LowPassStatus			= "Low Pass Status";
const char* const DemoGain_HighShelfStatus			= "High Shelf Status";
const char* const DemoGain_LowShelfStatus			= "Low Shelf Status";

#endif // DEMOGAIN_DEFS_H
