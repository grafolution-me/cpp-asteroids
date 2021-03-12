//       $Id: gl.h 607 2019-11-02 22:46:30Z p27116 $
//      $URL: https://svn01.fh-hagenberg.at/se/minilib/ml5/trunk/product/ml5/inc/ml5/gui/impl/gl.h $
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

#include "./wx.h"

namespace ml5::util {

template <typename T> void circle (T const x, T const y, T const radius) noexcept {
   static_assert (
      std::is_floating_point_v <T>, "ml5::util::circle<T>: T must be a floating-point type"
   );

   constexpr int segments  {60};
   constexpr T   increment {360 * deg <T> / segments};

   T angle {0};

   glBegin (GL_TRIANGLE_FAN);

   vertex_2 (x, y);

   for (int i {0}; i <= segments; ++i) {
      vertex_2 (x + radius * std::cos (angle),
                y + radius * std::sin (angle));

      angle += increment;
   }

   glEnd ();
}

inline void vertex_2 (float const x, float const y) noexcept{
   glVertex2f (x, y);
}

inline void vertex_2 (double const x, double const y) noexcept{
   glVertex2d (x, y);
}

}   // namespace ml5::util
