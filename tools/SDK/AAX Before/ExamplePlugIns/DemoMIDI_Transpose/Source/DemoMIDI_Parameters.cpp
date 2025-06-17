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
#include "DemoMIDI_Parameters.h"
#include "DemoMIDI_Defs.h"
#include "DemoMIDI_Alg.h"
#include "DemoMIDI_Utils.h"

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
DemoMIDI_Parameters::DemoMIDI_Parameters() :
AAX_CEffectParameters()
{
}

// *******************************************************************************
// METHOD:	EffectInit
// *******************************************************************************
AAX_Result DemoMIDI_Parameters::EffectInit()
{	
	// Add parameters
	//
	// Add the bypass parameter
	{
		std::unique_ptr<AAX_IParameter> param( new AAX_CParameter<bool>(
			cDefaultMasterBypassID, AAX_CString( "Master Bypass" ), false,
			AAX_CBinaryTaperDelegate<bool>(),
			AAX_CBinaryDisplayDelegate<bool>( "bypass", "on" ), true ) );
		param->SetNumberOfSteps( 2 );
		param->SetType( AAX_eParameterType_Discrete );
		mParameterManager.AddParameter( param.release() );
	}
	// Add the passthrough parameter
	{
		std::unique_ptr<AAX_IParameter>param( new AAX_CParameter<bool>(
			cDemoMIDI_PassthroughID, AAX_CString( "Passthrough" ), false,
			AAX_CBinaryTaperDelegate<bool>(),
			AAX_CBinaryDisplayDelegate<bool>( "off", "on" ), true ) );
		param->SetNumberOfSteps( 2 );
		param->SetType( AAX_eParameterType_Discrete );
		mParameterManager.AddParameter( param.release() );
	}
	// Add the parameter for the transposition value
	{
		std::unique_ptr<AAX_IParameter>param( new AAX_CParameter<int32_t>(
			cDemoMIDI_TransposeID, AAX_CString( "Transposition" ), cTransposeDefaultVal,
			AAX_CLinearTaperDelegate<int32_t>( cTransposeMinVal, cTransposeMaxVal ),
			AAX_CNumberDisplayDelegate<int32_t>(), true ) );
		param->SetNumberOfSteps( cTransposeSteps );
		mParameterManager.AddParameter( param.release() );
	}
	//
	// Don't register the packets, GenerateCoefficients() will take care of updating the values
	
	return AAX_SUCCESS;
}


// *******************************************************************************
// METHOD:	GenerateCoefficients
// *******************************************************************************
AAX_Result DemoMIDI_Parameters::GenerateCoefficients()
{
	SCoefficients coefficients;
	
	const AAX_IParameter* bypassParam		= mParameterManager.GetParameterByID( cDefaultMasterBypassID );
	const AAX_IParameter* passthruParam		= mParameterManager.GetParameterByID( cDemoMIDI_PassthroughID );
	const AAX_IParameter* transposeParam	= mParameterManager.GetParameterByID( cDemoMIDI_TransposeID );
	
	bypassParam->GetValueAsBool( &coefficients.mBypass );
	passthruParam->GetValueAsBool( &coefficients.mPassthrough );
	transposeParam->GetValueAsInt32( &coefficients.mTransposeValue );
	
	const AAX_Result result = Controller()->PostPacket( eAlgPortID_Coefficients,
														&coefficients,
														sizeof( coefficients ) );

	return result;
}


// *******************************************************************************
// METHOD:	ResetFieldData
// *******************************************************************************
AAX_Result DemoMIDI_Parameters::ResetFieldData( AAX_CFieldIndex inFieldIndex,
												void* oData,
												uint32_t inDataSize) const
{
	// Case for establishing the number of audio channels
	if ( inFieldIndex == eAlgPortID_NumAudioChannels )
	{
		// This should never be true
		if ( inDataSize != sizeof( int32_t ) )
			return AAX_ERROR_INVALID_INTERNAL_DATA;
		//
		// Cast the pointer to an appropriate type
		int32_t * dataIntPtr = static_cast<int32_t *>( oData );
		//
		// Retrieve the stem format information
		AAX_EStemFormat inStemFormat;
		AAX_EStemFormat outStemFormat;
		//
		Controller()->GetInputStemFormat( &inStemFormat );
		Controller()->GetInputStemFormat( &outStemFormat );
		//
		// This should never be true as well
		if ( inStemFormat != outStemFormat )
			return AAX_ERROR_INVALID_INTERNAL_DATA;
		//
		// Assign the newly calculated channel count
		*dataIntPtr = AAX_GetStemFormatChannelCount( inStemFormat );
		//
		return AAX_SUCCESS;
	}
	//
	// Case for intialising private data
	if ( inFieldIndex == eAlgPortID_PrivateData )
	{
		// This should never be true
		if ( inDataSize != sizeof( SPrivateData ) )
			return AAX_ERROR_INVALID_INTERNAL_DATA;
		//
		// Cast the pointer to an appropriate type
		SPrivateData * privDataPtr = static_cast<SPrivateData *>( oData );
		//
		// Get the parameters
		const AAX_IParameter* bypassParam		= mParameterManager.GetParameterByID( cDefaultMasterBypassID );
		const AAX_IParameter* passthruParam		= mParameterManager.GetParameterByID( cDemoMIDI_PassthroughID );
		const AAX_IParameter* transposeParam	= mParameterManager.GetParameterByID( cDemoMIDI_TransposeID );
		//
		// Update the values
		bypassParam->GetValueAsBool( &privDataPtr->mCoefficients.mBypass );
		passthruParam->GetValueAsBool( &privDataPtr->mCoefficients.mPassthrough );
		transposeParam->GetValueAsInt32( &privDataPtr->mCoefficients.mTransposeValue );
		//
		// Clear rest of the data
		NMidiUtils::ClearNotesArray( privDataPtr->mIsNoteOn );
		NMidiUtils::ClearNotesArray( privDataPtr->mIsTransposed );
		//
		return AAX_SUCCESS;
	}
	//
	// Use the default implementation
	return this->AAX_CEffectParameters::ResetFieldData(inFieldIndex, oData, inDataSize);
}
