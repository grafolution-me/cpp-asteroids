//       $Id: application.cpp 625 2020-01-12 15:50:54Z p20068 $
//      $URL: https://svn01.fh-hagenberg.at/se/minilib/ml5/trunk/product/ml5/src/gui/application.cpp $
// $Revision: 625 $
//     $Date: 2020-01-12 16:50:54 +0100 (So., 12 Jän 2020) $
//   Creator: peter.kulczycki<AT>fh-hagenberg.at
//  Creation: June 1, 2018
//   $Author: p20068 $
// Copyright: (c) 2018 Peter Kulczycki (peter.kulczycki<AT>fh-hagenberg.at)
//            (c) 2018 Michael Hava (michael.hava<AT>fh-hagenberg.at)
//   License: This document contains proprietary information belonging to
//            University of Applied Sciences Upper Austria, Campus Hagenberg. It
//            is distributed under the Boost Software License, Version 1.0 (see
//            http://www.boost.org/LICENSE_1_0.txt).

#include "../../inc/ml5/gui/application.h"

namespace ml5 {

application::~application () = default;

window & application::get_win () const {
   return deref (m_p_win);
}

void application::on_exit () {
}

void application::on_init () {
}

void application::on_idle (idle_event const &) {
}

void application::on_timer (timer_event const &) {
}

}   // namespace ml5
