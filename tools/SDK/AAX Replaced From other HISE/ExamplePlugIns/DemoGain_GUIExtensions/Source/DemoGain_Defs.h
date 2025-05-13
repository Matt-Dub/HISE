/*================================================================================================*/
/*
 *	Copyright 2008-2016, 2018, 2023-2024 Avid Technology, Inc.
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
 *	\brief  Definitions shared by the DemoGain_GUIExtensions classes in one easy-to-maintain file.
 */ 
/*================================================================================================*/

#pragma once
#ifndef DEMOGAIN_DEFS_H
#define DEMOGAIN_DEFS_H

#include "AAX.h"			// for AAX_CTypeID


// Type, product, and relation IDs
const AAX_CTypeID cDemoGain_ManufactureID =			'AVID';

#if PLUGGUI == 1 // Native (Win32 or Cocoa)
const AAX_CTypeID cDemoGain_ProductID =				'DmGN';
#elif PLUGGUI == 2 // Juce
const AAX_CTypeID cDemoGain_ProductID =				'DmGJ';
#elif PLUGGUI == 3 // VSTGUI
const AAX_CTypeID cDemoGain_ProductID =				'DmGV';
#elif PLUGGUI == 4 // Cocoa GUI in separate bundle
const AAX_CTypeID cDemoGain_ProductID =				'DGsb';
#else
const AAX_CTypeID cDemoGain_ProductID =				'DmGn';
#endif // PLUGGUI

const AAX_CTypeID cDemoGain_PlugInID_Native =		'DGDR';
const AAX_CTypeID cDemoGain_PlugInID_AudioSuite =	'DGDA';
const AAX_CTypeID cDemoGain_PlugInID_TI =			'DGDT';

const AAX_CTypeID cDemoGain_MeterID [2] =			{'mtrI','mtrO'};

const AAX_CParamID DemoGain_GainID =				"Gain";

#endif // DEMOGAIN_DEFS_H
