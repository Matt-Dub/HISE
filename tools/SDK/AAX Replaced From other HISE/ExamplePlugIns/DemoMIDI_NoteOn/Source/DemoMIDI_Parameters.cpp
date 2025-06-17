/*================================================================================================*/
/*
 *	Copyright 2009-2015, 2017, 2023-2024 Avid Technology, Inc.
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
#include "DemoMIDI_Parameters.h"
#include "DemoMIDI_Defs.h"
#include "DemoMIDI_Alg.h"

// AAX Includes
#include "AAX_CBinaryTaperDelegate.h"
#include "AAX_CBinaryDisplayDelegate.h"
#include "AAX_CLinearTaperDelegate.h"
#include "AAX_CNumberDisplayDelegate.h"
#include "AAX_MIDIUtilities.h"
#include "AAX_Assert.h"

// Standard Includes
#include <memory>

// *******************************************************************************
// ROUTINE:	Create
// *******************************************************************************
AAX_CEffectParameters *AAX_CALLBACK DemoMIDI_Parameters::Create()
{
	return new DemoMIDI_Parameters();
}

// *******************************************************************************
// METHOD:	DemoMIDI_Parameters
// *******************************************************************************
DemoMIDI_Parameters::DemoMIDI_Parameters () :
AAX_CEffectParameters()
{
}

// *******************************************************************************
// METHOD:	EffectInit
// *******************************************************************************
AAX_Result DemoMIDI_Parameters::EffectInit()
{	
	//Add parameters
	{
		std::unique_ptr<AAX_IParameter> param( new AAX_CParameter<bool>(
			cDefaultMasterBypassID, AAX_CString( "Master Bypass" ), false,
			AAX_CBinaryTaperDelegate<bool>(),
			AAX_CBinaryDisplayDelegate<bool>( "bypass", "on" ), true ) );
		param->SetNumberOfSteps( 2 );
		param->SetType( AAX_eParameterType_Discrete );
		mParameterManager.AddParameter( param.release() );
	}
	
	{
		std::unique_ptr<AAX_IParameter> param( new AAX_CParameter<bool>(
			DemoMIDI_HoldID, AAX_CString( "Hold" ), false,
			AAX_CBinaryTaperDelegate<bool>(),
			AAX_CBinaryDisplayDelegate<bool>( "off", "on" ), true ) );
		param->SetNumberOfSteps( 2 );
		param->SetType( AAX_eParameterType_Discrete );
		mParameterManager.AddParameter( param.release() );
	}
	
	{
		std::unique_ptr<AAX_IParameter> param( new AAX_CParameter<float>(
			DemoMIDI_GainID, AAX_CString( "Gain" ), 0.5f,
			AAX_CLinearTaperDelegate<float>( 0.0f, 1.0f ),
			AAX_CNumberDisplayDelegate<float>(), true ) );
		param->SetNumberOfSteps( 55 );
		mParameterManager.AddParameter( param.release() );
	}
	
	// register packets
	mPacketDispatcher.RegisterPacket( cDefaultMasterBypassID, eAlgPortID_BypassIn );
	mPacketDispatcher.RegisterPacket( DemoMIDI_GainID, eAlgPortID_CoefsGainIn );
	mPacketDispatcher.RegisterPacket( DemoMIDI_HoldID, eAlgPortID_HoldIn );
	
	return AAX_SUCCESS;
}


// *******************************************************************************
// METHOD:	ResetFieldData
// *******************************************************************************
AAX_Result DemoMIDI_Parameters::ResetFieldData( AAX_CFieldIndex inFieldIndex,
												void* oData,
												uint32_t inDataSize) const
{
	// Case for intialising private data
	if ( inFieldIndex == eAlgPortID_NoteData )
	{
		// This should never be true
		if ( inDataSize != sizeof( SDemoMIDI_NoteBits ) )
			return AAX_ERROR_INVALID_INTERNAL_DATA;
		//
		// Cast the pointer to an appropriate type
		SDemoMIDI_NoteBits * noteData = static_cast<SDemoMIDI_NoteBits *>( oData );
		//
		// Get the parameters
		const AAX_IParameter* bypassParam = mParameterManager.GetParameterByID( cDefaultMasterBypassID );
		const AAX_IParameter* holdParam   = mParameterManager.GetParameterByID( DemoMIDI_HoldID );
		//
		// Update the values based on parameters
		bypassParam->GetValueAsBool( &noteData->mBypassState );
		holdParam->GetValueAsBool( &noteData->mHoldState );
		//
		// Clean the rest of the data
		alg_utils::ClearNoteOnBits( noteData );
		alg_utils::ClearHeldNoteBits( noteData);
		//
		return AAX_SUCCESS;
	}
	//
	// Use the default implementation
	return this->AAX_CEffectParameters::ResetFieldData(inFieldIndex, oData, inDataSize);
}


// ***************************************************************************
// METHOD:	AAX_UpdateMIDINodes
// This will be called by the host if there are MIDI packets that need
// to be handled in the Data Model.
// ***************************************************************************
AAX_Result DemoMIDI_Parameters::UpdateMIDINodes( AAX_CFieldIndex inFieldIndex,	AAX_CMidiPacket& inPacket )
{
	AAX_Result result;
	
	// Do some MIDI work if necessary. There is no work to be
	// done in this simple example plug-in.
	if ( AAX::IsAllNotesOff( &inPacket ) )
	{
		// do all note off stuff...
	}
	else if ( AAX::IsNoteOff( &inPacket ) )
	{
		// do note off stuff...
	}
	else if ( AAX::IsNoteOn( &inPacket ) )
	{
		// do note on stuff...
	}
	
 	result = AAX_SUCCESS;
	
	return result;
}




