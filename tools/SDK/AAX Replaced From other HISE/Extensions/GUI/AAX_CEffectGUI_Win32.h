/*================================================================================================*/
/*
 *	Copyright 2010-2015, 2023-2024 Avid Technology, Inc.
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
 *  \file AAX_CEffectGUI_Win32.h
 *
 */
/*================================================================================================*/

#ifndef AAX_CEFFECTGUI_WIN32_H
#define AAX_CEFFECTGUI_WIN32_H

#include "AAX_CEffectGUI.h"

#include <string>
#include <vector>
#include <windows.h>

enum AAX_EEventResult
{
	AAX_eEventResult_PassEventToSystem = 0,
	AAX_eEventResult_PassEventToClient,
	AAX_eEventResult_DoNotPassEvent,
	AAX_eEventResult_ClearFocus,
	AAX_eEventResult_CancelFocus,
};

/** @brief	Implementation of the AAX_IEffectGUI interface that provides a native window to the effect.
*
*	AAX_CEffectGUI_Win32 adapts the AAX_IEffectGUI in order to provide a native window. 
*/
class AAX_CEffectGUI_Win32 : public AAX_CEffectGUI
{
public:
	AAX_CEffectGUI_Win32();
	virtual ~AAX_CEffectGUI_Win32();

protected:
	virtual void			CreateViewContents ();
	virtual void			CreateViewContainer ();
	virtual void			DeleteViewContainer ();
	virtual AAX_Result		GetViewSize ( AAX_Point * oViewSize ) const;

public:
	static	void			SetInstance( HINSTANCE iInstance ) { sInstance = iInstance; }
	static	HINSTANCE		GetInstance() { return sInstance; }
	HWND					GetParentHWND() { return mHWND; }	

protected:
	/** @brief Override this method to return the plug-in HWND resource ID
	 */
	virtual WORD			GetPlugInHWNDResourceID () const = 0;

	/** @brief Override this method to initialize the contents of the plug-in HWND

		Called after the plug-in HWND has been created
	 */
	virtual	void			InitPlugInHWNDContents () = 0;

	virtual AAX_EEventResult	HandleKeyDown( HWND hwnd, WPARAM wParam ) = 0;
	virtual AAX_EEventResult	DoTextWindowProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
	virtual AAX_EEventResult	DoMouseWindowProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
	virtual bool				HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam ) = 0;
	virtual void				ForceParameterUpdateForHWND( HWND hwnd ) = 0;

protected:
	void					SetPlugInHWND( HWND iPlugInHWND ) { mPlugInHWND = iPlugInHWND; }
	HWND					GetPlugInHWND () const { return mPlugInHWND; }
	void					SetupForKeyboardInput ( HWND iEditText );
	void					SetupForMouseInput ( HWND iWindow );

protected:
	static INT_PTR CALLBACK AAX_CEffectGUI_Win32::DialogProc( __in  HWND hwnd, __in  UINT uMsg, __in  WPARAM wParam, __in  LPARAM lParam );
	static LRESULT CALLBACK	TextWindowProc( __in HWND hwnd, __in UINT uMsg, __in WPARAM wParam, __in LPARAM lParam );
	static LRESULT CALLBACK	MouseInputWindowProc( __in HWND hwnd, __in UINT uMsg, __in WPARAM wParam, __in LPARAM lParam );

private:
	HWND					CreatePlugInHWND ( WORD iResourceID );
	void					SetParentHWND( HWND iParentHWND ) { mHWND = iParentHWND; }

private:
	static	HINSTANCE		sInstance;
	HWND					mHWND;	
	HWND					mPlugInHWND;		
	AAX_EEventResult		mLastTextResult;
};

#endif //AAX_CEffectGUI_Win32_H
