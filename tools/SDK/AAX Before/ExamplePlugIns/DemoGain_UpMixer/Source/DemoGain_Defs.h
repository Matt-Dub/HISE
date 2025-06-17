/*================================================================================================*/
/*
 *	Copyright 2016-2017, 2019, 2022-2024 Avid Technology, Inc.
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
 *	\file   DemoGain_Defs.h
 *
 *	\brief  Definitions shared by the DemoGain classes in one easy-to-maintain file.
 */ 
/*================================================================================================*/

#pragma once
#ifndef DEMOGAIN_DEFS_H
#define DEMOGAIN_DEFS_H

#include "AAX.h"			// for AAX_CTypeID


// Type, product, and relation IDs
const AAX_CTypeID cDemoGain_ManufactureID							= 'AVID';
const AAX_CTypeID cDemoGain_UpMixer_ProductID						= 'DgUP';

#define MAX_STEM_FORMAT AAX_eStemFormat_Ambi_7_ACN
const uint16_t cMaxNumChannels = AAX_STEM_FORMAT_CHANNEL_COUNT(MAX_STEM_FORMAT);
const uint16_t cMaxNumMeters   = cMaxNumChannels * 2;

static const AAX_CTypeID cDemoGain_InputMeterID[cMaxNumChannels] = {
	 'InM1'
	,'InM2'
	,'InM3'
	,'InM4'
	,'InM5'
	,'InM6'
	,'InM7'
	,'InM8'
	,'InM9'
	,'IM10'
	,'IM11'
	,'IM12'
	,'IM13'
	,'IM14'
	,'IM15'
	,'IM16'
	,'IM17'
	,'IM18'
	,'IM19'
	,'IM20'
	,'IM21'
	,'IM22'
	,'IM23'
	,'IM24'
	,'IM25'
	,'IM26'
	,'IM27'
	,'IM28'
	,'IM29'
	,'IM30'
	,'IM31'
	,'IM32'
	,'IM33'
	,'IM34'
	,'IM35'
	,'IM36'
	,'IM37'
	,'IM38'
	,'IM39'
	,'IM40'
	,'IM41'
	,'IM42'
	,'IM43'
	,'IM44'
	,'IM45'
	,'IM46'
	,'IM47'
	,'IM48'
	,'IM49'
	,'IM50'
	,'IM51'
	,'IM52'
	,'IM53'
	,'IM54'
	,'IM55'
	,'IM56'
	,'IM57'
	,'IM58'
	,'IM59'
	,'IM60'
	,'IM61'
	,'IM62'
	,'IM63'
	,'IM64'
};

static const AAX_CTypeID cDemoGain_OutputMeterID[cMaxNumChannels] = {
	 'OuM1'
	,'OuM2'
	,'OuM3'
	,'OuM4'
	,'OuM5'
	,'OuM6'
	,'OuM7'
	,'OuM8'
	,'OuM9'
	,'OM10'
	,'OM11'
	,'OM12'
	,'OM13'
	,'OM14'
	,'OM15'
	,'OM16'
	,'OM17'
	,'OM18'
	,'OM19'
	,'OM20'
	,'OM21'
	,'OM22'
	,'OM23'
	,'OM24'
	,'OM25'
	,'OM26'
	,'OM27'
	,'OM28'
	,'OM29'
	,'OM30'
	,'OM31'
	,'OM32'
	,'OM33'
	,'OM34'
	,'OM35'
	,'OM36'
	,'OM37'
	,'OM38'
	,'OM39'
	,'OM40'
	,'OM41'
	,'OM42'
	,'OM43'
	,'OM44'
	,'OM45'
	,'OM46'
	,'OM47'
	,'OM48'
	,'OM49'
	,'OM50'
	,'OM51'
	,'OM52'
	,'OM53'
	,'OM54'
	,'OM55'
	,'OM56'
	,'OM57'
	,'OM58'
	,'OM59'
	,'OM60'
	,'OM61'
	,'OM62'
	,'OM63'
	,'OM64'
};

