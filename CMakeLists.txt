cmake_minimum_required (VERSION 2.8)
set(CMAKE_LEGACY_CYGWIN_WIN32 0)

#set(CROSS x86_64-w64-mingw32-)
set(CMAKE_C_COMPILER ${CROSS}gcc)
set(CMAKE_CXX_COMPILER ${CROSS}g++)

project (Demo)

set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_C_FLAGS_DEBUG "-g -O0 -DDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -DDEBUG")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(POSITION_INDEPENDENT_CODE ON)

# add definitions for single target
add_library(pr OBJECT srcs/print_num.c srcs/print_str.cpp)
target_compile_definitions(pr PRIVATE -DDEMO)

add_library(mc OBJECT srcs/myclass.cpp)
add_library(str OBJECT srcs/strng.c)

# combine multiple libraries into standalone static library with target objects
add_library(st1 STATIC 
  $<TARGET_OBJECTS:pr>
  $<TARGET_OBJECTS:mc>
  $<TARGET_OBJECTS:str>)

add_library(ma srcs/power.c)
add_library(ut srcs/conv.c)

# combine multiple libraries into standalone static library with AR script
# this method can deliver the standalone library without the dependens
# also we can use create a thin archive with "ar cTq <new-lib> <dep-libs>"
# a single static library can resolve a cycle dependency in multiple libraries.
set(libSta sta)
set(filSta ${CMAKE_STATIC_LIBRARY_PREFIX}${libSta}${CMAKE_STATIC_LIBRARY_SUFFIX})
set(arScript "CREATE ${filSta}\\n")
list(APPEND arScript "ADDLIB $<TARGET_FILE_NAME:ma>\\n")
list(APPEND arScript "ADDLIB $<TARGET_FILE_NAME:ut>\\n")
list(APPEND arScript "ADDLIB $<TARGET_FILE_NAME:st1>\\n")
list(APPEND arScript "SAVE\\nEND")
# remove ";" from the string list
string(REPLACE ";" "" arScript ${arScript})

set(filSta ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${filSta})
add_custom_command(OUTPUT ${filSta}
  COMMAND printf "${arScript}" | ${CMAKE_AR} -M
  DEPENDS ma ut st1
  WORKING_DIRECTORY ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}
  VERBATIM)
set_directory_properties(PROPERTIES 
  ADDITIONAL_MAKE_CLEAN_FILES ${filSta})
add_custom_target(tgt_${libSta}
  DEPENDS ${filSta}
  COMMENT "Combine all libraries into standalone.")

#wrap the custom target to a static imported library
add_library(${libSta} STATIC IMPORTED GLOBAL)
add_dependencies(${libSta} tgt_${libSta})
set_target_properties(${libSta} PROPERTIES
  IMPORTED_LOCATION ${filSta})
  #INTERFACE_INCLUDE_DIRECTORIES ${LIB_HEADER_FOLDER}

# using same file for different executable only compiling once
add_library(main OBJECT srcs/main.cpp)

link_directories(${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})

# Create a executable target with static link
add_executable(ap_s $<TARGET_OBJECTS:main>)
target_link_libraries(ap_s LINK_PRIVATE ${libSta})

# convert a static library to shared library without source
# using a dummy source for add_library.
# set target property LINKER_LANGUAGE to CXX, 
# because of the archive includes c++ objects,
# so that cmake can determine g++ as the linker instead of gcc,
# otherwise, some unreference c++ symbols are raised.
# also, we can use a .cpp file as the dummy source, same result as above. 
add_custom_command(OUTPUT dummy.c
  COMMAND touch dummy.c)

add_library(shd SHARED dummy.c)
target_link_libraries(shd LINK_PRIVATE
  #-Wl,--export-all-symbols   # tested on cygwin, it's not nesserary.
  -Wl,--whole-archive
  ${libSta}
  -Wl,--no-whole-archive
)
set_target_properties(shd PROPERTIES LINKER_LANGUAGE CXX)

# Create a executable target with dynamic link
add_executable(ap_d $<TARGET_OBJECTS:main>)
target_link_libraries(ap_d LINK_PRIVATE shd)

# use LINK_PRIVATE is must in this case.
