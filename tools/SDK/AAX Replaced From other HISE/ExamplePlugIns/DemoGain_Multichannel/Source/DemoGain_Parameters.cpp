/*================================================================================================*/
/*
 *	Copyright 2009-2016, 2018, 2023-2024 Avid Technology, Inc.
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

#include "DemoGain_Parameters.h"
#include "DemoGain_Defs.h"
#include "DemoGain_Alg.h"

#include "AAX_CBinaryTaperDelegate.h"
#include "AAX_CBinaryDisplayDelegate.h"
#include "AAX_CLinearTaperDelegate.h"
#include "AAX_CNumberDisplayDelegate.h"

#include "AAX_StringUtilities.h"
#include "AAX_Assert.h"



// *******************************************************************************
// ROUTINE:	Create
// *******************************************************************************
AAX_CEffectParameters *AAX_CALLBACK DemoGain_Parameters::Create()
{
	return new DemoGain_Parameters();
}

// *******************************************************************************
// METHOD:	DemoGain_Parameters
// *******************************************************************************
DemoGain_Parameters::DemoGain_Parameters () :
	AAX_CEffectParameters()
	, mNumChannels(0)
{
}

// *******************************************************************************
// METHOD:	EffectInit
// *******************************************************************************
AAX_Result DemoGain_Parameters::EffectInit()
{	
	AAX_EStemFormat stemFormatInput;
    Controller()->GetInputStemFormat(&stemFormatInput);
    mNumChannels = AAX_STEM_FORMAT_CHANNEL_COUNT(stemFormatInput);
	
	//
	// Register parameters
	//
	
	// bypass
	{
		AAX_CString bypassID = cDefaultMasterBypassID;
		AAX_IParameter * masterBypass = new AAX_CParameter<bool>(
			bypassID.CString(), AAX_CString("Master Bypass"), false,
			AAX_CBinaryTaperDelegate<bool>(),
			AAX_CBinaryDisplayDelegate<bool>("bypass", "on"), true);
		masterBypass->SetNumberOfSteps( 2 );
		masterBypass->SetType( AAX_eParameterType_Discrete );
		mParameterManager.AddParameter(masterBypass);
		
		mPacketDispatcher.RegisterPacket(bypassID.CString(), eAlgPortID_BypassIn);
	}
    
	// gain
	{
		AAX_CParameter<float>* gainParameter = nullptr;
		for (uint16_t channelIndex = 0 ; (channelIndex < mNumChannels) && (channelIndex < cMaxNumChannels); ++channelIndex )
		{
			const char * parameterID = cDemoGain_GainIDs[channelIndex];
			const AAX_CString parameterName("Gain " + AAX::AsStringStemChannel(stemFormatInput, channelIndex, true));
			gainParameter = new AAX_CParameter<float>(parameterID,
													  parameterName,
													  1.0f,
													  AAX_CLinearTaperDelegate<float>(0.0f, 1.0f),
													  AAX_CNumberDisplayDelegate<float>(), true);
			gainParameter->SetNumberOfSteps(55);
			mParameterManager.AddParameter(gainParameter);
			
			mPacketDispatcher.RegisterPacket(parameterID, eAlgPortID_CoefsGainIn, this, &DemoGain_Parameters::UpdatePacket_Gain);
		}
	}

	return AAX_SUCCESS;
}

// *******************************************************************************
// METHOD:	UpdatePacketGain
// *******************************************************************************
AAX_Result DemoGain_Parameters::UpdatePacket_Gain( AAX_CPacket& ioPacket )
{
	AAX_Result result = AAX_SUCCESS;
	SDemoGain_CoefsGain* packet = ioPacket.GetPtr<SDemoGain_CoefsGain>();
	if (packet)
	{
		// Populate the packet
		for (uint16_t i = 0; (i < mNumChannels) && (i < cMaxNumChannels); ++i)
		{
			const char * parameterID = cDemoGain_GainIDs[i];
			AAX_IParameter* const parameter = mParameterManager.GetParameterByID(parameterID);
			AAX_ASSERT(parameter);
			
			float floatValue;
			if (parameter && parameter->GetValueAsFloat(&floatValue))
			{
				packet->mGain[i] = floatValue;
			}
			else
			{
				packet->mGain[i] = 0.f;
				result = AAX_ERROR_INVALID_PARAMETER_INDEX;
			}
		}
	}
	else
	{
		result = AAX_ERROR_NULL_OBJECT;
	}

	return result;
}
