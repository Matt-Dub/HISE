<!--
 *
 * Copyright 2024 Avid Technology, Inc.
 * All rights reserved.
 * 
 * This file is part of the Avid AAX SDK.
 * 
 * The AAX SDK is subject to commercial or open-source licensing.
 * 
 * By using the AAX SDK, you agree to the terms of both the Avid AAX SDK License
 * Agreement and Avid Privacy Policy.
 * 
 * AAX SDK License: https://developer.avid.com/aax
 * Privacy Policy: https://www.avid.com/legal/privacy-policy-statement
 * 
 * Or: You may also use this code under the terms of the GPL v3 (see
 * www.gnu.org/licenses).
 * 
 * THE AAX SDK IS PROVIDED "AS IS" WITHOUT ANY WARRANTY, AND ALL WARRANTIES, WHETHER
 * EXPRESSED OR IMPLIED, INCLUDING MERCHANTABILITY AND FITNESS FOR PURPOSE, ARE
 * DISCLAIMED.
 *
 -->

# AAX SDK

## Prerequisites

To access the AAX SDK, first sign up as an AAX developer at
[developer.avid.com/audio](https://developer.avid.com/audio). You can then download
the AAX SDK from [my.avid.com](https://my.avid.com/products/cppsdk)

Pro Tools requires an iLok authorization. Contact devauth@avid.com if you need to
request a license.

Pro Tools also requires that AAX plugins are digitally signed using tools from PACE
Anti-Piracy Inc. Special "developer builds" of Pro Tools can run unsigned plugins.
Developer build installers are available at [my.avid.com](https://my.avid.com/products/cppsdk).

When you are ready to make your AAX products available to users, request access to the
digital signing tools by writing to audiosdk@avid.com

## Quick Start

1. Build the AAX Library project in [Libs/AAXLibrary](Libs/AAXLibrary)
2. Build any of the example plugin projects in [ExamplePlugIns](ExamplePlugIns)
3. Install the resulting aaxplugin into the AAX plug-ins directory

   * macOS: /Library/Application Support/Avid/Audio/Plug-Ins
   * Windows: C:\Program Files\Common Files\Avid\Audio\Plug-Ins

4. Run a developer build of Pro Tools to use the plugin

<!--
The AAX Library is a static library containing base implementations of the
AAX API. AAX plug-ins typically link to this library to inherit a default
implementation of the AAX API, then override the library classes to provide
customized behavior.
-->

## Documentation

See the [code generated documentation](docs.html) for more information about the AAX SDK

The SDK documentation is also provided in PDF form. The PDF documentation is not
recommended for browsing but can be very useful for text-based searches.


## Tips

If you create a folder named "Plug-Ins" next to your host executable then
this plug-ins folder will be used instead of the the system plug-ins folder.

On Windows, if you place the SDK too deep in your file hierarchy you may
encounter build failures due to the system's path length limitation. To avoid
this issue, locate the SDK near the root of your drive.
