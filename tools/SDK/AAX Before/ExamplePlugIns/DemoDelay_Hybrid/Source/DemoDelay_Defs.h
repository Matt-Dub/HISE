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
 *	\file   DemoDelay_Defs.h
 *
 *	\brief  Definitions shared by the DemoDelay_Hybrid classes in one easy-to-maintain file.
 *
 *  \author Dave Tremblay
 */ 
/*================================================================================================*/
#pragma once
#ifndef DemoDelay_DEFS_H
#define DemoDelay_DEFS_H

#include "AAX.h"			// for AAX_CTypeID


// Type, product, and relation IDs
const AAX_CTypeID cDemoDelay_ManufactureID =		'AVID';
const AAX_CTypeID cDemoDelay_ProductID =			'DmDH';
const AAX_CTypeID cDemoDelay_PlugInID_Native =		'DHna';
const AAX_CTypeID cDemoDelay_PlugInID_TI =			'DHti';

const AAX_CTypeID cDemoDelay_MeterID [2] =			{'mtrI','mtrO'};

#define DemoDelay_DelayID		"Delay"

#endif // DemoDelay_DEFS_H
