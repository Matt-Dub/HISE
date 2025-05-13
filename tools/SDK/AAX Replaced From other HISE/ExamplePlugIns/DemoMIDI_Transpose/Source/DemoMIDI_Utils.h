/*================================================================================================*/
/*
 *	Copyright 2024 Avid Technology, Inc.
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
 *  \file   DemoMIDI_Utils.h
 *
 *  \brief  Miscellaneous utilities used by DemoMIDI_Transpose
 *
 *  \author Jakub Jankowski
 */
/*================================================================================================*/
#pragma once
#ifndef DEMOMIDI_UTILS_H
#define DEMOMIDI_UTILS_H

// DemoMIDI includes
#include "DemoMIDI_Defs.h"

namespace NMidiUtils
{
//==============================================================================
// FUNCTION: ClearNotesArray - helper function that clears the note data
//==============================================================================
static void ClearNotesArray( NoteDataSegment (&noteDataArray)[cNumNoteSegments] )
{
	for ( int i = 0; i < cNumNoteSegments; ++i )
	{
		noteDataArray[i] = 0x00000000;
	}
}
} // namespace NMidiUtils

#endif // DEMOMIDI_UTILS_H
