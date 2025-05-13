/*================================================================================================*/
/*
 *	Copyright 2014-2017, 2022-2024 Avid Technology, Inc.
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

//==============================================================================
// Input stem formats: 7.1 SDDS; 7.1 DTS; 5.1.2
//==============================================================================
extern "C"
TI_EXPORT
void AlgEntry_8_1(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<8, 1> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_8_2(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<8, 2> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_8_3(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<8, 3> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_8_4(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<8, 4> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_8_5(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<8, 5> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_8_6(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<8, 6> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_8_7(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<8, 7> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_8_8(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<8, 8> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_8_9(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<8, 9> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_8_10(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<8, 10> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_8_11(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<8, 11> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_8_12(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<8, 12> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_8_13(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<8, 13> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_8_14(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<8, 14> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_8_15(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<8, 15> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_8_16(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<8, 16> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_8_25(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<8, 25> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_8_36(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<8, 36> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_8_49(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<8, 49> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_8_64(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<8, 64> (
        inInstancesBegin,
        inInstancesEnd);
}
