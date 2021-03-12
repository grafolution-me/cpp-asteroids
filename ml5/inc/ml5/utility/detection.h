//       $Id: detection.h 607 2019-11-02 22:46:30Z p27116 $
//      $URL: https://svn01.fh-hagenberg.at/se/minilib/ml5/trunk/product/ml5/inc/ml5/utility/detection.h $
// $Revision: 607 $
//     $Date: 2019-11-02 23:46:30 +0100 (Sa., 02 Nov 2019) $
//   Creator: peter.kulczycki<AT>fh-hagenberg.at
//  Creation: June 1, 2018
//   $Author: p27116 $
// Copyright: (c) 2018 Peter Kulczycki (peter.kulczycki<AT>fh-hagenberg.at)
//            (c) 2018 Michael Hava (michael.hava<AT>fh-hagenberg.at)
//   License: This document contains proprietary information belonging to
//            University of Applied Sciences Upper Austria, Campus Hagenberg. It
//            is distributed under the Boost Software License, Version 1.0 (see
//            http://www.boost.org/LICENSE_1_0.txt).

#pragma once

#include "./macros.h"

#include <type_traits>

// -------------------------------------------------------------------------------------------------

#undef ML5_DETECTED_OS_LINUX
#undef ML5_DETECTED_OS_MINGW
#undef ML5_DETECTED_OS_NONE
#undef ML5_DETECTED_OS_TYPE
#undef ML5_DETECTED_OS_WINDOWS

#if defined __linux || defined __posix || defined __unix
   #define ML5_DETECTED_OS_TYPE ml5::util::detected_os_linux
   #define ML5_DETECTED_OS_LINUX

#elif defined _WIN32 || defined _WIN64
   #define ML5_DETECTED_OS_TYPE ml5::util::detected_os_windows
   #define ML5_DETECTED_OS_WINDOWS

   #if defined __MINGW32__ || defined __MINGW64__
      #undef  ML5_DETECTED_OS_TYPE
      #define ML5_DETECTED_OS_TYPE ml5::util::detected_os_mingw
      #define ML5_DETECTED_OS_MINGW
   #endif

#else
   #define ML5_DETECTED_OS_TYPE ml5::util::detected_os_none
   #define ML5_DETECTED_OS_NONE
#endif

// -------------------------------------------------------------------------------------------------

#undef ML5_DETECTED_COMPILER_CL
#undef ML5_DETECTED_COMPILER_CLANG
#undef ML5_DETECTED_COMPILER_GCC
#undef ML5_DETECTED_COMPILER_ICC
#undef ML5_DETECTED_COMPILER_NONE
#undef ML5_DETECTED_COMPILER_NVCC
#undef ML5_DETECTED_COMPILER_TYPE

#if defined __clang__
   #define ML5_DETECTED_COMPILER_TYPE ml5::util::detected_compiler_clang
   #define ML5_DETECTED_COMPILER_CLANG

#elif defined __CUDACC__ && ((__CUDACC_VER_MAJOR__ > 9) || ((__CUDACC_VER_MAJOR__ == 9) && (__CUDACC_VER_MINOR__ >= 2)))   // >= 9.2
   #define ML5_DETECTED_COMPILER_TYPE ml5::util::detected_compiler_nvcc
   #define ML5_DETECTED_COMPILER_NVCC

#elif defined __GNUC__ && ((__GNUC__ > 7) || ((__GNUC__ == 7) && (__GNUC_MINOR__ >= 3)))   // >= 7.3
   #define ML5_DETECTED_COMPILER_TYPE ml5::util::detected_compiler_gcc
   #define ML5_DETECTED_COMPILER_GCC

#elif defined __INTEL_COMPILER
   #define ML5_DETECTED_COMPILER_TYPE ml5::util::detected_compiler_icc
   #define ML5_DETECTED_COMPILER_ICC

#elif defined _MSC_VER && (_MSC_VER >= 1914)   // >= 19.14
   #define ML5_DETECTED_COMPILER_TYPE ml5::util::detected_compiler_cl
   #define ML5_DETECTED_COMPILER_CL

#else
   #define ML5_DETECTED_COMPILER_TYPE ml5::util::detected_compiler_none
   #define ML5_DETECTED_COMPILER_NONE
#endif

namespace ml5::util {

// -------------------------------------------------------------------------------------------------

enum class os {
   none,     // no operating system detected
   linux,    //
   mingw,    // MinGW, MSYS2
   windows   //
};

using detected_os_none    = std::integral_constant <os, os::none>;
using detected_os_linux   = std::integral_constant <os, os::linux>;
using detected_os_mingw   = std::integral_constant <os, os::mingw>;
using detected_os_windows = std::integral_constant <os, os::windows>;

using detected_os = ML5_DETECTED_OS_TYPE;

constexpr os detected_os_v {detected_os::value};

constexpr char const * detected_os_as_string () noexcept {
   if constexpr (detected_os_v == os::linux)   return "linux";   else
   if constexpr (detected_os_v == os::mingw)   return "mingw";   else
   if constexpr (detected_os_v == os::windows) return "windows"; else
                                               return "none";
}

// -------------------------------------------------------------------------------------------------

enum class compiler {
   none,    // no compiler detected
   cl,      // Microsoft Compiler
   clang,   // Clang Compiler-Frontend
   gcc,     // GNU Compiler-Suite
   icc,     // Intel Compiler
   nvcc     // NVIDIA CUDA-Compiler
};

using detected_compiler_none  = std::integral_constant <compiler, compiler::none>;
using detected_compiler_cl    = std::integral_constant <compiler, compiler::cl>;
using detected_compiler_clang = std::integral_constant <compiler, compiler::clang>;
using detected_compiler_gcc   = std::integral_constant <compiler, compiler::gcc>;
using detected_compiler_icc   = std::integral_constant <compiler, compiler::icc>;
using detected_compiler_nvcc  = std::integral_constant <compiler, compiler::nvcc>;

using detected_compiler = ML5_DETECTED_COMPILER_TYPE;

constexpr compiler detected_compiler_v {detected_compiler::value};

constexpr char const * detected_compiler_as_string () noexcept {
   if constexpr (detected_compiler_v == compiler::cl)    return "cl";    else
   if constexpr (detected_compiler_v == compiler::clang) return "clang"; else
   if constexpr (detected_compiler_v == compiler::gcc)   return "gcc";   else
   if constexpr (detected_compiler_v == compiler::icc)   return "icc";   else
   if constexpr (detected_compiler_v == compiler::nvcc)  return "nvcc";  else
                                                         return "none";
}

// -------------------------------------------------------------------------------------------------

}   // namespace ml5::util

#undef ML5_DETECTED_COMPILER_TYPE
#undef ML5_DETECTED_OS_TYPE

// -------------------------------------------------------------------------------------------------
