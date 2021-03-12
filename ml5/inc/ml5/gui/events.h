//       $Id: events.h 625 2020-01-12 15:50:54Z p20068 $
//      $URL: https://svn01.fh-hagenberg.at/se/minilib/ml5/trunk/product/ml5/inc/ml5/gui/events.h $
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

#include "./impl/wx.h"

#include "../base/object.h"

namespace ml5 {

// -------------------------------------------------------------------------------------------------

class ML5_DLL_EXPORT event : public object, MI5_DERIVE (event, object) {
   MI5_INJECT (event)

   public:
      template <typename E> explicit event (E const & event) : m_event {event} {
      }

      event (event const &) = delete;
      event (event &&) = delete;

      virtual ~event () = 0;

      event & operator = (event const &) = delete;
      event & operator = (event &&) = delete;

   protected:
      template <typename E> E const & get_event () const {
         return static_cast <E const &> (m_event);   // a static_cast is safe here
      }

   private:
      wxEvent const & m_event;
};

// -------------------------------------------------------------------------------------------------

class ML5_DLL_EXPORT idle_event final : public event, MI5_DERIVE (idle_event, event) {
   MI5_INJECT (idle_event)

   public:
      explicit idle_event (wxIdleEvent const &);

   private:
      wxIdleEvent const & get_event () const;
};

// -------------------------------------------------------------------------------------------------

class ML5_DLL_EXPORT key_event final : public event, MI5_DERIVE (key_event, event) {
   MI5_INJECT (key_event)

   public:
      explicit key_event (wxKeyEvent const &);

      int get_key_code () const;

   private:
      wxKeyEvent const & get_event () const;
};

// -------------------------------------------------------------------------------------------------

class ML5_DLL_EXPORT menu_event final : public event, MI5_DERIVE (menu_event, event) {
   MI5_INJECT (menu_event)

   public:
      explicit menu_event (wxCommandEvent const & event, std::tuple <std::string, std::string> const & item);

      std::string const & get_item           () const;
      std::string const & get_title          () const;
      std::string         get_title_and_item () const;

   private:
      wxCommandEvent const & get_event () const;

      std::tuple <std::string, std::string> const & m_item;
};

// -------------------------------------------------------------------------------------------------

class ML5_DLL_EXPORT mouse_event final : public event, MI5_DERIVE (mouse_event, event) {
   MI5_INJECT (mouse_event)

   public:
      explicit mouse_event (wxMouseEvent const &);

      int     get_button         () const;
      wxPoint get_position       () const;
      int     get_wheel_rotation () const;
      bool    is_left_button     () const;
      bool    is_right_button    () const;

   private:
      wxMouseEvent const & get_event () const;
};

// -------------------------------------------------------------------------------------------------

class ML5_DLL_EXPORT paint_event final : public event, MI5_DERIVE (paint_event, event) {
   MI5_INJECT (paint_event)

   public:
      using context_t = wxDC;
//    using context_t = wxGraphicsContext;

      explicit paint_event (wxPaintEvent const & event);
      explicit paint_event (wxPaintEvent const & event, context_t & context);

      context_t & get_context () const;
      bool        has_context () const;

   private:
      wxPaintEvent const & get_event () const;

      util::wrapped_t <context_t> m_context;
};

// -------------------------------------------------------------------------------------------------

class ML5_DLL_EXPORT size_event final : public event, MI5_DERIVE (size_event, event) {
   MI5_INJECT (size_event)

   public:
      explicit size_event (wxSizeEvent const &);

      wxSize get_size () const;

   private:
      wxSizeEvent const & get_event () const;
};

// -------------------------------------------------------------------------------------------------

class ML5_DLL_EXPORT timer_event final : public event, MI5_DERIVE (timer_event, event) {
   MI5_INJECT (timer_event)

   public:
      explicit timer_event (time_point, duration_t, double, wxTimerEvent const &);

      double const &     get_fps        () const;
      duration_t const & get_interval   () const;
      time_point const & get_time_point () const;

   private:
      wxTimerEvent const & get_event () const;

      double     m_fps        {0.0};
      duration_t m_interval   {0};
      time_point m_time_point {};
};

// -------------------------------------------------------------------------------------------------

}   // namespace ml5
