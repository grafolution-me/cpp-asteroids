//       $Id: iterator.h 633 2020-01-22 20:05:03Z p20068 $
//      $URL: https://svn01.fh-hagenberg.at/se/minilib/ml5/trunk/product/ml5/inc/ml5/container/iterator.h $
// $Revision: 633 $
//     $Date: 2020-01-22 21:05:03 +0100 (Mi., 22 Jän 2020) $
//   Creator: michael.hava<AT>fh-hagenberg.at
//  Creation: June 1, 2018
//   $Author: p20068 $
// Copyright: (c) 2018 Michael Hava (michael.hava<AT>fh-hagenberg.at)
//            (c) 2018 Peter Kulczycki (peter.kulczycki<AT>fh-hagenberg.at)
//   License: This document contains proprietary information belonging to
//            University of Applied Sciences Upper Austria, Campus Hagenberg. It
//            is distributed under the Boost Software License, Version 1.0 (see
//            http://www.boost.org/LICENSE_1_0.txt).

#pragma once

#include "../base/object.h"

namespace ml5 {

template <typename T> class iterator : public object, MI5_DERIVE (iterator <T>, object) {
   MI5_INJECT (iterator <T>)

   public:
      virtual ~iterator () = 0;

      virtual T &  get_current () const = 0;
      virtual bool is_at_end   () const noexcept = 0;
      virtual void to_next     () = 0;

      constexpr bool not_at_end () const noexcept {
         return !is_at_end ();
      }
};

template <typename T> iterator <T>::~iterator () = default;

}   // namespace ml5