static const char * cDemoGain_GainIDs [cMaxNumChannels] = {
	 "Gain1"
	,"Gain2"
	,"Gain3"
	,"Gain4"
	,"Gain5"
	,"Gain6"
	,"Gain7"
	,"Gain8"
	,"Gain9"
	,"Gain10"
	,"Gain11"
	,"Gain12"
	,"Gain13"
	,"Gain14"
	,"Gain15"
	,"Gain16"
	,"Gain17"
	,"Gain18"
	,"Gain19"
	,"Gain20"
	,"Gain21"
	,"Gain22"
	,"Gain23"
	,"Gain24"
	,"Gain25"
	,"Gain26"
	,"Gain27"
	,"Gain28"
	,"Gain29"
	,"Gain30"
	,"Gain31"
	,"Gain32"
	,"Gain33"
	,"Gain34"
	,"Gain35"
	,"Gain36"
	,"Gain37"
	,"Gain38"
	,"Gain39"
	,"Gain40"
	,"Gain41"
	,"Gain42"
	,"Gain43"
	,"Gain44"
	,"Gain45"
	,"Gain46"
	,"Gain47"
	,"Gain48"
	,"Gain49"
	,"Gain50"
	,"Gain51"
	,"Gain52"
	,"Gain53"
	,"Gain54"
	,"Gain55"
	,"Gain56"
	,"Gain57"
	,"Gain58"
	,"Gain59"
	,"Gain60"
	,"Gain61"
	,"Gain62"
	,"Gain63"
	,"Gain64"
};

static const int32_t cDemoGain_TI_Counts[cMaxNumChannels][2] =
{
	// InstanceCycleCount, SharedCycleCount
	{ 141, 88 }, // 1 channel
	{ 248, 87 }, // 2 channels
	{ 347, 90 }, // 3 channels
	{ 452, 93 }, // 4 channels
	{ 557, 95 }, // 5 channels
	{ 662, 96 }, // 6 channels
	{ 767, 99 }, // 7 channels
	{ 872, 100 }, // 8 channels
	{ 978, 95 }, // 9 channels
	{ 1083, 96 }, // 10 channels
	{ 2508, 121 }, // 11 channels TODO:: update with correct measurement
	{ 2508, 121 }, // 12 channels TODO:: update with correct measurement
	{ 2508, 121 }, // 13 channels TODO:: update with correct measurement
	{ 2508, 121 }, // 14 channels TODO:: update with correct measurement
	{ 2508, 121 }, // 15 channels TODO:: update with correct measurement
	{ 1715, 98 }, // 16 channels
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 2508, 121 }, // 25 channels TODO:: update with correct measurement
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 2508, 121 }, // 36 channels TODO:: update with correct measurement
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 2508, 121 }, // 49 channels TODO:: update with correct measurement
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 2508, 121 } // 64 channels TODO:: update with correct measurement
};

static const char * cDemoGain_RoutingIDs [cMaxNumChannels] = {
    "Route1"
    ,"Route2"
    ,"Route3"
    ,"Route4"
    ,"Route5"
    ,"Route6"
    ,"Route7"
    ,"Route8"
    ,"Route9"
    ,"Route10"
    ,"Route11"
    ,"Route12"
    ,"Route13"
    ,"Route14"
    ,"Route15"
    ,"Route16"
	,"Route17"
	,"Route18"
	,"Route19"
	,"Route20"
	,"Route21"
	,"Route22"
	,"Route23"
	,"Route24"
	,"Route25"
	,"Route26"
	,"Route27"
	,"Route28"
	,"Route29"
	,"Route30"
	,"Route31"
	,"Route32"
	,"Route33"
	,"Route34"
	,"Route35"
	,"Route36"
	,"Route37"
	,"Route38"
	,"Route39"
	,"Route40"
	,"Route41"
	,"Route42"
	,"Route43"
	,"Route44"
	,"Route45"
	,"Route46"
	,"Route47"
	,"Route48"
	,"Route49"
	,"Route50"
	,"Route51"
	,"Route52"
	,"Route53"
	,"Route54"
	,"Route55"
	,"Route56"
	,"Route57"
	,"Route58"
	,"Route59"
	,"Route60"
	,"Route61"
	,"Route62"
	,"Route63"
	,"Route64"
};

#endif // DEMOGAIN_DEFS_H
