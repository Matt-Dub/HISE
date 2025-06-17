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
 *	\file  AAX_Alignment.h
 *
 *	\brief Alignment malloc and free methods for optimization
 *
 */ 
/*================================================================================================*/

#ifndef AAX_ALIGNMENT_H
#define AAX_ALIGNMENT_H

#include <stddef.h>

namespace AAX
{

	inline void alignFree(void *p)
	{  	
		char** aTempPtr=reinterpret_cast<char**>(p);
		aTempPtr--;							//backup 4 bytes past the beginning of the buffer
		char* aRealPtr = aTempPtr[0];		//Get the real address

		if(aRealPtr)
			::delete[] aRealPtr;
	}

	template <class T> 
	T* alignMalloc(int iArraySize, int iAlignment)
	{
		// We can seriously mess ourselves up if alignment is not a power of 2
		if ((iAlignment != 2) && (iAlignment != 4) && (iAlignment != 8) && (iAlignment != 16) && (iAlignment != 32)) {
			return 0;
		}
		// We can't allocate a negative-size array
		if (iArraySize <= 0) {
			return 0;
		}

		const unsigned int cSizeOfPointer = sizeof(char*);
		// Over-allocate memory by the maximum offset we could be from our requested alignment
		char* aRealPtr = ::new char[iArraySize*sizeof(T) + iAlignment + cSizeOfPointer];
		if (!aRealPtr) {
			return 0;
		}
		char* p=aRealPtr;
		p+=cSizeOfPointer;	//Skip four bytes (we store the real base address here)
		size_t mod = size_t(p) & (iAlignment-1);
		if (mod)
			p += (iAlignment - mod);
		*reinterpret_cast<char**>(p-cSizeOfPointer)=aRealPtr;	//Save the real address.  We'll need it for delete.
		return (T*) p;
	}
} // namespace AAX

#endif //AAX_ALIGNMENT_H
