/*================================================================================================*/
/*
 *	Copyright 2024 Avid Technology, Inc.
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

// DemoMIDI Includes
#include "DemoMIDI_Describe.h"
#include "DemoMIDI_Alg.h"
#include "DemoMIDI_Parameters.h"
#include "DemoMIDI_Defs.h"

// AAX Includes
#include "AAX_ICollection.h"
#include "AAX_IComponentDescriptor.h"
#include "AAX_IEffectDescriptor.h"
#include "AAX_IPropertyMap.h"
#include "AAX_Exception.h"
#include "AAX_Errors.h"
#include "AAX_Assert.h"

// Other Includes
#include <array>

// ***************************************************************************
// ROUTINE:	DescribeAlgorithmComponent
// Algorithm component description
// ***************************************************************************
static void DescribeAlgorithmComponent( const AAX_EStemFormat		inStemFormat,
										const AAX_CTypeID			inStemID,
										AAX_IComponentDescriptor*	outDesc )
{
	AAX_CheckedResult err;
	
	// Describe the fields in the algorithm's context structure
	//
	// Subscribe context fields to host-provided services or information
	err = outDesc->AddAudioIn( eAlgFieldID_AudioIn );
	err = outDesc->AddAudioOut( eAlgFieldID_AudioOut );
	err = outDesc->AddAudioBufferLength( eAlgFieldID_BufferSize );
	//
	// Register context fields for controls
	err = outDesc->AddDataInPort( eAlgPortID_Coefficients, sizeof( SCoefficients ) );
	//
	// Register MIDI nodes
	err = outDesc->AddMIDINode( eAlgPortID_MIDINodeIn,	AAX_eMIDINodeType_LocalInput,	"MIDI Transpose In",	0x0001 );
	err = outDesc->AddMIDINode( eAlgPortID_MIDINodeOut,	AAX_eMIDINodeType_LocalOutput,	"MIDI Transpose Out",	0x0001 );
	//
	// Register private data
	err = outDesc->AddPrivateData( eAlgPortID_PrivateData,		sizeof( SPrivateData ) );
	err = outDesc->AddPrivateData( eAlgPortID_NumAudioChannels,	sizeof( int32_t ) );
	
	// Describe the algorithms properties
	//
	// Create a property map 
	AAX_IPropertyMap* const properties = outDesc->NewPropertyMap();
	if ( !properties )
		err = AAX_ERROR_NULL_OBJECT;
	//
	// Generic properties
	err = properties->AddProperty( AAX_eProperty_ManufacturerID,	cDemoMIDI_ManufacturerID );
	err = properties->AddProperty( AAX_eProperty_ProductID,			cDemoMIDI_ProductID );
	err = properties->AddProperty( AAX_eProperty_CanBypass,			true );
	err = properties->AddProperty( AAX_eProperty_UsesClientGUI,		true ); // Uses auto-GUI
	//
	// Stem format -specific properties
	err = properties->AddProperty( AAX_eProperty_InputStemFormat,	inStemFormat );
	err = properties->AddProperty( AAX_eProperty_OutputStemFormat,	inStemFormat );
	//
	// Add the ID for the current stem format
	err = properties->AddProperty( AAX_eProperty_PlugInID_Native,	inStemID );
	//
	// Register algorithm callback for AAX Native
	err = outDesc->AddProcessProc_Native( DemoMIDI_AlgorithmProcessFunction, properties );
}

// ***************************************************************************
// ROUTINE:	DescribeEffect
// ***************************************************************************
static AAX_Result DescribeEffect( AAX_IEffectDescriptor* outDescriptor )
{
	AAX_CheckedResult err;
	AAX_IComponentDescriptor* const compDesc = outDescriptor->NewComponentDescriptor ();
	if ( !compDesc )
		err = AAX_ERROR_NULL_OBJECT;
	
	// Effect identifiers
	//
	err = outDescriptor->AddName( "Demo MIDI Transpose" );
	err = outDescriptor->AddName( "DemoMIDITranspose" );
	err = outDescriptor->AddName( "Transpose" );
	err = outDescriptor->AddName( "Trans" );
	err = outDescriptor->AddName( "DT" );

	err = outDescriptor->AddCategory( AAX_ePlugInCategory_Example );
	err = outDescriptor->AddCategory( AAX_EPlugInCategory_MIDIEffect );
	
	// Effect components
	//
	// Describe algorithm component for different stem formats
	for ( auto stemFormatAndId : cStemFormatsAndIds )
	{
		compDesc->Clear();
		DescribeAlgorithmComponent( stemFormatAndId.first,
								    stemFormatAndId.second,
									compDesc );
		err = outDescriptor->AddComponent( compDesc );
	}
	//
	// Data model
	err = outDescriptor->AddProcPtr( reinterpret_cast<void *>(DemoMIDI_Parameters::Create), kAAX_ProcPtrID_Create_EffectParameters );
	err = outDescriptor->AddResourceInfo(AAX_eResourceType_PageTable, "DemoMIDIPages.xml");
	
	return err;
}

// ***************************************************************************
// ROUTINE:	GetEffectDescriptions
// ***************************************************************************
AAX_Result GetEffectDescriptions( AAX_ICollection * outCollection )
{
	AAX_CheckedResult err;
	AAX_IEffectDescriptor* const plugInDescriptor = outCollection->NewDescriptor();
	
	if ( plugInDescriptor )
	{
		err = DescribeEffect( plugInDescriptor );
		err = outCollection->AddEffect( cEffectID_DemoMIDI, plugInDescriptor );
	}
	else
	{
		err = AAX_ERROR_NULL_OBJECT;
	}
	
	err = outCollection->SetManufacturerName( "Avid" );
	err = outCollection->AddPackageName( "DemoMIDI AAX SDK Example Plug-In" );
	err = outCollection->AddPackageName( "DemoMIDI" );
	err = outCollection->AddPackageName( "DmMD" );
	err = outCollection->SetPackageVersion( 1 );
	
	return err;
}
