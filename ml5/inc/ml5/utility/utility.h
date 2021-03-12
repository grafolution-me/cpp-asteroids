//       $Id: utility.h 633 2020-01-22 20:05:03Z p20068 $
//      $URL: https://svn01.fh-hagenberg.at/se/minilib/ml5/trunk/product/ml5/inc/ml5/utility/utility.h $
// $Revision: 633 $
//     $Date: 2020-01-22 21:05:03 +0100 (Mi., 22 Jän 2020) $
//   Creator: peter.kulczycki<AT>fh-hagenberg.at
//  Creation: June 1, 2018
//   $Author: p20068 $
// Copyright: (c) 2018 Peter Kulczycki (peter.kulczycki<AT>fh-hagenberg.at)
//            (c) 2018 Michael Hava (michael.hava<AT>fh-hagenberg.at)
//   License: This document contains proprietary information belonging to
//            University of Applied Sciences Upper Austria, Campus Hagenberg. It
//            is distributed under the Boost Software License, Version 1.0 (see
//            http://www.boost.org/LICENSE_1_0.txt).

#pragma once

#include "./libraries.h"
#include "./constants.h"
#include "./traits.h"

#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <cstring>
#include <ctime>
#include <functional>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <optional>
#include <random>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <thread>
#include <tuple>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <utility>
#include <vector>

#if defined ML5_DETECTED_COMPILER_GCC
   #include <cstdlib>
   #include <cxxabi.h>
#endif

namespace ml5 {

// -------------------------------------------------------------------------------------------------

using clock_t = std::chrono::steady_clock;   // std::chrono::high_resolution_clock

using duration_t = clock_t::duration;
using time_point = clock_t::time_point;

static_assert (clock_t::is_steady);

// -------------------------------------------------------------------------------------------------

template <typename T> T get_random_uniform (T const l, T const u) noexcept {
   static_assert (
      std::is_integral_v <T> || std::is_floating_point_v <T>,
      "ml5::get_random_uniform<T>: T must be an integral or floating-point type"
   );

   static std::mt19937_64 generator {
      static_cast <unsigned> (std::time (nullptr))   // better use seed sequences
   };

   if constexpr (std::is_integral_v <T>) {
      return std::uniform_int_distribution  <T> {l, u} (generator);
   } else {
      return std::uniform_real_distribution <T> {l, u} (generator);
   }
}

// -------------------------------------------------------------------------------------------------

}   // namespace ml5

namespace ml5::util {

// -------------------------------------------------------------------------------------------------

template <typename F> class final_action final {   // taken from the Guideline Support Library
   public:
      explicit constexpr final_action (F fun) noexcept : m_fun {std::move (fun)} {
      }

      final_action (final_action const &) = delete;

      constexpr final_action (final_action && other) noexcept
         : m_fun    {std::move (other.m_fun)}
         , m_invoke {other.m_invoke} {

         other.m_invoke = false;
      }

      final_action & operator = (final_action const &) = delete;
      final_action & operator = (final_action &&) = delete;

     ~final_action () noexcept {
         if (m_invoke) {
            m_fun ();
         }
      }

   private:
      F    m_fun    {};
      bool m_invoke {true};
};

template <typename F> constexpr final_action <F> finally (F fun) noexcept {
   return final_action <F> (std::move (fun));
}

// -------------------------------------------------------------------------------------------------

template <typename T> constexpr std::type_info const & type_info () noexcept {
   return typeid (T);   // std::remove_cvref_t
}

template <typename T> constexpr std::type_info const & static_type_info (T const &) noexcept {
   return type_info <T> ();
}

// -------------------------------------------------------------------------------------------------

template <typename T> constexpr T * nnull (T * const p) noexcept {
   Expects (p); return p;
}

template <typename T> constexpr std::unique_ptr <T> & nnull (std::unique_ptr <T> & p) noexcept {
   Expects (p); return p;
}

template <typename T> constexpr std::unique_ptr <T> const & nnull (std::unique_ptr <T> const & p) noexcept {
   Expects (p); return p;
}

template <typename T> constexpr T & deref (T * const p) noexcept {
   return *nnull (p);
}

template <typename T> constexpr T & deref (std::unique_ptr <T> const & p) noexcept {
   return *nnull (p);
}

// -------------------------------------------------------------------------------------------------

template <typename T, typename ...A> T & deref_new (A && ...a) {
   return deref (new T {std::forward <A> (a)...});
}

template <template <typename ...> typename C, typename ...A> auto make_from_values (A && ...a) {
   using T = std::common_type_t <A...>; return C <T> {static_cast <T> (std::forward <A> (a))...};
}

template <typename T> constexpr std::unique_ptr <T> make_unique_ptr (T * const p) noexcept {
   return std::unique_ptr <T> {nnull (p)};
}

template <typename T> constexpr std::unique_ptr <T []> make_unique_ptr_to_carray (T * const p) noexcept {
   return std::unique_ptr <T []> {nnull (p)};
}

template <typename T, typename D> constexpr std::unique_ptr <T [], D> make_unique_ptr_to_carray (T * const p, D && d) noexcept {
   return std::unique_ptr <T [], D> {nnull (p), d};
}

// -------------------------------------------------------------------------------------------------

inline std::string normalize_type_name (std::string const & name) {
   return std::regex_replace (std::regex_replace (name, std::regex {"class |enum |struct "}, ""), std::regex {"\\s*>\\s*"}, ">");
}

inline std::string type_as_string (std::type_info const & type) {
   #if defined ML5_HAVE_BOOST
      return normalize_type_name (boost::core::demangle (type.name ()));   // needs boost/core/typeinfo.hpp

   #elif defined ML5_DETECTED_COMPILER_GCC
      int        status {0};
      auto const name   {make_unique_ptr_to_carray (
         abi::__cxa_demangle (type.name (), nullptr, nullptr, &status),   // see https://gcc.gnu.org/onlinedocs/libstdc++/libstdc++-html-USERS-4.3/a01696.html
         std::free
      )};

      return normalize_type_name ((status == 0) ? name.get () : type.name ());

   #else
      return normalize_type_name (type.name ());
   #endif
}

template <typename T> constexpr std::string type_as_string () noexcept {
   return type_as_string (type_info <T> ());
}

template <typename T> constexpr std::string type_as_string (T const &) noexcept {
   return type_as_string (type_info <T> ());
}

// -------------------------------------------------------------------------------------------------

template <typename T> using wrapped_t = std::optional <std::reference_wrapper <T>>;

inline std::string erase_all (std::string s, char const c) {
   s.erase (std::remove (std::begin (s), std::end (s), c), std::end (s)); return s;
}

template <typename R> constexpr auto itor_from_ritor (R ritor) noexcept {
   return std::next (ritor).base ();
}

template <typename T> constexpr T & unwrap (wrapped_t <T> const & w) noexcept {
   return w.value ().get ();
}

// -------------------------------------------------------------------------------------------------

}   // namespace ml5::util
