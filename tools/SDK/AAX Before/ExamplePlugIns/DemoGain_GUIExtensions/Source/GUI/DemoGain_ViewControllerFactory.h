/*================================================================================================*/
/*
 *	Copyright 2011-2015, 2023-2024 Avid Technology, Inc.
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
 *	\file   DemoGain_ViewControllerFactory.h
 *
 *	\brief  DemoGain_ViewControllerFactory class definition
 *
 *  \author David Hearst
 */ 
/*================================================================================================*/
class AAX_IEffectParameters;
class AAX_IController;
class AAX_IViewContainer;

@interface DemoGain_ViewControllerFactory : NSObject
{
}

- (NSViewController*)viewControllerFromBundle:(NSBundle*)bundle effectParameters:(AAX_IEffectParameters*)effectParameters
																controller:(AAX_IController*)controller;

@end
