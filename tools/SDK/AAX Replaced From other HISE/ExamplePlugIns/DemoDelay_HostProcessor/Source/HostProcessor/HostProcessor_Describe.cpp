/*================================================================================================*/
/*
 *	Copyright 2013-2015, 2018, 2023-2024 Avid Technology, Inc.
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

// DemoDelay Includes
#include "HostProcessor_Describe.h"
#include "DemoDelay_Describe.h"
#include "DemoDelay_HostProcessor.h"
#include "DemoDelay_Parameters.h"
#include "DemoDelay_Defs.h"

// AAX Includes
#include "AAX_ICollection.h"
#include "AAX_IEffectDescriptor.h"
#include "AAX_IPropertyMap.h"
#include "AAX_Exception.h"
#include "AAX_Assert.h"


// ***************************************************************************
// ROUTINE:	Delay_GetPlugInDescription
// ***************************************************************************
static AAX_Result Delay_GetPlugInDescription( AAX_IEffectDescriptor * outDescriptor )
{
	AAX_CheckedResult err;
	
    AAX_IPropertyMap* const properties = outDescriptor->NewPropertyMap();
	if (!properties)
		err = AAX_ERROR_NULL_OBJECT;
	
	err = properties->AddProperty ( AAX_eProperty_ManufacturerID, cDemoDelay_ManufactureID );
	err = properties->AddProperty ( AAX_eProperty_ProductID, cDemoDelay_ProductID );
	err = properties->AddProperty ( AAX_eProperty_PlugInID_AudioSuite, cDemoDelay_PlugInID_AudioSuite );
	err = properties->AddProperty ( AAX_eProperty_NumberOfInputs, AAX_eMaxAudioSuiteTracks );
	err = properties->AddProperty ( AAX_eProperty_NumberOfOutputs, AAX_eMaxAudioSuiteTracks );
    err = properties->AddProperty ( AAX_eProperty_UsesClientGUI, true );
	
	err = outDescriptor->AddName ( "Demo Delay (HostProcessor)" );
	err = outDescriptor->AddName ( "Demo Delay (HP)" );
	err = outDescriptor->AddName ( "DmDly HP" );
	err = outDescriptor->AddName ( "DmDly" );
	err = outDescriptor->AddName ( "Dly" );
	
	err = outDescriptor->AddCategory ( AAX_ePlugInCategory_Example );
    
    err = outDescriptor->AddProcPtr(reinterpret_cast<void*>(DemoDelay_Parameters::Create), kAAX_ProcPtrID_Create_EffectParameters);
    err = outDescriptor->AddProcPtr(reinterpret_cast<void*>(DemoDelay_HostProcessor::Create), kAAX_ProcPtrID_Create_HostProcessor);
    
    err = outDescriptor->SetProperties(properties);
    
    return err;
}

// ***************************************************************************
// ROUTINE:	HostProcessor_GetEffectDescriptions
// ***************************************************************************
AAX_Result HostProcessor_GetEffectDescriptions( AAX_ICollection * outCollection )
{
	AAX_CheckedResult err;
	static const AAX_CEffectID effectID_DemoDelay = "com.avid.aax.sdk.demodelay.hostprocessor";
	AAX_IEffectDescriptor* const plugInDescriptor = outCollection->NewDescriptor();
	if ( plugInDescriptor )
	{
		AAX_SWALLOW_MULT(
			err = Delay_GetPlugInDescription( plugInDescriptor );
			err = outCollection->AddEffect( effectID_DemoDelay, plugInDescriptor );
		);
	}
	else
		err = AAX_ERROR_NULL_OBJECT;
    
    return err;
}
