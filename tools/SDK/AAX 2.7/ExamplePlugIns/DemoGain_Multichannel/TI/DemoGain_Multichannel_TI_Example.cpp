/*================================================================================================*/
/*
 *	Copyright 2014-2017, 2023-2024 Avid Technology, Inc.
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
// Host Alg wrapper shim headers
#include "DemoGain_Alg.h"
#include "../TI/CCSv5/elf_linkage_aax_ccsv5.h"

extern "C"
TI_EXPORT
void AlgEntry_1(	SDemoGain_Alg_Context * const		inInstancesBegin [],
				const void *						inInstancesEnd)
{
	DemoGain_AlgorithmProcessFunction<1> (
		inInstancesBegin,
		inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_2(	SDemoGain_Alg_Context * const		inInstancesBegin [],
				const void *						inInstancesEnd)
{
	DemoGain_AlgorithmProcessFunction<2> (
		inInstancesBegin,
		inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_3(	SDemoGain_Alg_Context * const		inInstancesBegin [],
				const void *						inInstancesEnd)
{
	DemoGain_AlgorithmProcessFunction<3> (
		inInstancesBegin,
		inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_4(	SDemoGain_Alg_Context * const		inInstancesBegin [],
				const void *						inInstancesEnd)
{
	DemoGain_AlgorithmProcessFunction<4> (
		inInstancesBegin,
		inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_5(	SDemoGain_Alg_Context * const		inInstancesBegin [],
				const void *						inInstancesEnd)
{
	DemoGain_AlgorithmProcessFunction<5> (
		inInstancesBegin,
		inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_6(	SDemoGain_Alg_Context * const		inInstancesBegin [],
				const void *						inInstancesEnd)
{
	DemoGain_AlgorithmProcessFunction<6> (
		inInstancesBegin,
		inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_7(	SDemoGain_Alg_Context * const		inInstancesBegin [],
				const void *						inInstancesEnd)
{
	DemoGain_AlgorithmProcessFunction<7> (
		inInstancesBegin,
		inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_8(	SDemoGain_Alg_Context * const		inInstancesBegin [],
				const void *						inInstancesEnd)
{
	DemoGain_AlgorithmProcessFunction<8> (
		inInstancesBegin,
		inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_9(	SDemoGain_Alg_Context * const		inInstancesBegin [],
				const void *						inInstancesEnd)
{
	DemoGain_AlgorithmProcessFunction<9> (
		inInstancesBegin,
		inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_10(	SDemoGain_Alg_Context * const		inInstancesBegin [],
				const void *						inInstancesEnd)
{
	DemoGain_AlgorithmProcessFunction<10> (
		inInstancesBegin,
		inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_16(   SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<16> (
        inInstancesBegin,
        inInstancesEnd);
}
