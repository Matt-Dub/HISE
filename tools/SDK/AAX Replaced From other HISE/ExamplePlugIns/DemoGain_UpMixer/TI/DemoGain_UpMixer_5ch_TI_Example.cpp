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
// Input stem formats: 5.0
//==============================================================================
extern "C"
TI_EXPORT
void AlgEntry_5_1(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<5, 1> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_5_2(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<5, 2> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_5_3(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<5, 3> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_5_4(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<5, 4> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_5_5(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<5, 5> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_5_6(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<5, 6> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_5_7(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<5, 7> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_5_8(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<5, 8> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_5_9(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<5, 9> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_5_10(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<5, 10> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_5_11(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<5, 11> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_5_12(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<5, 12> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_5_13(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<5, 13> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_5_14(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<5, 14> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_5_15(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<5, 15> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_5_16(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<5, 16> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_5_25(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<5, 25> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_5_36(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<5, 36> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_5_49(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<5, 49> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_5_64(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<5, 64> (
        inInstancesBegin,
        inInstancesEnd);
}
