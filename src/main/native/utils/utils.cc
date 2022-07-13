/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2016-2021 Intel Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#if defined(_MSC_VER)
  #include <intrin.h> // SIMD intrinsics for Windows
#else
//  #include <x86intrin.h> // SIMD intrinsics for GCC
#define SIMDE_ENABLE_NATIVE_ALIASES
#include <simde/x86/avx512.h>
#include <simde/x86/avx.h>
#include <simde/x86/sse4.1.h>
  #include <simde/x86/sse.h>
#endif

#ifdef linux
  #include <omp.h>
#endif

#include "utils.h"
#include <avx.h>

/*
 * Class:     com_intel_gkl_IntelGKLUtils
 * Method:    getFlushToZeroNative
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_com_intel_gkl_IntelGKLUtils_getFlushToZeroNative
  (JNIEnv *env, jobject obj)
{
  jboolean value = SIMDE_MM_GET_FLUSH_ZERO_MODE() == _MM_FLUSH_ZERO_ON ? 1 : 0;
    return value;
}

/*
 * Class:     com_intel_gkl_IntelGKLUtils
 * Method:    setFlushToZeroNative
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_com_intel_gkl_IntelGKLUtils_setFlushToZeroNative
  (JNIEnv *env, jobject obj, jboolean value)
{
    if (value)
    {
      SIMDE_MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
    }
    else
    {
        SIMDE_MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_OFF);
    }
}

/*
 * Class:     com_intel_gkl_IntelGKLUtils
 * Method:    isAvxSupportedNative
 * Signature: (Z)V
 */
JNIEXPORT jboolean JNICALL Java_com_intel_gkl_IntelGKLUtils_isAvxSupportedNative
  (JNIEnv *env, jobject obj)
{
    return is_avx_supported();
}

/*
 * Class:     com_intel_gkl_IntelGKLUtils
 * Method:    isAvx2SupportedNative
 * Signature: (Z)V
 */
JNIEXPORT jboolean JNICALL Java_com_intel_gkl_IntelGKLUtils_isAvx2SupportedNative
  (JNIEnv *env, jobject obj)
{
    return is_avx2_supported();
}

/*
 * Class:     com_intel_gkl_IntelGKLUtils
 * Method:    isAvx512SupportedNative
 * Signature: (Z)V
 */
JNIEXPORT jboolean JNICALL Java_com_intel_gkl_IntelGKLUtils_isAvx512SupportedNative
  (JNIEnv *env, jobject obj)
{
    return is_avx512_supported();
}

/*
 * Class:     com_intel_gkl_IntelGKLUtils
 * Method:    getAvailableOmpThreadsNative
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_intel_gkl_IntelGKLUtils_getAvailableOmpThreadsNative
  (JNIEnv *env, jobject obj)
{
#ifdef _OPENMP
    int avail_threads = omp_get_max_threads();
#else
    int avail_threads = 0;
#endif

    return avail_threads;
}
