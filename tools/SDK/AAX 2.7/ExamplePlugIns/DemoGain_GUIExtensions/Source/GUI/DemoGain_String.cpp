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
/*================================================================================================*/
#include "DemoGain_String.h"


DemoGain_String::DemoGain_String() :
	mString("")
{
}

uint32_t DemoGain_String::Length () const
{
	return uint32_t(mString.length());
}

uint32_t DemoGain_String::MaxLength () const
{
	return kMaxStringLength;
}

const char * DemoGain_String::Get ()	const
{
	return mString.c_str();
}

void DemoGain_String::Set ( const char * iString )
{
	mString = iString;
}

AAX_IString & DemoGain_String::operator=(const AAX_IString & iOther)
{	
	mString = iOther.Get();
	return *this;
}

AAX_IString & DemoGain_String::operator=(const char * iString)
{
	mString = iString;
	return *this;
}
