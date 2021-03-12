//       $Id: object.cpp 607 2019-11-02 22:46:30Z p27116 $
//      $URL: https://svn01.fh-hagenberg.at/se/minilib/ml5/trunk/product/ml5/src/base/object.cpp $
// $Revision: 607 $
//     $Date: 2019-11-02 23:46:30 +0100 (Sa., 02 Nov 2019) $
//   Creator: michael.hava<AT>fh-hagenberg.at
//  Creation: June 1, 2018
//   $Author: p27116 $
// Copyright: (c) 2018 Michael Hava (michael.hava<AT>fh-hagenberg.at)
//            (c) 2018 Peter Kulczycki (peter.kulczycki<AT>fh-hagenberg.at)
//   License: This document contains proprietary information belonging to
//            University of Applied Sciences Upper Austria, Campus Hagenberg. It
//            is distributed under the Boost Software License, Version 1.0 (see
//            http://www.boost.org/LICENSE_1_0.txt).

#include "../../inc/ml5/base/object.h"

namespace ml5 {

object::~object () = default;

std::string const & object::get_class_name () const noexcept {
   return get_metainfo ().name ();
}

object::minfo_cont_t const & object::get_metainfo_bases () const noexcept {
   return get_metainfo ().bases ();
}

bool object::is_a (std::string const & name) const noexcept {
   return get_metainfo ().is_a (name);
}

bool object::is_a (std::type_info const & type) const noexcept {
   return get_metainfo ().is_a (type);
}

}   // namespace ml5
