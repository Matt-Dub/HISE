/*================================================================================================*/
/*
 *	Copyright 2022, 2023-2024 Avid Technology, Inc.
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
// Input stem formats: 7.0.4
//==============================================================================
extern "C"
TI_EXPORT
void AlgEntry_11_1(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<11, 1> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_11_2(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<11, 2> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_11_3(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<11, 3> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_11_4(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<11, 4> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_11_5(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<11, 5> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_11_6(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<11, 6> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_11_7(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<11, 7> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_11_8(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<11, 8> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_11_9(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<11, 9> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_11_10(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<11, 10> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_11_11(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<11, 11> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_11_12(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<11, 12> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_11_13(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<11, 13> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_11_14(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<11, 14> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_11_15(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<11, 15> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_11_16(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<11, 16> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_11_25(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<11, 25> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_11_36(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<11, 36> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_11_49(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<11, 49> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_11_64(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<11, 64> (
        inInstancesBegin,
        inInstancesEnd);
}
