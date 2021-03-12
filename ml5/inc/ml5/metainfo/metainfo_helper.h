//       $Id: metainfo_helper.h 607 2019-11-02 22:46:30Z p27116 $
//      $URL: https://svn01.fh-hagenberg.at/se/minilib/ml5/trunk/product/ml5/inc/ml5/metainfo/metainfo_helper.h $
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

#include "./metainfo_injector.h"

namespace ml5::util {

template <typename C> struct get_metainfo_helper final {
   template <bool A, typename ...B> static metainfo_injector <C, A, B...> deducer (metainfo_injector <C, A, B...> const &);

   static constexpr metainfo <C> const & get_meta_info () noexcept {
      return decltype (deducer (std::declval <C> ()))::get_metainfo ();
   }
};

}   // namespace ml5::util

namespace ml5 {

template <typename C> constexpr metainfo <C> const & get_metainfo () noexcept {
   return util::get_metainfo_helper <C>::get_meta_info ();
}

template <typename C, typename ...A> std::unique_ptr <C> instantiate (A && ...a) {
   return get_metainfo <C> ().instantiate (std::forward <A> (a)...);
}

}   // namespace ml5
