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

// Component includes
#include "DemoMIDI_Alg.h"
#include "DemoMIDI_Utils.h"

// AAX includes
#include "AAX.h"
#include "AAX_MIDIUtilities.h"

//==============================================================================
// SCoefficients methods definitions
//==============================================================================
bool SCoefficients::operator!=( const SCoefficients& inOther ) const
{
	return IsBypassDifferent( inOther ) || IsPassthroughDifferent( inOther ) || IsTransposeDifferent( inOther );
}

bool SCoefficients::IsBypassDifferent( const SCoefficients& inOther ) const
{
	return this->mBypass != inOther.mBypass;
}

bool SCoefficients::IsPassthroughDifferent( const SCoefficients& inOther ) const
{
	return this->mPassthrough != inOther.mPassthrough;
}

bool SCoefficients::IsTransposeDifferent( const SCoefficients& inOther ) const
{
	return this->mTransposeValue != inOther.mTransposeValue;
}


namespace
{
//==============================================================================
// FUNCTION: GetTransposedValue
// Returns the transposed note index
//==============================================================================
int8_t GetTransposedValue( const uint8_t noteIndex, const int32_t transposition )
{
	const int32_t tempValue = noteIndex + transposition;
	// Maximum value cannot be bigger that 127 and smaller than 0
	if ( tempValue <= cMaxMidiPitch && tempValue >= cMinMidiPitch )
	{
		return static_cast<uint8_t>( tempValue ); // This cast is safe because the value will aways be between 0 and 127
	}
	else if ( tempValue > cMaxMidiPitch )
	{
		return static_cast<uint8_t>(cMaxMidiPitch);
	}
	else
	{
		return static_cast<uint8_t>(cMinMidiPitch);
	}
}

//==============================================================================
// FUNCTION: PostEventToActiveNotes
// Posts a given event to all active notes
//==============================================================================
void PostEventToActiveNotes( const NoteDataSegment		( &noteDataArray )[cNumNoteSegments],
							 AAX_IMIDINode&				outMidiNode,
							 const AAX::EStatusNibble	noteEvent,
							 const int32_t				transposition )
{
	int segmentIndex = 0;
	// Iterate over data chunks
	for ( auto noteData : noteDataArray )
	{
		// Calculate the index of the first note in the segment
		int noteIndex = segmentIndex * cNumNotesPerSegment;
		// Each element of the array is a 32 bit integer, so we need to iterate over each bit
		while ( 0x0 != noteData )
		{
			// If the last bit is set, send the midi event for that note
			if ( ( noteData & 0x00000001 ) == 0x00000001 )
			{
				// Calculate the transposed note index if needed
				int tempIndex = noteIndex;
				if ( transposition != 0 )
				{
					tempIndex = GetTransposedValue( noteIndex, transposition );
				}
				// Configure the new outgoing MIDI packet
				AAX_CMidiPacket midiOutPacket;
				midiOutPacket.mTimestamp = 0;
				midiOutPacket.mLength = 3;
				midiOutPacket.mData[0] = noteEvent | 0x00;
				midiOutPacket.mData[1] = static_cast<unsigned char>( tempIndex );
				midiOutPacket.mData[2] = 0x00;
				midiOutPacket.mData[3] = 0x00;
				midiOutPacket.mIsImmediate = 1;
				// Post the MIDI packet
				outMidiNode.PostMIDIPacket( &midiOutPacket );
			}
			// Handle setup for next loop iteration
			noteData = noteData >> 1; // shift the bits to the right
			++noteIndex;
		}
		++segmentIndex;
	}
}

//==============================================================================
// FUNCTION: ProcessAudioPassthrough
//==============================================================================
void ProcessAudioPassthrough( const float* const* const	audioInput,
							  float* const* const		audioOutput,
							  const int32_t				numAudioChannels,
							  const int32_t				bufferMemSize )
{
	for ( int32_t channel = 0; channel < numAudioChannels; ++channel )
	{
		const float* const	AAX_RESTRICT inputChannel	= audioInput[channel];
		float* const		AAX_RESTRICT outputChannel	= audioOutput[channel];
		// Copy the input data to the output
		if ( inputChannel && outputChannel && *inputChannel != *outputChannel )
		{
			memcpy( outputChannel, inputChannel, bufferMemSize );
		}
	}
}

//==============================================================================
// FUNCTION: HandleBypassChanged
//==============================================================================
void HandleBypassChanged( const SCoefficients* const	coefs,
						  SPrivateData* const			privateData,
						  AAX_IMIDINode&				midiOutNode )
{
	if ( coefs->mBypass )
	{
		// Send note off to currently transposed notes
		PostEventToActiveNotes( privateData->mIsTransposed, midiOutNode, AAX::eStatusNibble_NoteOff, 0 );
		// Clear all of the persistent note data
		NMidiUtils::ClearNotesArray( privateData->mIsTransposed );
	}
	else if ( !coefs->mPassthrough && privateData->mCoefficients.mTransposeValue != 0 )
	{
		// Send note off to current notes
		PostEventToActiveNotes( privateData->mIsNoteOn, midiOutNode, AAX::eStatusNibble_NoteOff, 0 );
	}
}

//==============================================================================
// FUNCTION: HandlePassthroughChanged
//==============================================================================
void HandlePassthroughChanged( const SCoefficients* const	coefs,
							   SPrivateData* const			privateData,
							   AAX_IMIDINode&				midiOutNode )
{
	if ( coefs->mPassthrough )
	{
		// Send note on to notes that were held while passthrough was switched on
		PostEventToActiveNotes( privateData->mIsNoteOn, midiOutNode, AAX::eStatusNibble_NoteOn, 0 );
	}
	else
	{
		// Send note off to notes that were being passed through
		PostEventToActiveNotes( privateData->mIsNoteOn, midiOutNode, AAX::eStatusNibble_NoteOff, 0 );
	}
}

//==============================================================================
// FUNCTION: HandlePassthroughChanged
//==============================================================================
void HandleTransposeChanged( const SCoefficients* const	coefs,
							 SPrivateData* const		privateData,
							 AAX_IMIDINode&				midiOutNode )
{
	// Send note off to current notes
	if (privateData->mCoefficients.mTransposeValue == 0 && !coefs->mPassthrough)
	{
		PostEventToActiveNotes( privateData->mIsNoteOn, midiOutNode, AAX::eStatusNibble_NoteOff, 0 );
	}
	else
	{
		PostEventToActiveNotes( privateData->mIsTransposed, midiOutNode, AAX::eStatusNibble_NoteOff, 0 );
	}
	// Clear all of the persistent transposed note data
	NMidiUtils::ClearNotesArray( privateData->mIsTransposed );
	// Send new transposed note on events based on currently active notes
	PostEventToActiveNotes( privateData->mIsNoteOn, midiOutNode, AAX::eStatusNibble_NoteOn, coefs->mTransposeValue );
	// Don't update the transposed array if transpose is zero
	if ( coefs->mTransposeValue != 0 )
	{
		int segmentIndex = 0;
		// Iterate over data chunks
		for ( auto noteData : privateData->mIsNoteOn )
		{
			// Calculate the index of the first note in the segment
			int noteIndex = segmentIndex * cNumNotesPerSegment;
			// Each element of the array is a 32 bit integer, so we need to iterate over each bit
			while ( 0x0 != noteData )
			{
				// If the last bit is set, send the midi note off event for that note
				if ( ( noteData & 0x00000001 ) == 0x00000001 )
				{
					// Calculate data reaquired to update the transposed notes array
					const uint8_t  transposedIndex	= GetTransposedValue( noteIndex, coefs->mTransposeValue );
					const uint8_t  keySegment		= transposedIndex / cNumNotesPerSegment;
					const uint8_t  keyOffset		= transposedIndex % cNumNotesPerSegment;
					const uint32_t keyOffsetBits	= ( 0x01 << keyOffset );
					// Update the array
					privateData->mIsTransposed[keySegment] |= keyOffsetBits;
				}
				// Handle setup for next loop iteration
				noteData = noteData >> 1; // shift the bits to the right
				++noteIndex;
			}
			++segmentIndex;
		}
	}
}
} // namespace


