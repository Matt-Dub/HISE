/*================================================================================================*/
/*
 *	Copyright 2015, 2023-2024 Avid Technology, Inc.
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
 *  \file AAX_MIDILogging.h
 *
 *	\brief	Utilities for logging MIDI data
 */
/*================================================================================================*/

/// @cond ignore
#ifndef AAX_MIDILOGGING_H
#define AAX_MIDILOGGING_H
/// @endcond

// AAX Includes
#include "AAX.h"

namespace AAX
{
	/** @name MIDI logging utilities
	 */
	//@{
	/** Print a MIDI stream as a C-string
		
		@details
		Sets an empty string in release builds
		
		@ingroup OtherExtensions
	*/
	void AsStringMIDIStream_Debug(const AAX_CMidiStream& inStream, char* outBuffer, int32_t inBufferSize);
	//@} MIDI logging utilities
}

/// @cond ignore
#endif // AAX_MIDILOGGING_H
/// @endcond
