/*================================================================================================*/
/*
 *	Copyright 2012-2015, 2017, 2023-2024 Avid Technology, Inc.
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

// DemoSampler Includes
#include "DemoSampler_Describe.h"
#include "DemoSampler_Defs.h"
#include "DemoSampler_Parameters.h"

// AAX Includes
#include "AAX_ICollection.h"
#include "AAX_IComponentDescriptor.h"
#include "AAX_IEffectDescriptor.h"
#include "AAX_IPropertyMap.h"
#include "AAX_Exception.h"
#include "AAX_Errors.h"
#include "AAX_Assert.h"


static const AAX_CEffectID kEffectID_DemoSampler = "com.avid.aax.sdk.demosampler";


// ***************************************************************************
// ROUTINE:	GetEffectDescriptions
// ***************************************************************************
AAX_Result GetEffectDescriptions( AAX_ICollection * outCollection )
{
	AAX_CheckedResult err;
	AAX_IEffectDescriptor* const effectDescriptor = outCollection->NewDescriptor();
	if ( effectDescriptor == NULL )
		err = AAX_ERROR_NULL_OBJECT;
	
	// Effect identifiers
	err = effectDescriptor->AddName ( "Demo Sampler" );
	err = effectDescriptor->AddName ( "DmSm" );
	err = effectDescriptor->AddCategory ( AAX_ePlugInCategory_Example | AAX_ePlugInCategory_SWGenerators );
	
	err = effectDescriptor->AddResourceInfo ( AAX_eResourceType_PageTable, "DemoSamplerPages.xml" );
	
	// Describe the algorithm and effect specifics using the CMonolithicParameters convenience layer.  (Native Only)
	AAX_SInstrumentSetupInfo setupInfo;
	setupInfo.mInputStemFormat = AAX_eStemFormat_Mono;
	setupInfo.mOutputStemFormat = AAX_eStemFormat_Mono;
	setupInfo.mManufacturerID = cDemoSampler_ManufactureID;
	setupInfo.mProductID = cDemoSampler_ProductID;
	setupInfo.mPluginID = cDemoSampler_PlugInID_Native;
	setupInfo.mCanBypass = true;
	setupInfo.mNeedsInputMIDI = true;
	setupInfo.mInputMIDINodeName = "DemoMIDI_Sampler";
	setupInfo.mInputMIDIChannelMask = 0x0001;
	setupInfo.mNeedsGlobalMIDI = true;
	setupInfo.mGlobalMIDIEventMask = AAX_eMIDIClick;
	setupInfo.mNeedsTransport = true;
	err = AAX_CMonolithicParameters::StaticDescribe(effectDescriptor, setupInfo);
	
	// Add custom properties
	AAX_IPropertyMap* const properties = effectDescriptor->NewPropertyMap();
	if (properties)
	{
		err = properties->AddProperty(AAX_eProperty_SampleRate, AAX_eSampleRateMask_44100); // Samples are only set up for playback at 44.1 kHz
		err = properties->AddProperty(AAX_eProperty_UsesClientGUI, true); // Use the host-generated GUI

		// It's common practice to disable multi-mono support for instrument plug-ins, because
		// multi-mono instances on instrument tracks receive MIDI events only to their first instance by default.
		err = properties->AddProperty(AAX_eProperty_Constraint_MultiMonoSupport, false);

		err = effectDescriptor->SetProperties(properties);
	}
	else
		err = AAX_ERROR_NULL_OBJECT;
	
	// Data model
	err = effectDescriptor->AddProcPtr( (void *) DemoSampler_Parameters::Create, kAAX_ProcPtrID_Create_EffectParameters );
	
	// Add the Effect
	err = outCollection->AddEffect( kEffectID_DemoSampler, effectDescriptor );
	
	// Collection properties
	err = outCollection->SetManufacturerName( "Avid" );
	err = outCollection->AddPackageName( "DemoMIDISampler Plug-In" );
	err = outCollection->AddPackageName( "DemoSampler" );
	err = outCollection->AddPackageName( "DmSY" );
	err = outCollection->SetPackageVersion( 1 );		
	
	return err;
}
