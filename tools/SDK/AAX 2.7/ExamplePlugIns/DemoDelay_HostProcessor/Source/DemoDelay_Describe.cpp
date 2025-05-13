/*================================================================================================*/
/*
 *	Copyright 2014-2015, 2017, 2023-2024 Avid Technology, Inc.
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
#include "DemoDelay_Describe.h"
#include "HostProcessor/HostProcessor_Describe.h"
#include "HostProcessor_Comp/HostProcessor_Comp_Describe.h"

// AAX Includes
#include "AAX_ICollection.h"
#include "AAX_Exception.h"

// ***************************************************************************
// ROUTINE:	GetEffectDescriptions
// ***************************************************************************
AAX_Result GetEffectDescriptions( AAX_ICollection * outCollection )
{
    AAX_CheckedResult err;
	
	// This plug-in includes two separate Effects
	//	Delay: This effect implements a standard delay algorithm using the Host Processor interface. The
	//		behavior of this Effect is identical to that of the standard DemoDelay AudioSuite plug-in.
	//	Delay Comp: This effect demonstrates the Host Processor interface's random-access functionality
	//		by "compensating" for its algorithm's delay and place input samples back into their original
	//		location on the timeline.
	err = HostProcessor_GetEffectDescriptions( outCollection );
	err = HostProcessor_Comp_GetEffectDescriptions( outCollection );
	
	err = outCollection->SetManufacturerName( "Avid" );
	err = outCollection->AddPackageName( "DemoDelay (HostProcessor) AAX SDK Example Plug-In" );
	err = outCollection->AddPackageName( "DemoDelay (HostProcessor)" );
	err = outCollection->AddPackageName( "DemoDelay HostProcessor" );
	err = outCollection->AddPackageName( "DemoDelay HP" );
	err = outCollection->AddPackageName( "DemoDelay" );
	err = outCollection->AddPackageName( "DmDly" );
	err = outCollection->SetPackageVersion( 1 );		
	
	return err;
}
