//       $Id: application.h 625 2020-01-12 15:50:54Z p20068 $
//      $URL: https://svn01.fh-hagenberg.at/se/minilib/ml5/trunk/product/ml5/inc/ml5/gui/application.h $
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

#pragma once

#include "./impl/impl_application.h"

#include "./window.h"

// -------------------------------------------------------------------------------------------------

namespace ml5 {

class ML5_DLL_EXPORT application : public object, MI5_DERIVE (application, object) {
   MI5_INJECT (application)

   friend class impl::canvas;
   friend class impl::frame;

   public:
      application () = default;

      application (application const &) = delete;
      application (application &&) = delete;

      virtual ~application () = 0;

      application & operator = (application const &) = delete;
      application & operator = (application &&) = delete;

                               window & get_win () const;
      template <typename ...A> int      run     (A && ...args);

   protected:
      virtual std::unique_ptr <window> make_window () const = 0;

      virtual void on_exit  ();
      virtual void on_init  ();

      virtual void on_idle  (idle_event const & event);
      virtual void on_timer (timer_event const & event);

   private:
      impl::application *      m_p_app_impl {nullptr};
      std::unique_ptr <window> m_p_win      {nullptr};
};

}   // namespace ml5

// -------------------------------------------------------------------------------------------------

#include "./application.inl"
