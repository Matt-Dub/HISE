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
// Input stem formats: 6.1; 7.0 SDDS; 7.0 DTS; 5.0.2
//==============================================================================
extern "C"
TI_EXPORT
void AlgEntry_7_1(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<7, 1> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_7_2(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<7, 2> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_7_3(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<7, 3> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_7_4(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<7, 4> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_7_5(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<7, 5> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_7_6(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<7, 6> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_7_7(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<7, 7> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_7_8(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<7, 8> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_7_9(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<7, 9> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_7_10(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<7, 10> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_7_11(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<7, 11> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_7_12(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<7, 12> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_7_13(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<7, 13> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_7_14(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<7, 14> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_7_15(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<7, 15> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_7_16(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<7, 16> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_7_25(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<7, 25> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_7_36(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<7, 36> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_7_49(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<7, 49> (
        inInstancesBegin,
        inInstancesEnd);
}

extern "C"
TI_EXPORT
void AlgEntry_7_64(  SDemoGain_Alg_Context * const       inInstancesBegin [],
                const void *                        inInstancesEnd)
{
    DemoGain_AlgorithmProcessFunction<7, 64> (
        inInstancesBegin,
        inInstancesEnd);
}
