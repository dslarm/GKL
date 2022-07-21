#---------------------------------------------------------------------
# common
#---------------------------------------------------------------------
if(NOT APPLE)
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--no-as-needed")
endif()
if (CMAKE_SYSTEM_PROCESSOR MATCHES "(x86)|(X86)|(amd64)|(AMD64)")
    set (X86 TRUE)
    message("Is x86")
else ()
    set (X86 FALSE)
    message("Is not x86")
endif ()

if(X86)
set_property(SOURCE avx2_impl.cc APPEND_STRING PROPERTY COMPILE_FLAGS " -mavx -mavx2 ")
set_property(SOURCE avx512_impl.cc APPEND_STRING PROPERTY COMPILE_FLAGS " -mavx -mavx2 -mavx512f -mavx512dq -mavx512vl -mavx512bw ")
endif()

#---------------------------------------------------------------------
# common includes
#---------------------------------------------------------------------
include_directories(../common)
if (NOT $ENV{SSE2NEON} STREQUAL "")
include_directories(../../../../sse2neon)
add_definitions( -DSSE2NEON )
else()
include_directories(../../../../simde)
endif()

#---------------------------------------------------------------------
# smithwaterman
#---------------------------------------------------------------------
set(TARGET gkl_smithwaterman)


add_library(${TARGET} SHARED
    IntelSmithWaterman.cc avx2_impl.cc avx512_impl.cc smithwaterman_common.cc)

install(TARGETS ${TARGET} DESTINATION ${CMAKE_BINARY_DIR})

