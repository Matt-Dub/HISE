/*================================================================================================*/
/*
 *	Copyright 2012-2015, 2023-2024 Avid Technology, Inc.
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
 *	\file   DemoSampler_SampleBase.h
 *
 *	\brief  Definitions shared by the DemoMIDI_Sampler classes in one easy-to-maintain file.
 */ 
/*================================================================================================*/
#pragma once
#ifndef _DEMOSAMPLERSAMPLEBASE
#define _DEMOSAMPLERSAMPLEBASE

#include "AAX.h"

const int32_t bass_size = 44096;
extern float bass_bank[bass_size];

const int32_t snare_size = 14992;
extern float snare_bank[snare_size];

const int32_t tom_size = 10192;
extern float tom_bank[tom_size];

#endif	//	_DEMOSAMPLERSAMPLEBASE
