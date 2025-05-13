/*
 * Copyright 2014, 2023-2024 Avid Technology, Inc. All rights reserved.
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
 */

-mv67p
--abi=eabi
--mem_model:data=far
--gcc
--long_precision_bits=32
--keep_asm
--src_interlist
--asm_listing
--diag_warning=225
--debug_software_pipeline	/* debug_software_pipeline puts extra software pipeline optimization info in the asm files, has no performance effect on debug or release builds. */
