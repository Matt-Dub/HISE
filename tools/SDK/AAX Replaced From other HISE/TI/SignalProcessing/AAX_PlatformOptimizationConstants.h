/*================================================================================================*/
/*
 *	Copyright 2009-2015, 2023-2024 Avid Technology, Inc.
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
 *	\file  AAX_PlatformOptimizationConstants.h
 *
 *	\brief Constants descriptor...
 *
 */ 
/*================================================================================================*/
#pragma once

#ifndef AAX_PLATFORMOPTIMIZATIONCONSTANTS_H
#define AAX_PLATFORMOPTIMIZATIONCONSTANTS_H

// Set up our platform-specific optimization defines
#if USE_PLATFORM_OPTIMIZATION
	#if defined( WINDOWS_VERSION )
			#define USE_INTEL_IPP (1)		// Windows
			#define __SSE__ (1)				// Manually define the __SSE__ flag
	#elif defined( MAC_VERSION )
		#if defined(__ppc__)
			#define USE_ALTIVEC_VDSP (1)	// PPC
		#elif defined(__i386__) or defined(__x86_64__)
			#define USE_INTEL_IPP (1)		// MacTel
		#else
			#error "Unsupported platform for optimizations!"
		#endif // __i386__ or __ppc__
	#else
		#error "Unsupported platform for optimizations!"
	#endif // WINDOWS_VERSION
#endif // USE_PLATFORM_OPTIMIZATION

#endif // AAX_PLATFORMOPTIMIZATIONCONSTANTS_H

