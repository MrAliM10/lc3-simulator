# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\SA_P1_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\SA_P1_autogen.dir\\ParseCache.txt"
  "SA_P1_autogen"
  )
endif()
