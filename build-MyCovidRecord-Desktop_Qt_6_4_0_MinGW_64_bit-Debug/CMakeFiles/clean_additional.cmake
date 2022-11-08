# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\MyCovidRecord_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\MyCovidRecord_autogen.dir\\ParseCache.txt"
  "MyCovidRecord_autogen"
  )
endif()
