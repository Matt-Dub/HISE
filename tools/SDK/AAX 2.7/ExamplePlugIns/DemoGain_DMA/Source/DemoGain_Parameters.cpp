/*================================================================================================*/
/*
 *	Copyright 2009-2015, 2023-2024 Avid Technology, Inc.
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
#include "DemoGain_AlgProc_ScatterGather.h"

#include "AAX_CBinaryTaperDelegate.h"
#include "AAX_CBinaryDisplayDelegate.h"
#include "AAX_CLinearTaperDelegate.h"
#include "AAX_CNumberDisplayDelegate.h"

#include "AAX_Assert.h"
#include "AAX_UtilsNative.h"


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
{
}

// *******************************************************************************
// METHOD:	~DemoGain_Parameters
// *******************************************************************************
DemoGain_Parameters::~DemoGain_Parameters ()
{
}

// *******************************************************************************
// METHOD:	EffectInit
// *******************************************************************************
AAX_Result DemoGain_Parameters::EffectInit()
{		
	// bypass
	AAX_CString bypassID = cDefaultMasterBypassID;
	AAX_IParameter * masterBypass = new AAX_CParameter<bool>(
		bypassID.CString(), AAX_CString("Master Bypass"), false,
		AAX_CBinaryTaperDelegate<bool>(),
		AAX_CBinaryDisplayDelegate<bool>("bypass", "on"), true);
	masterBypass->SetNumberOfSteps( 2 );
	masterBypass->SetType( AAX_eParameterType_Discrete );
	mParameterManager.AddParameter(masterBypass);
	
	// gain
	AAX_CParameter<float>* gainParameter = new AAX_CParameter<float>(
		DemoGain_GainID, AAX_CString("Gain"), 1.0f,
		AAX_CLinearTaperDelegate<float>(0.0f, 1.0f),
		AAX_CNumberDisplayDelegate<float>(), true);
	gainParameter->SetNumberOfSteps(55);
	mParameterManager.AddParameter(gainParameter);

	// register packets
	mPacketDispatcher.RegisterPacket(bypassID.CString(), eAlgPortID_BypassIn);
	mPacketDispatcher.RegisterPacket(DemoGain_GainID, eAlgPortID_CoefsGainIn, this, &DemoGain_Parameters::UpdatePacket_Gain);
	
	// Data verification (not quite a unit test...)
	//
	// Scatter/Gather
	AAX_ASSERT (IsPowerOfTwo(cDemoGain_DMASG_NumReadWritePoints));
	AAX_ASSERT (IsPowerOfTwo(cDemoGain_DMASG_GatherTransferLength));
	AAX_ASSERT (IsPowerOfTwo(cDemoGain_DMASG_ExternalBufferSize));
	AAX_ASSERT (IsPowerOfTwo(cDemoGain_DMASG_NumReadWritePoints));
	AAX_ASSERT (cDemoGain_DMA_MaxBufferLength > (1 << cDemoGain_DMA_TIBufferSizeProperty));
	AAX_ASSERT (cDemoGain_DMASG_GatherTransferLength > cDemoGain_DMASG_NumReadWritePoints);
	AAX_ASSERT (cDemoGain_DMASG_ExternalBufferSize > cDemoGain_DMASG_NumReadWritePoints);
	
	return AAX_SUCCESS;
}

// *******************************************************************************
// METHOD:	UpdatePacketGain
// *******************************************************************************
AAX_Result DemoGain_Parameters::UpdatePacket_Gain( AAX_CPacket& ioPacket )
{
	AAX_IParameter*	 parameter = mParameterManager.GetParameterByID( DemoGain_GainID );
	if (parameter)
	{
		float floatValue;
		if (parameter->GetValueAsFloat(&floatValue))
		{
			SDemoGain_DMA_CoefsGain&  packet = *ioPacket.GetPtr<SDemoGain_DMA_CoefsGain>();
			
			// Populate packet
			packet.mGain = floatValue;
		}
	}
	return AAX_SUCCESS;
}

// *******************************************************************************
// METHOD:	ResetFieldData
// *******************************************************************************
AAX_Result DemoGain_Parameters::ResetFieldData (AAX_CFieldIndex iFieldIndex, void * oData, uint32_t iDataSize) const
{
	// Call inherited to zero out values
	AAX_Result result = AAX_CEffectParameters::ResetFieldData (iFieldIndex, oData, iDataSize);
	
	const AAX_IController* controller = Controller();
	if (controller)
	{
		AAX_CString curEffectID = "";
		controller->GetEffectID(&curEffectID);
		
		// Scatter/Gather
		AAX_CString scatterGatherEffectID = kEffectID_DemoGain_DMASG;
		if (AAX::IsEffectIDEqual(&curEffectID, &scatterGatherEffectID))
		{
			if (iFieldIndex == eAlgFieldID_ScatterGather_DMALocalData)
			{
				SDemoGain_DMASG_DMALocalData* data = static_cast<SDemoGain_DMASG_DMALocalData*> (oData);
				data->mCurExternalWriteOffset = TransformOffset(cDemoGain_DMA_MaxBufferSize, cDemoGain_DMASG_ExternalBufferSegmentSize);
				for (uint32_t i = 0; i < cDemoGain_DMASG_NumReadWritePoints; i++)
				{
					data->mExtBufferOffsetTable[i] = i * cDemoGain_DMASG_ExternalBufferSegmentSize;
				}
				
#if DEMOGAIN_DMA_TEST_MODE
				AAX_ASSERT (IsPowerOfTwo(data->TestModeBufferLength));
				data->TestModeInitBlock ();
#endif
			}
		}
	}
	else
	{
		result = AAX_ERROR_NULL_COMPONENT;
	}

	return result;
}
