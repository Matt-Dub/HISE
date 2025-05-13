REM        Copyright 2016, 2023-2024 Avid Technology, Inc.
REM All rights reserved.
REM 
REM This file is part of the Avid AAX SDK.
REM 
REM The AAX SDK is subject to commercial or open-source licensing.
REM 
REM By using the AAX SDK, you agree to the terms of both the Avid AAX SDK License
REM Agreement and Avid Privacy Policy.
REM 
REM AAX SDK License: https://developer.avid.com/aax
REM Privacy Policy: https://www.avid.com/legal/privacy-policy-statement
REM 
REM Or: You may also use this code under the terms of the GPL v3 (see
REM www.gnu.org/licenses).
REM 
REM THE AAX SDK IS PROVIDED "AS IS" WITHOUT ANY WARRANTY, AND ALL WARRANTIES, WHETHER
REM EXPRESSED OR IMPLIED, INCLUDING MERCHANTABILITY AND FITNESS FOR PURPOSE, ARE
REM DISCLAIMED.

set OutDir=%1

CALL ..\..\..\..\Utilities\CreatePackage.bat %OutDir% ..\..\..\..\Utilities\PlugIn.ico

echo Copy "DemoSynthPages.xml"
copy /Y ..\..\Source\DemoSynthPages.xml %OutDir%\..\..\Contents\Resources\ > NUL

