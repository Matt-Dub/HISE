/*================================================================================================*/
/*
 *	Copyright 2013-2017, 2019, 2021, 2023-2024 Avid Technology, Inc.
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

// AAX includes
#include "AAX.h"
#include "AAX_MIDIUtilities.h"

// Standard includes
#include <math.h>		// for fabsf(), sinf()
#include <algorithm>	// for max()


//==============================================================================
// Processing function definition
//==============================================================================

template<int kNumChannelsIn, int kNumChannelsOut> 
void
AAX_CALLBACK
DemoMIDI_AlgorithmProcessFunction( SDemoMIDI_Alg_Context * const inInstancesBegin [],
								   const void *					 inInstancesEnd )
{
	// Get a pointer to the beginning of the memory block table
	SDemoMIDI_Alg_Context* AAX_RESTRICT instance = inInstancesBegin [0];
	
	
	//--------- Iterate over plug-in instances ---------//
	//
	for (SDemoMIDI_Alg_Context * const * walk = inInstancesBegin; walk < inInstancesEnd; ++walk)
	{
		instance = *walk;
		
		//--------- Retrieve instance-specific information ---------//
		//
		// Memory blocks
		const int32_t		bufferSize	= *instance->mBufferSizeP;
		const bool		  bypass		= (*instance->mCtrlBypassP != alg_utils::cStateFalse);
		const float			gain		= *instance->mGainP;
		const bool			holdNotes	= (*instance->mCtrlHoldP != alg_utils::cStateFalse);
		float*				meterTaps	= *instance->mMetersPP;
		SDemoMIDI_NoteBits* const notes	= instance->mNoteData;
		//
		// Setup MIDI In node pointers 
		AAX_IMIDINode* midiInNode = instance->mMIDINodeInP;
		const AAX_CMidiStream* midiInStream = midiInNode->GetNodeBuffer();
		const AAX_CMidiPacket* midiInPacketPtr = midiInStream->mBuffer;
		uint32_t inputPacketsRemaining = midiInStream->mBufferSize;
		//
		// Setup MIDI Out node pointers
		AAX_IMIDINode* const midiOutPassThroughNode = instance->mMIDINodeOutPassThroughP;
		//
		const bool holdChanged = ( holdNotes != notes->mHoldState );
		const bool bypassChanged = ( bypass != notes->mBypassState );
		
		//--------- Handle paramater changes ---------//
		//
		// Example of MIDI output: send a note off message to held notes if hold was just turned off or 
		// if bypass was just engaged
		if ( ( holdChanged && !holdNotes ) || ( bypassChanged && bypass ) )
		{	
			// local variable used to easily determine which note should recieve a note off
			int noteIndex = 0;
			
			for ( uint32_t heldNotesBits : notes->mIsHeld )
			{
				// if no notes are held in this segment, skip to the next segment
				if ( heldNotesBits == 0x00000000 )
				{
					noteIndex += alg_utils::cNumNotesPerSegment;
					continue;
				}

				// each element of the array is a 32 bit integer, so we need to iterate over each bit
				for ( int i = 0; i < alg_utils::cNumNotesPerSegment; ++i )
				{
					// if the last bit is set, send the midi note off event for that note
					if ( ( heldNotesBits & 0x00000001 ) == 0x00000001 )
					{
						AAX_CMidiPacket midiOutPacket;
						midiOutPacket.mTimestamp = 0;
						midiOutPacket.mLength = 3;
						midiOutPacket.mData[0] = AAX::eStatusNibble_NoteOff | 0x00;
						midiOutPacket.mData[1] = ( unsigned char ) noteIndex;
						midiOutPacket.mData[2] = 0x00;
						midiOutPacket.mData[3] = 0x00;
						midiOutPacket.mIsImmediate = 1;
															
						// post the MIDI packet
						midiOutPassThroughNode->PostMIDIPacket( &midiOutPacket ) ;
					}
					
					heldNotesBits = heldNotesBits >> 1; // shift the bits to the right
					++noteIndex; // increase the noteIndex
				}
			}

			// Clear the arrays that hold information about held state and note on state
			alg_utils::ClearNoteOnBits( notes );
			alg_utils::ClearHeldNoteBits( notes );
		}

		
		//--------- Run processing loop over each channel ---------//
		//
		for ( int ch = 0; ch < kNumChannelsIn; ch++ )
		{
			//--------- Run processing loop over each sample ---------//
			//
			for ( int32_t t = 0; t < bufferSize; t++ )
			{
				// Set up audio sample pointers
				//
				// Audio channels
				float* const AAX_RESTRICT pdI = instance->mInputPP [0]; // First channel
				float* const AAX_RESTRICT pdO = instance->mOutputPP [0]; // First channel
				
				while ( ( 0 < inputPacketsRemaining ) &&
						( NULL != midiInPacketPtr ) &&
						( midiInPacketPtr->mTimestamp <= t ) )
				{
					bool passPacket = false;
					
					// Handle the MIDI packet
					//
					// Switch note-is-on bit flags on or off in the SDemoMIDI_NoteBits bit
					// array as note on and note off messages are received.
					{
						const uint8_t data1 = midiInPacketPtr->mData[1];
						const uint8_t keySegment = data1/32; // (intentional int division) Segment in SDemoMIDI_NoteBits
						const uint8_t keyOffset = data1 % 32; // Offset in SDemoMIDI_NoteBits
						
						if ( AAX::IsNoteOff( midiInPacketPtr ) )
						{
							// only send note off events if notes are not held
							if ( !holdNotes || bypass )
							{
								passPacket = true;
								const uint32_t mask = ~( 0x01 << keyOffset );
								notes->mIsOn[keySegment] &= mask;
							}
							// if a note off event was discarded, register that note as held (for bypass)
							else
							{
								const uint32_t mask = ( 0x01 << keyOffset );
								notes->mIsHeld[keySegment] |= mask;
							}
						}
						else if ( AAX::IsNoteOn( midiInPacketPtr ) )
						{
							passPacket = true;
							const uint32_t mask = ( 0x01 << keyOffset );
							notes->mIsOn[keySegment] |= mask;

							// if a held note receives a note on event, send a note off event for that note
							// otherwise the subsequent note will be held indefinitely
							if ( notes->mIsHeld[keySegment] & mask )
							{
								AAX_CMidiPacket midiOutPacket;
								midiOutPacket.mTimestamp = 0;
								midiOutPacket.mLength = 3;
								midiOutPacket.mData[0] = AAX::eStatusNibble_NoteOff | 0x00;
								midiOutPacket.mData[1] = data1;
								midiOutPacket.mData[2] = 0x00;
								midiOutPacket.mData[3] = 0x00;
								midiOutPacket.mIsImmediate = 1;
								
								// post the MIDI packet
								if ( NULL != midiOutPassThroughNode )
									midiOutPassThroughNode->PostMIDIPacket( &midiOutPacket );
							}
						}
						else if ( AAX::IsAllNotesOff( midiInPacketPtr ) )
						{
							// pass an all notes off event even if notes are held
							passPacket = true;
							alg_utils::ClearNoteOnBits( notes );
						}
					}
					
					// Example of MIDI output: perform MIDI packet pass-through
					if ( NULL != midiOutPassThroughNode && true == passPacket )
					{
						AAX_CMidiPacket midiOutPacket;
						
						// Copy the packet from the input MIDI node to the output MIDI node
						memcpy( &midiOutPacket, midiInPacketPtr, sizeof ( AAX_CMidiPacket ) );
						
						// Post the MIDI packet
						midiOutPassThroughNode->PostMIDIPacket( &midiOutPacket );
					}
					
					// Increment to the next MIDI packet
					++midiInPacketPtr;
					--inputPacketsRemaining;
				}
				
				// Process Audio Samples
				const bool anyNoteIsOn = 0x00 != ( notes->mIsOn[0] | notes->mIsOn[1] | notes->mIsOn[2] | notes->mIsOn[3] );
				if ( anyNoteIsOn )
				{
					pdO[t] = 1.0f * gain;
				}
				else
				{
					pdO[t] = 0.0f;
				}
				
				// Handle bypass for audio signal
				if ( bypass )
				{
					pdO[t] = pdI[t];
				}
				
				// Do metering
				//
				// Accumulate the max value for metering. This will get cleared for us by the shell
				// when it sends the accumulated value up to the host.
				meterTaps[eMeterTap_PreGain] = std::max( fabsf( instance->mInputPP [0] [t] ), meterTaps[eMeterTap_PreGain] );
				meterTaps[eMeterTap_PostGain] = std::max( fabsf( instance->mOutputPP [0] [t] ), meterTaps[eMeterTap_PostGain] );
				
			} // Go to the next sample
		} // Go to next channel
		
		// Update persistent states
		notes->mHoldState = holdNotes;
		notes->mBypassState = bypass;
		
	} // End instance-iteration loop
}
