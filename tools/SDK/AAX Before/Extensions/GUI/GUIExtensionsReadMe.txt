=============================================

AAX SDK GUI Extensions projects

Copyright 2023-2024 Avid Technology, Inc.
All rights reserved.

This file is part of the Avid AAX SDK.

The AAX SDK is subject to commercial or open-source licensing.

By using the AAX SDK, you agree to the terms of both the Avid AAX SDK License
Agreement and Avid Privacy Policy.

AAX SDK License: https://developer.avid.com/aax
Privacy Policy: https://www.avid.com/legal/privacy-policy-statement

Or: You may also use this code under the terms of the GPL v3 (see
www.gnu.org/licenses).

THE AAX SDK IS PROVIDED "AS IS" WITHOUT ANY WARRANTY, AND ALL WARRANTIES, WHETHER
EXPRESSED OR IMPLIED, INCLUDING MERCHANTABILITY AND FITNESS FOR PURPOSE, ARE
DISCLAIMED.

=============================================

These projects demonstrate how to extend the AAX SDK's GUI programming
interface using a variety of popular GUI frameworks:

* Native Cocoa
* Native Win32
* VSTGUI
* JUCE

These projects do not represent core functionality of the AAX SDK, but rather
they serve as examples of how plug-in GUIs can be written to the AAX
specification using a variety of different approaches.

-------------
Project Notes
-------------

* The VST and JUCE GUI Extension library projects use a macro value to resolve 
file paths to the installed framework directory.  This macro is defined in a 
Visual Studio property sheet on Windows and as a custom project variable on Mac.  
Because this macro will not be resolved on Mac until compilation, the Xcode GUI 
will not be able to find the included files.  However, the projects should 
builds successfully once the macros are updated to point to the correct 
directory.

* The JUCE GUI Extension code in this SDK was written using version 1.51 of the
JUCE framework
