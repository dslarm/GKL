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
set_property(SOURCE avx_impl.cc APPEND_STRING PROPERTY COMPILE_FLAGS " -mavx ")
set_property(SOURCE avx512_impl.cc APPEND_STRING PROPERTY COMPILE_FLAGS " -mavx -mavx2 -mavx512f -mavx512dq -mavx512vl ")
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
# pairhmm
#---------------------------------------------------------------------
set(TARGET gkl_pairhmm)
add_library(${TARGET} SHARED IntelPairHmm.cc avx_impl.cc avx512_impl.cc pairhmm_common.cc)
install(TARGETS ${TARGET} DESTINATION ${CMAKE_BINARY_DIR})

#---------------------------------------------------------------------
# pairhmm_omp
#---------------------------------------------------------------------
find_package(OpenMP)

if(OPENMP_FOUND)
  set(TARGET gkl_pairhmm_omp)
  add_library(${TARGET} SHARED IntelPairHmm.cc avx_impl.cc avx512_impl.cc pairhmm_common.cc)
  set_target_properties(${TARGET} PROPERTIES COMPILE_OPTIONS ${OpenMP_CXX_FLAGS})
  target_link_libraries(${TARGET} ${OpenMP_CXX_FLAGS})
  install(TARGETS ${TARGET} DESTINATION ${CMAKE_BINARY_DIR})
endif()

#---------------------------------------------------------------------
# pairhmm_c
#---------------------------------------------------------------------
set(TARGET gkl_pairhmm_c)
add_library(${TARGET} SHARED IntelPairHmmCSource.cpp avx_impl.cc avx512_impl.cc pairhmm_common.cc)
if (APPLE)
  target_link_libraries(${TARGET} gkl_pairhmm_shacc)
endif()
install(TARGETS ${TARGET} DESTINATION ${CMAKE_BINARY_DIR})
