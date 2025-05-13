//
//
// Copyright 2014, 2023-2024 Avid Technology, Inc. All rights reserved.
// 
// This file is part of the Avid AAX SDK.
// 
// The AAX SDK is subject to commercial or open-source licensing.
// 
// By using the AAX SDK, you agree to the terms of both the Avid AAX SDK License
// Agreement and Avid Privacy Policy.
// 
// AAX SDK License: https://developer.avid.com/aax
// Privacy Policy: https://www.avid.com/legal/privacy-policy-statement
// 
// Or: You may also use this code under the terms of the GPL v3 (see
// www.gnu.org/licenses).
// 
// THE AAX SDK IS PROVIDED "AS IS" WITHOUT ANY WARRANTY, AND ALL WARRANTIES, WHETHER
// EXPRESSED OR IMPLIED, INCLUDING MERCHANTABILITY AND FITNESS FOR PURPOSE, ARE
// DISCLAIMED.
//
//

/*
The __binit__ section stores data that that needs to be copied at load-time. Plug-ins don't use it, but since our plug-ins are actually dynamic executables rather than dynamic libraries, we need to have the initialization functions just like a static executable - this is why we link to the RTS library and export the auto_init_elf function. But because we link to RTS, we need to handle __binit__.
*/
#pragma once
#ifndef _ELF_LINKAGE_AAX_CCSV5_H_
#define _ELF_LINKAGE_AAX_CCSV5_H_

#include <elf_linkage.h>

// #include <cpy_tbl.h>
// far const COPY_TABLE *__binit__;

far const int* __binit__;

#endif
