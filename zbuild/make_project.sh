#!/bin/sh

#cmake -G "Eclipse CDT4 - Unix Makefiles" -DCMAKE_ECLIPSE_GENERATE_SOURCE_PROJECT=TRUE -DCMAKE_ECLIPSE_MAKE_ARGUMENTS=-j8 .
cmake " -G \"Eclipse CDT4 - Unix Makefiles\" -DCMAKE_BUILD_TYPE:STRING=DEBUG" .