//==============================================================================
// Processing function definition
//==============================================================================
void AAX_CALLBACK DemoMIDI_AlgorithmProcessFunction( SDemoMIDI_Alg_Context * const inInstancesBegin [],
													 const void *				   inInstancesEnd )
{
	// Get a pointer to the beginning of the memory block table
	SDemoMIDI_Alg_Context* AAX_RESTRICT instance = inInstancesBegin [0];
	//
	//--------- Iterate over plug-in instances ---------//
	//
	for ( SDemoMIDI_Alg_Context * const * walk = inInstancesBegin; walk < inInstancesEnd; ++walk )
	{
		instance = *walk;
		
		//--------- Retrieve general instance-specific information ---------//
		//
		// Memory blocks
		const SCoefficients* const		coefs					= instance->mpCoefficients;
		const int32_t					bufferSize				= *instance->mpBufferSize;
		SPrivateData* const				privateData				= instance->mpPrivateData;
		//
		// Setup MIDI In node pointers
		AAX_IMIDINode* const			midiInNode				= instance->mpMIDINodeIn;
		const AAX_CMidiStream* const	midiInStream			= midiInNode->GetNodeBuffer();
		const AAX_CMidiPacket*			midiInPacketPtr			= midiInStream->mBuffer;
		uint32_t						inputPacketsRemaining	= midiInStream->mBufferSize;
		//
		// Setup MIDI Out node pointers
		AAX_IMIDINode* const			midiOutNode				= instance->mpMIDINodeOut;
		
		//--------- Process audio signal ---------//
		//
		{
			// Retrieve instance-specific audio related information //
			const float* const* const	audioInput			= instance->mppInput;
			float* const* const			audioOutput			= instance->mppOutput;
			const int32_t				numAudioChannels	= *instance->mpNumAudioChannels;
			//
			// Calculate the buffer memory size
			const int32_t 				bufferMemSize	= sizeof( float ) * bufferSize;
			//
			// Perfrom the audio passthrough
			ProcessAudioPassthrough( audioInput, audioOutput, numAudioChannels, bufferMemSize );
		}
		
		
		//--------- Handle parameter changes ---------//
		//
		// Perform MIDI processing only if the MIDI output node is a valid object
		if ( NULL != midiOutNode )
		{
			// Handle bypass changes
			if ( coefs->IsBypassDifferent( privateData->mCoefficients ) )
			{
				HandleBypassChanged(coefs, privateData, *midiOutNode);
			}
			//
			// Handle passthrough changes
			if ( coefs->IsPassthroughDifferent( privateData->mCoefficients ) && !coefs->mBypass)
			{
				HandlePassthroughChanged(coefs, privateData, *midiOutNode);
			}
			//
			// Handle transposition changes
			if ( coefs->IsTransposeDifferent( privateData->mCoefficients ) && !coefs->mBypass)
			{
				HandleTransposeChanged(coefs, privateData, *midiOutNode);
			}
			//
			//--------- Process MIDI messages ---------//
			//
			// Run processing loop over the audio buffer size
			for ( int32_t t = 0; t < bufferSize; ++t )
			{
				// Iterate over the input packets
				while ( ( 0 < inputPacketsRemaining ) && ( NULL != midiInPacketPtr ) && ( midiInPacketPtr->mTimestamp <= t ) )
				{
					// Handle the MIDI packet processing
					const uint8_t	dataChunk		= midiInPacketPtr->mData[1];
					const uint8_t	keySegment		= dataChunk / cNumNotesPerSegment; // (intentional int division) Segment in SPrivateData
					const uint8_t	keyOffset		= dataChunk % cNumNotesPerSegment; // Offset in SPrivateData
					const bool		isNoteOn		= AAX::IsNoteOn( midiInPacketPtr );
					const bool		isNoteOff		= AAX::IsNoteOff( midiInPacketPtr );
					const bool		isAllNotesOff	= AAX::IsAllNotesOff( midiInPacketPtr );
					//
					// Transpose only when the value the event is either note on or off, plugin is not bypassed and transpose is non-zero
					if ( !coefs->mBypass && coefs->mTransposeValue != 0 && ( isNoteOn || isNoteOff ) )
					{
						// New outgoing packet
						AAX_CMidiPacket midiOutPacket;
						// Temporary variable to store the result of transposition calculations
						const uint8_t firstDataChunk = GetTransposedValue( dataChunk, coefs->mTransposeValue );
						// Copy the input packet to manipulate it
						memcpy( &midiOutPacket, midiInPacketPtr, sizeof( AAX_CMidiPacket ) );
						// Write the calculated data to the outgoing packet
						midiOutPacket.mData[1] = firstDataChunk;
						// Post the MIDI packet
						midiOutNode->PostMIDIPacket( &midiOutPacket );
						// Update the private data information about transposed notes
						const uint8_t newKeySegment = firstDataChunk / cNumNotesPerSegment; // (intentional int division) Segment in SPrivateData
						const uint8_t newKeyOffset  = firstDataChunk % cNumNotesPerSegment; // Offset in SPrivateData
						// Update the transposed notes array
						if ( isNoteOn )
						{
							const uint32_t keyOffsetBits = ( 0x01 << newKeyOffset );
							privateData->mIsTransposed[newKeySegment] |= keyOffsetBits;
						}
						else
						{
							const uint32_t mask = ~( 0x01 << newKeyOffset );
							privateData->mIsTransposed[newKeySegment] &= mask;
						}
					}
					// Update the array to accurately represent the state of current incoming events
					if ( isNoteOn )
					{
						// Update the note on array
						const uint32_t keyOffsetBits = ( 0x01 << keyOffset );
						privateData->mIsNoteOn[keySegment] |= keyOffsetBits;
					}
					else if ( isNoteOff )
					{
						// Update the note on array
						const uint32_t mask = ~( 0x01 << keyOffset );
						privateData->mIsNoteOn[keySegment] &= mask;
					}
					else if ( isAllNotesOff )
					{
						NMidiUtils::ClearNotesArray( privateData->mIsNoteOn );
						NMidiUtils::ClearNotesArray( privateData->mIsTransposed );
					}
					// Perform MIDI packet passthrough
					if ( coefs->mPassthrough || coefs->mBypass || isAllNotesOff || coefs->mTransposeValue == 0)
					{
						// New outgoing MIDI packet
						AAX_CMidiPacket midiOutPacket;
						// Copy the packet from the input MIDI node to the output MIDI node
						memcpy( &midiOutPacket, midiInPacketPtr, sizeof( AAX_CMidiPacket ) );
						// Post the MIDI packet
						midiOutNode->PostMIDIPacket( &midiOutPacket );
					}
					//
					// Increment to the next MIDI packet
					++midiInPacketPtr;
					--inputPacketsRemaining;
				}
			}
		}
		//
		// Update the instance persistant data for paramater changes
		if ( *coefs != privateData->mCoefficients )
		{
			memcpy( &privateData->mCoefficients, coefs, sizeof( SCoefficients ) );
		}
	} // End instance-iteration loop
}
