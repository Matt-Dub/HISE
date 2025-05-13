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
// Input stem formats: Ambisonics 7th order
//==============================================================================
extern "C"
TI_EXPORT
void AlgEntry_64_1(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<64, 1> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_64_2(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<64, 2> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_64_3(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<64, 3> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_64_4(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<64, 4> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_64_5(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<64, 5> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_64_6(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<64, 6> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_64_7(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<64, 7> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_64_8(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<64, 8> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_64_9(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<64, 9> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_64_10(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<64, 10> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_64_11(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<64, 11> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_64_12(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<64, 12> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_64_13(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<64, 13> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_64_14(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<64, 14> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_64_15(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<64, 15> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_64_16(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<64, 16> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_64_25(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<64, 25> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_64_36(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<64, 36> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_64_49(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<64, 49> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_64_64(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<64, 64> (
        inInstancesBegin,
        inInstancesEnd);
}
