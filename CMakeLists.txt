cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(WebBind VERSION 0.1)


IF (NOT ${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
  message(FATAL_ERROR "WebBind need to be compiled with emscripten to WASM, currently building to ${CMAKE_SYSTEM_NAME}.")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS YES)
set(CMAKE_FIND_PACKAGE_REDIRECTS_DIR ${CMAKE_BINARY_DIR})

message(${PROJECT_NAME} ": compiler id is " ${CMAKE_CXX_COMPILER_ID} " VERSION IS " ${CMAKE_CXX_COMPILER_VERSION})

# add compile caching if ccache is installed on the system
find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
  set(CXX_COMPILER_LAUNCHER  "${CCACHE_PROGRAM}" CACHE INTERNAL "")
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
  message("Enabled compiler caching")
endif()


add_compile_options(-DNDEBUG)
add_compile_options(-Wno-attributes)
add_compile_options(-ffp-contract=off)
add_compile_options(-fstrict-aliasing)
add_compile_options(-fPIC)
add_compile_options(-fvisibility=hidden)
add_compile_options(-O3)

add_compile_options(-std=c++17)
add_compile_options(-fvisibility-inlines-hidden)
add_compile_options(-fno-exceptions)

add_compile_options(-pthread)

# comment out the two lines below and it works
add_compile_options(-fno-rtti)
add_compile_options(-DEMSCRIPTEN_HAS_UNBOUND_TYPE_NAMES=0)

set(CMAKE_EXECUTABLE_SUFFIX ".js")

add_executable(Example
  "src/main.cpp")


target_link_options(Example
  PUBLIC
  -Oz
  -fno-rtti
  "SHELL:--pre-js ${CMAKE_CURRENT_SOURCE_DIR}/JS/helloWorld.js"
  "SHELL:--post-js ${CMAKE_CURRENT_SOURCE_DIR}/JS/post.js"
  "SHELL:--extern-post-js ${CMAKE_CURRENT_SOURCE_DIR}/JS/loadWebBind.js"
  -sALLOW_MEMORY_GROWTH
  -sDISABLE_EXCEPTION_CATCHING
  -sINVOKE_RUN=0
  -sNODEJS_CATCH_EXIT=0
  -sIGNORE_MISSING_MAIN=0
  -sDYNAMIC_EXECUTION=0
  -sEXPORT_NAME=WebBindInit
  -sEXPORTED_FUNCTIONS=[_main]
  -sFORCE_FILESYSTEM=0
  -sFILESYSTEM=0
  -sMODULARIZE
  -sNO_EXIT_RUNTIME=1
  -sINITIAL_MEMORY=128MB
  -sWASM=1
  -sSTRICT=1
  -sASSERTIONS=0
  --no-entry
  -sASSERTIONS=0
  -sEXIT_RUNTIME
  -lembind)

add_custom_command(
  TARGET Example POST_BUILD
  COMMAND js-beautify -r "$<TARGET_FILE:Example>"
  VERBATIM)

set_property(TARGET Example PROPERTY OUTPUT_NAME webBind)
set_property(TARGET Example PROPERTY LINK_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/JS/helloWorld.js;${CMAKE_CURRENT_SOURCE_DIR}/JS/loadWebBind.js)
