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
 *	\file   DemoGain_String.h
 *
 */ 
/*================================================================================================*/

#ifndef _DEMOGAIN_STRING_
#define _DEMOGAIN_STRING_

#include "AAX_IString.h"
#include <string>

class DemoGain_String : public AAX_IString
{
public: ////////////////////////////////////////////// DemoGain_String
	static const uint32_t	kMaxStringLength = static_cast<uint32_t>(-2);
	
	/** Constructs an empty string. */
	DemoGain_String();

public: ////////////////////////////////////////////// AAX_IString	
	/** Length methods */
	virtual uint32_t		Length () const;
	virtual uint32_t		MaxLength () const;
	
	/** C string methods */
	virtual const char *	Get ()	const;
	virtual void			Set ( const char * iString );		
	
	/** Assignment operators */
	virtual AAX_IString &	operator=(const AAX_IString & iOther);
	virtual AAX_IString &	operator=(const char * iString);
	
private: ///////////////////////////////////////////// DemoGain_String
	std::string mString;
};

#endif // _DEMOGAIN_STRING_
