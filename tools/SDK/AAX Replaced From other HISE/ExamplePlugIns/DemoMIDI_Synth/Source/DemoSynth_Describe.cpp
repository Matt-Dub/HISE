/*================================================================================================*/
/*
 *	Copyright 2012-2017, 2023-2024 Avid Technology, Inc.
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

// DemoSynth Includes
#include "DemoSynth_Describe.h"
#include "DemoSynth_Defs.h"
#include "DemoSynth_Parameters.h"

// AAX Includes
#include "AAX_CMonolithicParameters.h"
#include "AAX_ICollection.h"
#include "AAX_IComponentDescriptor.h"
#include "AAX_IEffectDescriptor.h"
#include "AAX_IPropertyMap.h"
#include "AAX_Exception.h"
#include "AAX_Errors.h"
#include "AAX_Assert.h"


static const AAX_CEffectID kEffectID_DemoSynth = "com.avid.aax.sdk.demomidi.synth";


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
	err = effectDescriptor->AddName ( "Demo Synth" );
	err = effectDescriptor->AddName ( "DmSy" );
	err = effectDescriptor->AddCategory ( AAX_ePlugInCategory_Example | AAX_ePlugInCategory_SWGenerators );
	err = effectDescriptor->AddResourceInfo ( AAX_eResourceType_PageTable, "DemoSynthPages.xml" );
	
	// Describe the algorithm and effect specifics using the CMonolithicParameters convenience layer.  (Native Only)
	AAX_SInstrumentSetupInfo setupInfo;
	setupInfo.mManufacturerID = cDemoSynth_ManufactureID;
	setupInfo.mProductID = cDemoSynth_ProductID;
	setupInfo.mCanBypass = true;
	setupInfo.mNeedsInputMIDI = true;
	setupInfo.mInputMIDINodeName = "Demo Synth";
	setupInfo.mInputMIDIChannelMask = 0x0001;
	setupInfo.mMultiMonoSupport = false; // See note for AAX_eProperty_Constraint_MultiMonoSupport
	//
	// Mono
	setupInfo.mInputStemFormat = AAX_eStemFormat_Mono;
	setupInfo.mOutputStemFormat = AAX_eStemFormat_Mono;
	setupInfo.mPluginID = cDemoSynth_PlugInID_Native_Mono;
	err = AAX_CMonolithicParameters::StaticDescribe(effectDescriptor, setupInfo);
	//
	// Stereo
	setupInfo.mInputStemFormat = AAX_eStemFormat_Stereo;
	setupInfo.mOutputStemFormat = AAX_eStemFormat_Stereo;
	setupInfo.mPluginID = cDemoSynth_PlugInID_Native_Stereo;
	err = AAX_CMonolithicParameters::StaticDescribe(effectDescriptor, setupInfo);
	
	// Add custom properties
	AAX_IPropertyMap* const properties = effectDescriptor->NewPropertyMap();
	if (properties)
	{
		// Use the host-generated GUI
		err = properties->AddProperty(AAX_eProperty_UsesClientGUI, true);
		
		// It's common practice to disable multi-mono support for instrument plug-ins, because
		// multi-mono instances on instrument tracks receive MIDI events only to their first instance by default.
		err = properties->AddProperty(AAX_eProperty_Constraint_MultiMonoSupport, false);
		
		err = effectDescriptor->SetProperties(properties);
	}
	else
		err = AAX_ERROR_NULL_OBJECT;
	
	// Data model
	err = effectDescriptor->AddProcPtr( (void *) DemoSynth_Parameters::Create, kAAX_ProcPtrID_Create_EffectParameters );
	
	// Add the Effect
	err = outCollection->AddEffect( kEffectID_DemoSynth, effectDescriptor );
		
	// Add properties to the Collection
	err = outCollection->SetManufacturerName( "Avid" );
	err = outCollection->AddPackageName( "DemoMIDI_Synth AAX SDK Example Plug-In" );
	err = outCollection->AddPackageName( "DemoMIDI_Synth" );
	err = outCollection->AddPackageName( "Demo Synth" );
	err = outCollection->AddPackageName( "DmSy" );
	err = outCollection->SetPackageVersion( 1 );
	
	return err;
}
