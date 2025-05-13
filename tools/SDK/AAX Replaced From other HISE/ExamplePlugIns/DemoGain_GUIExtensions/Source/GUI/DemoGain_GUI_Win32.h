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

/**  
 *	\file   DemoGain_GUI_Win32.h
 *
 *	\brief	DemoGain_GUI class definition.
 */ 
/*================================================================================================*/
#pragma once
#ifndef DEMOGAIN_GUI_WIN32_H
#define DEMOGAIN_GUI_WIN32_H

#include "AAX_CEffectGUI_Win32.h"

enum EEditAction
{
	eEditAction_EndEdit = 0,
	eEditAction_BeginOrContinueEdit
};

enum EMouseEventType
{
	eMouseEventType_MouseDown = 0,
	eMouseEventType_MouseDrag,
	eMouseEventType_MouseUp
};


//==============================================================================
class DemoGain_GUI : public AAX_CEffectGUI_Win32
{
public:
	static AAX_IEffectGUI *		AAX_CALLBACK Create ();

	DemoGain_GUI();
	virtual ~DemoGain_GUI();

public: ////////// AAX_CEffectGUI
	virtual AAX_Result			ParameterUpdated ( AAX_CParamID iParameterID );
	virtual	AAX_Result			TimerWakeup();

public: ////////// AAX_CEffectGUI_Win32
	virtual WORD				GetPlugInHWNDResourceID () const;
	virtual	void				InitPlugInHWNDContents ();
	
	virtual AAX_EEventResult	HandleKeyDown( HWND hwnd, WPARAM wParam );
	virtual AAX_EEventResult	DoMouseWindowProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
	virtual bool				HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam );
	virtual void				ForceParameterUpdateForHWND( HWND hwnd );
	
private: ////////// DemoGain_GUI
	void						UpdateParameterEditEvent (AAX_CParamID iParamID, EEditAction iAction);
	bool						HandleMouseEvent (EMouseEventType iEventType, const AAX_CParamID & iParamID, const WPARAM & iEventMods);
	uint32_t					GetAAXModifiersFromWin32MouseEvent (const WPARAM & wParam);

private: ////////// DemoGain_GUI
	HWND						mGainText;
	HWND						mGainSlider;
	HWND						mInputBar;
	HWND						mOutputBar;

	bool						mGainSliderIsEditing;
};

#endif
