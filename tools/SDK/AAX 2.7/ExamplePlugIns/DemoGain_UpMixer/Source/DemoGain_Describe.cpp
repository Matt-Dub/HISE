/*================================================================================================*/
/*
 *	Copyright 2016-2017, 2019, 2021-2024 Avid Technology, Inc.
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

#include "DemoGain_Describe.h"
#include "DemoGain_Defs.h"
#include "DemoGain_Alg.h"
#include "DemoGain_Parameters.h"

// AAX Components
#include "AAX_ICollection.h"
#include "AAX_IComponentDescriptor.h"
#include "AAX_IEffectDescriptor.h"
#include "AAX_IPropertyMap.h"
#include "AAX_Errors.h"
#include "AAX_Exception.h"
#include "AAX_Assert.h"

// Standard Includes
#include <vector>

namespace
{
	const AAX_CEffectID kEffectID_DemoGain	= "com.avid.aax.sdk.demogain.upmixer";

	const char * cMeterNames_Inputs[cMaxNumChannels]  = 
	{
		"Input Meter 01",
		"Input Meter 02",
		"Input Meter 03",
		"Input Meter 04",
		"Input Meter 05",
		"Input Meter 06",
		"Input Meter 07",
		"Input Meter 08",
		"Input Meter 09",
		"Input Meter 10",
		"Input Meter 11",
		"Input Meter 12",
		"Input Meter 13",
		"Input Meter 14",
		"Input Meter 15",
		"Input Meter 16",
		"Input Meter 17",
		"Input Meter 18",
		"Input Meter 19",
		"Input Meter 10",
		"Input Meter 21",
		"Input Meter 22",
		"Input Meter 23",
		"Input Meter 24",
		"Input Meter 25",
		"Input Meter 26",
		"Input Meter 27",
		"Input Meter 28",
		"Input Meter 29",
		"Input Meter 30",
		"Input Meter 31",
		"Input Meter 32",
		"Input Meter 33",
		"Input Meter 34",
		"Input Meter 35",
		"Input Meter 36",
		"Input Meter 37",
		"Input Meter 38",
		"Input Meter 39",
		"Input Meter 40",
		"Input Meter 41",
		"Input Meter 42",
		"Input Meter 43",
		"Input Meter 44",
		"Input Meter 45",
		"Input Meter 46",
		"Input Meter 47",
		"Input Meter 48",
		"Input Meter 49",
		"Input Meter 50",
		"Input Meter 51",
		"Input Meter 52",
		"Input Meter 53",
		"Input Meter 54",
		"Input Meter 55",
		"Input Meter 56",
		"Input Meter 57",
		"Input Meter 58",
		"Input Meter 59",
		"Input Meter 60",
		"Input Meter 61",
		"Input Meter 62",
		"Input Meter 63",
		"Input Meter 64"
	};

	const char * cMeterNames_Outputs[cMaxNumChannels] =
	{
		"Output Meter 01",
		"Output Meter 02",
		"Output Meter 03",
		"Output Meter 04",
		"Output Meter 05",
		"Output Meter 06",
		"Output Meter 07",
		"Output Meter 08",
		"Output Meter 09",
		"Output Meter 10",
		"Output Meter 11",
		"Output Meter 12",
		"Output Meter 13",
		"Output Meter 14",
		"Output Meter 15",
		"Output Meter 16",
		"Output Meter 17",
		"Output Meter 18",
		"Output Meter 19",
		"Output Meter 10",
		"Output Meter 21",
		"Output Meter 22",
		"Output Meter 23",
		"Output Meter 24",
		"Output Meter 25",
		"Output Meter 26",
		"Output Meter 27",
		"Output Meter 28",
		"Output Meter 29",
		"Output Meter 30",
		"Output Meter 31",
		"Output Meter 32",
		"Output Meter 33",
		"Output Meter 34",
		"Output Meter 35",
		"Output Meter 36",
		"Output Meter 37",
		"Output Meter 38",
		"Output Meter 39",
		"Output Meter 40",
		"Output Meter 41",
		"Output Meter 42",
		"Output Meter 43",
		"Output Meter 44",
		"Output Meter 45",
		"Output Meter 46",
		"Output Meter 47",
		"Output Meter 48",
		"Output Meter 49",
		"Output Meter 50",
		"Output Meter 51",
		"Output Meter 52",
		"Output Meter 53",
		"Output Meter 54",
		"Output Meter 55",
		"Output Meter 56",
		"Output Meter 57",
		"Output Meter 58",
		"Output Meter 59",
		"Output Meter 60",
		"Output Meter 61",
		"Output Meter 62",
		"Output Meter 63",
		"Output Meter 64"
	};

	// Structure representing a host context in which this
	// plug-in is supported. Note that this plug-in does
	// not register any offline (AudioSuite) support since
	// AAX does not allow width-changing AudioSuite plug-ins.
	struct SHostContext
	{
		AAX_EStemFormat mInputStemFormat;
		AAX_EStemFormat mOutputStemFormat;
		AAX_ETargetPlatform mTargetPlatform;
	};
	
	// ***************************************************************************
	// FUNCTION:	PlugInID
	// Generate a plug-in ID for a given configuration
	//
	// WARNING: Using algorithmic generation of type IDs.
	// The resulting IDs MUST NEVER CHANGE between versions
	// of this plug-in. Changes will result in compatibility
	// bugs with saved sessions that are very difficult to
	// resolve successfully.
	//
	// Whenever this approach is taken in production code
	// the resulting IDs should be tested at compile time
	// for consistency against known expected values.
	// ***************************************************************************
	AAX_Result PlugInID(const SHostContext& inHostContext, AAX_CTypeID& outTypeID, AAX_EProperty& outProperty)
	{
		AAX_Result result = AAX_SUCCESS;
		AAX_EProperty property = AAX_eProperty_NoID;
		
		uint8_t plat = 0;
		if (inHostContext.mTargetPlatform == kAAX_eTargetPlatform_Native) {
			plat = 'N';
			property = AAX_eProperty_PlugInID_Native;
		}
		else if (inHostContext.mTargetPlatform == kAAX_eTargetPlatform_TI) {
			plat = 'T';
			property = AAX_eProperty_PlugInID_TI;
		}
		else {
			result = AAX_ERROR_INVALID_ARGUMENT;
		}
		
		if (AAX_SUCCESS == result)
		{
			const uint8_t ifmt = 'A' + AAX_STEM_FORMAT_INDEX(inHostContext.mInputStemFormat);
			const uint8_t ofmt = 'A' + AAX_STEM_FORMAT_INDEX(inHostContext.mOutputStemFormat);
			
			outTypeID = 0x0;
			outTypeID |= (ofmt << 0);
			outTypeID |= (ifmt << 8);
			outTypeID |= ('_'  << 16);
			outTypeID |= (plat << 24);
			
			outProperty = property;
		}
		
		return result;
	}

	// ***************************************************************************
	// ROUTINE:	DescribeAlgorithmComponent
	// Algorithm component description
	// ***************************************************************************
	template<AAX_EStemFormat kInputStemFormat, AAX_EStemFormat kOutputStemFormat>
	AAX_Result DescribeAlgorithmComponent( AAX_IComponentDescriptor * outDesc )
	{
		AAX_CheckedResult err;
		const uint16_t cNumInChannels = AAX_STEM_FORMAT_CHANNEL_COUNT ( kInputStemFormat );
		const uint16_t cNumOutChannels = AAX_STEM_FORMAT_CHANNEL_COUNT ( kOutputStemFormat );
				
		// Describe algorithm's context structure
		//
		// Subscribe context fields to host-provided services or information
		err = outDesc->AddAudioIn (eAlgPortID_AudioIn);
		err = outDesc->AddAudioOut (eAlgPortID_AudioOut);
		err = outDesc->AddAudioBufferLength (eAlgPortID_BufferSize);

		// Register context fields as communications destinations (i.e. input)
		err = outDesc->AddDataInPort ( eAlgPortID_BypassIn, sizeof (int32_t) );
		err = outDesc->AddDataInPort ( eAlgPortID_CoefsGainIn, sizeof (SDemoGain_CoefsGain) );
		err = outDesc->AddDataInPort ( eAlgPortID_RoutingMapIn, sizeof (SDemoGain_RoutingMap) );
		
		// Meter section
		if (cMaxNumChannels >= cNumInChannels && cMaxNumChannels >= cNumOutChannels)
		{
			AAX_CTypeID	meterIDs[ cMaxNumMeters ];
			const uint16_t    cNumMeters = cNumInChannels + cNumOutChannels;
			uint16_t    index = 0;
			
			// Input meters
			uint16_t channelIndex = 0;
			while ( channelIndex < cNumInChannels )
				meterIDs[index++] = cDemoGain_InputMeterID[channelIndex++];
			
			// Output meters
			channelIndex = 0;
			while ( channelIndex < cNumOutChannels )
				meterIDs[index++] = cDemoGain_OutputMeterID[channelIndex++];

			err = outDesc->AddMeters ( eAlgPortID_Meters, meterIDs, cNumMeters );
		}
		else
		{
			err = outDesc->AddPrivateData ( eAlgPortID_Meters, 1 );
		}
		
		// Register processing callbacks
		//
		// Create a property map 
		AAX_IPropertyMap* properties = outDesc->NewPropertyMap();
		if ( !properties )
			err = AAX_ERROR_NULL_OBJECT;
		//
		// Required properties
		err = properties->AddProperty ( AAX_eProperty_ManufacturerID, cDemoGain_ManufactureID );
		err = properties->AddProperty ( AAX_eProperty_ProductID, cDemoGain_UpMixer_ProductID );
		err = properties->AddProperty ( AAX_eProperty_InputStemFormat, kInputStemFormat );
		err = properties->AddProperty ( AAX_eProperty_OutputStemFormat, kOutputStemFormat );
		
		// Optional properties
		err = properties->AddProperty ( AAX_eProperty_CanBypass, true );
		err = properties->AddProperty ( AAX_eProperty_UsesClientGUI, true );
		
		AAX_CTypeID plugInIDValue = AAX_eProperty_NoID;
		AAX_EProperty plugInIDProperty = AAX_eProperty_NoID;
		err = PlugInID( SHostContext({kInputStemFormat, kOutputStemFormat, kAAX_eTargetPlatform_Native}), plugInIDValue, plugInIDProperty );
		err = properties->AddProperty ( plugInIDProperty, plugInIDValue );
		
		// Register Native callback
		err = outDesc->AddProcessProc_Native(DemoGain_AlgorithmProcessFunction< cNumInChannels, cNumOutChannels >, properties);

		AAX_CTypeID plugInIDValue_TI = AAX_eProperty_NoID;
		AAX_EProperty plugInIDProperty_TI = AAX_eProperty_NoID;
		err = PlugInID( SHostContext({kInputStemFormat, kOutputStemFormat, kAAX_eTargetPlatform_TI}), plugInIDValue_TI, plugInIDProperty_TI );
		err = properties->AddProperty ( plugInIDProperty_TI, plugInIDValue_TI );

		// Register TI-specific properties
		properties->AddProperty(AAX_eProperty_DSP_AudioBufferLength, AAX_eAudioBufferLengthDSP_Default);
#ifndef AAX_TI_BINARY_IN_DEVELOPMENT // Define this macro when using a debug TI DLL to allocate only 1 instance per chip
		properties->AddProperty(AAX_eProperty_TI_InstanceCycleCount, cDemoGain_TI_Counts[cNumOutChannels - 1][0]);
		properties->AddProperty(AAX_eProperty_TI_SharedCycleCount, cDemoGain_TI_Counts[cNumOutChannels - 1][1]);
#endif
		// Register TI callback
		AAX_CString dllName("DemoGain_UpMixer_");
		dllName.AppendNumber(cNumInChannels);
		dllName.Append("ch_TI_Example.dll");
		AAX_CString algEntryName("AlgEntry_");
		algEntryName.AppendNumber(cNumInChannels);
		algEntryName.Append("_");
		algEntryName.AppendNumber(cNumOutChannels);
		err = outDesc->AddProcessProc_TI(dllName.CString(), algEntryName.CString(), properties);
		
		return err;
	}
	
	// ***************************************************************************
	// ROUTINE:	AddAlgorithmComponentDescription
	// Create algorithm component description and add to an effect description
	// ***************************************************************************
	template<AAX_EStemFormat kInputStemFormat, AAX_EStemFormat kOutputStemFormat>
	AAX_Result AddAlgorithmComponentDescription( AAX_IEffectDescriptor& outEffectDescriptor )
	{
		AAX_Result result = AAX_SUCCESS;
		AAX_CAPTURE_MULT(result,
			AAX_CheckedResult err;
			AAX_IComponentDescriptor* compDesc = outEffectDescriptor.NewComponentDescriptor ();
			if ( !compDesc )
				err = AAX_ERROR_NULL_OBJECT;
			
			err = compDesc->Clear();
			err = DescribeAlgorithmComponent<kInputStemFormat, kOutputStemFormat>(compDesc);
			err = outEffectDescriptor.AddComponent( compDesc );
		);
		return result;
	}
	
	// This example uses a bit of template metaprogramming in order to register the algorithm's
	// input and output stem formats using template parameters. This appraoch is used specifically
	// to ensure that a different entrypoint is used for each stem format in the TI DLL. Native
	// plug-ins can use run-time resolution.
	//
	// Usage example:
	//   AAX_IEffectDescriptor* desc = description_object;
	//   AAX_Result result;
	//   int numComponentsAdded = 0;
	//   numComponentsAdded += TMDoDescribeAlgorithmComponents<target_platform_1>(desc, result);
	//   numComponentsAdded += TMDoDescribeAlgorithmComponents<target_platform_2>(desc, result);
	//   if (0 == numComponentsAdded && AAX_SUCCESS != result)
	//     return result;
	//
	// TMStemFormat: Association of indices to stem formats
	//   Note: a better way to do this is with overloaded operator[] but Visual Studio 2013 does
	//   not support the constexpr keyword, which would be required for this use of operator[].
	template <int I> struct TMStemFormat {};
	template <> struct TMStemFormat<0>  { static const AAX_EStemFormat get = AAX_eStemFormat_Mono; };
	template <> struct TMStemFormat<1>  { static const AAX_EStemFormat get = AAX_eStemFormat_Stereo; };
	template <> struct TMStemFormat<2>  { static const AAX_EStemFormat get = AAX_eStemFormat_LCR; };
	template <> struct TMStemFormat<3>  { static const AAX_EStemFormat get = AAX_eStemFormat_LCRS; };
	template <> struct TMStemFormat<4>  { static const AAX_EStemFormat get = AAX_eStemFormat_Quad; };
	template <> struct TMStemFormat<5>  { static const AAX_EStemFormat get = AAX_eStemFormat_5_0; };
	template <> struct TMStemFormat<6>  { static const AAX_EStemFormat get = AAX_eStemFormat_5_1; };
	template <> struct TMStemFormat<7>  { static const AAX_EStemFormat get = AAX_eStemFormat_6_0; };
	template <> struct TMStemFormat<8>  { static const AAX_EStemFormat get = AAX_eStemFormat_6_1; };
	template <> struct TMStemFormat<9>  { static const AAX_EStemFormat get = AAX_eStemFormat_7_0_SDDS; };
	template <> struct TMStemFormat<10> { static const AAX_EStemFormat get = AAX_eStemFormat_7_1_SDDS; };
	template <> struct TMStemFormat<11> { static const AAX_EStemFormat get = AAX_eStemFormat_7_0_DTS; };
	template <> struct TMStemFormat<12> { static const AAX_EStemFormat get = AAX_eStemFormat_7_1_DTS; };
	template <> struct TMStemFormat<13> { static const AAX_EStemFormat get = AAX_eStemFormat_7_0_2; };
	template <> struct TMStemFormat<14> { static const AAX_EStemFormat get = AAX_eStemFormat_7_1_2; };
	template <> struct TMStemFormat<15> { static const AAX_EStemFormat get = AAX_eStemFormat_Ambi_1_ACN; };
	template <> struct TMStemFormat<16> { static const AAX_EStemFormat get = AAX_eStemFormat_Ambi_2_ACN; };
	template <> struct TMStemFormat<17> { static const AAX_EStemFormat get = AAX_eStemFormat_Ambi_3_ACN; };
	template <> struct TMStemFormat<18> { static const AAX_EStemFormat get = AAX_eStemFormat_Ambi_4_ACN; };
	template <> struct TMStemFormat<19> { static const AAX_EStemFormat get = AAX_eStemFormat_Ambi_5_ACN; };
	template <> struct TMStemFormat<20> { static const AAX_EStemFormat get = AAX_eStemFormat_Ambi_6_ACN; };
	template <> struct TMStemFormat<21> { static const AAX_EStemFormat get = AAX_eStemFormat_Ambi_7_ACN; };
	template <> struct TMStemFormat<22> { static const AAX_EStemFormat get = AAX_eStemFormat_5_0_2; };
	template <> struct TMStemFormat<23> { static const AAX_EStemFormat get = AAX_eStemFormat_5_1_2; };
	template <> struct TMStemFormat<24> { static const AAX_EStemFormat get = AAX_eStemFormat_5_0_4; };
	template <> struct TMStemFormat<25> { static const AAX_EStemFormat get = AAX_eStemFormat_5_1_4; };
	template <> struct TMStemFormat<26> { static const AAX_EStemFormat get = AAX_eStemFormat_7_0_4; };
	template <> struct TMStemFormat<27> { static const AAX_EStemFormat get = AAX_eStemFormat_7_1_4; };
	template <> struct TMStemFormat<28> { static const AAX_EStemFormat get = AAX_eStemFormat_9_0_4; };
	template <> struct TMStemFormat<29> { static const AAX_EStemFormat get = AAX_eStemFormat_9_1_4; };
	template <> struct TMStemFormat<30> { static const AAX_EStemFormat get = AAX_eStemFormat_9_0_6; };
	template <> struct TMStemFormat<31> { static const AAX_EStemFormat get = AAX_eStemFormat_9_1_6; };
	template <> struct TMStemFormat<32> { static const AAX_EStemFormat get = AAX_eStemFormat_7_0_6; };
	template <> struct TMStemFormat<33> { static const AAX_EStemFormat get = AAX_eStemFormat_7_1_6; };

	static const int TMStemFormatSize = 34; // simple approach
	//
	// TMP loop functions
	template <AAX_EStemFormat kInputStemFormat, int I=TMStemFormatSize>
	struct TMDoDescribeAlgorithmComponentsOfInputFormat {
		static void Run( AAX_IEffectDescriptor& outEffectDescriptor, AAX_AggregateResult& ioAggregateResult ) {
//            if (TMStemFormat<I-1>::get != kInputStemFormat) { // don't register non-converting combinations
			if((kInputStemFormat >= AAX_eStemFormat_Ambi_4_ACN && TMStemFormat<I-1>::get == kInputStemFormat) || (kInputStemFormat < AAX_eStemFormat_Ambi_4_ACN && TMStemFormat<I-1>::get < AAX_eStemFormat_Ambi_4_ACN)){
				// To avoid long load times when there are many variants
				// registered by one AAX plug-in, reduce the total number
				// of variants for DemoGain_UpMixer to only N > N for
				// certain formats
				ioAggregateResult = AddAlgorithmComponentDescription<kInputStemFormat, TMStemFormat<I-1>::get>(outEffectDescriptor);
			}
//            }
			
			// next
			TMDoDescribeAlgorithmComponentsOfInputFormat<kInputStemFormat, I-1>::Run(outEffectDescriptor, ioAggregateResult);
		}
	};
	template<AAX_EStemFormat kInputStemFormat>
	struct TMDoDescribeAlgorithmComponentsOfInputFormat<kInputStemFormat, 0> {
		static void Run( AAX_IEffectDescriptor&, AAX_AggregateResult& ) { /* terminal case: no action */ }
	};
	//
	template <int I=TMStemFormatSize>
	struct TMDoDescribeAlgorithmComponents {
		static void Run( AAX_IEffectDescriptor& outEffectDescriptor, AAX_AggregateResult& ioAggregateResult ) {
			TMDoDescribeAlgorithmComponentsOfInputFormat<TMStemFormat<I-1>::get>::Run(outEffectDescriptor, ioAggregateResult);
			TMDoDescribeAlgorithmComponents<I-1>::Run(outEffectDescriptor, ioAggregateResult);
		}
	};
	template<>
	struct TMDoDescribeAlgorithmComponents<0> {
		static void Run( AAX_IEffectDescriptor&, AAX_AggregateResult& ) { /* terminal case: no action */ }
	};
	
	// ***************************************************************************
	// ROUTINE:	DemoGain_GetPlugInDescription
	// ***************************************************************************
	AAX_Result DemoGain_GetPlugInDescription( AAX_IEffectDescriptor * outDescriptor )
	{
		AAX_CheckedResult err;
		
		// Effect identifiers
		//
		err = outDescriptor->AddName ( "Demo Gain (UpMixer)" );
		err = outDescriptor->AddName ( "DemoGain" );
		err = outDescriptor->AddName ( "DmGain" );
		err = outDescriptor->AddName ( "DGpr" );
		err = outDescriptor->AddName ( "Dn" );
		err = outDescriptor->AddCategory ( AAX_ePlugInCategory_Example );
		
		// Effect components
		//
		// Algorithm component
		//
		{
			// Register all input/output stem format combinations
			AAX_AggregateResult agg;
			TMDoDescribeAlgorithmComponents<>::Run(*outDescriptor, agg);
			
			// throw an exception using the last error if none
			// of the components were successfully registered
			if (0 == agg.NumSucceeded()) {
				err = agg.LastFailure();
			}
		}
		
		// Data model
		//
		err = outDescriptor->AddProcPtr( (void *) DemoGain_Parameters::Create, kAAX_ProcPtrID_Create_EffectParameters );
		outDescriptor->AddResourceInfo ( AAX_eResourceType_PageTable, "DemoGainPages.xml" );

		// Effect's meter display properties
		//
		// Input meters
		{
			AAX_IPropertyMap* const inputMeterProperties = outDescriptor->NewPropertyMap();
			if (!inputMeterProperties)
				err = AAX_ERROR_NULL_OBJECT;
			
			err = inputMeterProperties->AddProperty ( AAX_eProperty_Meter_Type, AAX_eMeterType_Input );
			err = inputMeterProperties->AddProperty ( AAX_eProperty_Meter_Orientation, AAX_eMeterOrientation_Default );
			
			
			for (uint32_t channelIndex = 0; channelIndex < cMaxNumChannels; ++channelIndex)
			{
				err = outDescriptor->AddMeterDescription ( cDemoGain_InputMeterID [ channelIndex ], cMeterNames_Inputs [ channelIndex ], inputMeterProperties );
			}
		}
		// Output meters
		{
			AAX_IPropertyMap* const outputMeterProperties = outDescriptor->NewPropertyMap();
			if (!outputMeterProperties)
				err = AAX_ERROR_NULL_OBJECT;
			
			err = outputMeterProperties->AddProperty ( AAX_eProperty_Meter_Type, AAX_eMeterType_Output );
			err = outputMeterProperties->AddProperty ( AAX_eProperty_Meter_Orientation, AAX_eMeterOrientation_Default );
		
			for (uint32_t channelIndex = 0 ; channelIndex < cMaxNumChannels; ++channelIndex)
			{
				err = outDescriptor->AddMeterDescription ( cDemoGain_OutputMeterID [ channelIndex ], cMeterNames_Outputs [ channelIndex ], outputMeterProperties );
			}
		}

		return err;
	}
} // end unnamed namespace

// ***************************************************************************
// ROUTINE:	GetEffectDescriptions
// ***************************************************************************
AAX_Result GetEffectDescriptions( AAX_ICollection * outCollection )
{
	AAX_CheckedResult err;
	AAX_IEffectDescriptor* const plugInDescriptor = outCollection->NewDescriptor();
	if ( plugInDescriptor )
	{
		AAX_SWALLOW_MULT(
			err = DemoGain_GetPlugInDescription( plugInDescriptor );
			err = outCollection->AddEffect( kEffectID_DemoGain, plugInDescriptor );
		);
	}
	else
		err = AAX_ERROR_NULL_OBJECT;
	
	err = outCollection->SetManufacturerName( "Avid" );
	err = outCollection->AddPackageName( "DemoGainUpMixer AAX SDK Example Plug-In" );
	err = outCollection->AddPackageName( "DemoGainUMixer" );
	err = outCollection->AddPackageName( "DemoGainUMix" );
	err = outCollection->AddPackageName( "DemoGainU" );
	err = outCollection->AddPackageName( "DmGU" );
	err = outCollection->SetPackageVersion( 1 );
	
	return err;
}
