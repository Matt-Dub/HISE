/*================================================================================================*/
/*
 *	Copyright 2010-2015, 2017, 2019, 2023-2024 Avid Technology, Inc.
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

/**  
 *	\file   RectiFi_EffectParameters.h
 *
 *	\brief  RectiFi_EffectParameters class declaration.
 *
 */ 
/*================================================================================================*/ 

#ifndef RECTIFI_EFFECTPARAMETERS_H
#define RECTIFI_EFFECTPARAMETERS_H

#include "AAX_CEffectParameters.h"


#include AAX_ALIGN_FILE_BEGIN
#include AAX_ALIGN_FILE_HOST
#include AAX_ALIGN_FILE_END
	struct SCompleteRectiFiChunk
	{
		int32_t					fPreFilter;
		int32_t					fRectiType;
		int32_t					fEffectLevel;
		int32_t					fPostFilter;
		int32_t					fEffectMix;
	};
#include AAX_ALIGN_FILE_BEGIN
#include AAX_ALIGN_FILE_RESET
#include AAX_ALIGN_FILE_END


// *******************************************************************************
// CLASS:	RectiFi_EffectParameters
// *******************************************************************************
class RectiFi_EffectParameters : public AAX_CEffectParameters
{
public:
	//Constructor
	RectiFi_EffectParameters ();
	
	static AAX_CEffectParameters *AAX_CALLBACK Create();
	//Overrides from AAX_CEffectParameters
	AAX_Result			EffectInit();

protected:
	AAX_Result	PreFilt_ProcessFunction(  AAX_CPacket& ioPacket );
	AAX_Result	PostFilt_ProcessFunction( AAX_CPacket& ioPacket );
	AAX_Result	Gain_ProcessFunction( AAX_CPacket& ioPacket );
	AAX_Result	Mix_ProcessFunction( AAX_CPacket& ioPacket );
private:
	AAX_Result SetChunk( AAX_CTypeID chunkID, const AAX_SPlugInChunk * chunk);
	void       ByteSwapChunk(SCompleteRectiFiChunk* out, const SCompleteRectiFiChunk* in) const;
	AAX_Result CompareActiveChunk( const AAX_SPlugInChunk * aChunkP, AAX_CBoolean * aIsEqualP ) const;
	AAX_Result GetNumberOfChunks ( int32_t * numChunks ) const;
	AAX_Result GetChunkIDFromIndex ( int32_t index, AAX_CTypeID * chunkID ) const;
	AAX_Result GetChunkSize ( AAX_CTypeID chunkID, uint32_t * size ) const;
	AAX_Result GetChunk ( AAX_CTypeID chunkID, AAX_SPlugInChunk * chunk ) const;
	int32_t    GetChunkValueForParameter(const char* identifier) const;
	AAX_Result ResetFieldData (AAX_CFieldIndex inFieldIndex, void * inData, uint32_t inDataSize) const;

private:	
	AAX_CSampleRate sampleRateContr;
    AAX_CParameter<double> * mParameterGain;
    AAX_CParameter<int32_t> * mParameterRectification;
};


#endif
