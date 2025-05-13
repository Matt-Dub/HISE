#!/bin/sh
# 
# Copyright 2023-2024 Avid Technology, Inc.
# 
# This file is part of the Avid AAX SDK.
# 
# The AAX SDK is subject to commercial or open-source licensing.
# 
# By using the AAX SDK, you agree to the terms of both the Avid AAX SDK License
# Agreement and Avid Privacy Policy.
# 
# AAX SDK License: https://developer.avid.com/aax
# Privacy Policy: https://www.avid.com/legal/privacy-policy-statement
# 
# Or: You may also use this code under the terms of the GPL v3 (see
# www.gnu.org/licenses).
# 
# THE AAX SDK IS PROVIDED "AS IS" WITHOUT ANY WARRANTY, AND ALL WARRANTIES, WHETHER
# EXPRESSED OR IMPLIED, INCLUDING MERCHANTABILITY AND FITNESS FOR PURPOSE, ARE
# DISCLAIMED.

DIR="$( cd "$( dirname "$0" )" && pwd )"

# Fix paths that incorrectly point to dot directory
perl -e 's#\/Volumes.*?\/dot\/#\.\/#g;' -pi $(find ${DIR}/output -type f)

# Put dot images into 'centered' class
perl -e 's#\<img(.*?)src\=\"dot_#\<img class="centered"\1src\=\"dot_#g;' -pi $(find ${DIR}/output/html/*.html -type f)
