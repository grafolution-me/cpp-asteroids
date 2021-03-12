//       $Id: container.h 633 2020-01-22 20:05:03Z p20068 $
//      $URL: https://svn01.fh-hagenberg.at/se/minilib/ml5/trunk/product/ml5/inc/ml5/container/container.h $
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

#include "./iterator_adapter.h"

namespace ml5 {

// -------------------------------------------------------------------------------------------------

template <typename T> class container : public object, MI5_DERIVE (container <T>, object) {
   MI5_INJECT (container <T>)

   static_assert (!std::is_const_v <T>);

   public:
      virtual ~container ();

      virtual void        add      (T value) = 0;
      virtual void        clear    () noexcept = 0;
      virtual bool        contains (T const & value) const noexcept = 0;
      virtual void        remove   (T const & value) noexcept = 0;
      virtual std::size_t size     () const noexcept = 0;

      virtual std::unique_ptr <iterator <T>> make_iterator () = 0;
      virtual std::unique_ptr <iterator <T>> make_iterator () const;

      util::iterator_adapter <T> begin () const noexcept;
      util::iterator_adapter <T> end   () const noexcept;

      bool           empty        () const noexcept;
//    iterator <T> * new_iterator () const;
};

// -------------------------------------------------------------------------------------------------

template <typename T> std::ostream & operator << (std::ostream & lhs, container <T> const & rhs);

// -------------------------------------------------------------------------------------------------

}   // namespace ml5

#include "./container.inl"
