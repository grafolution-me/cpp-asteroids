//       $Id: vector_iterator.h 607 2019-11-02 22:46:30Z p27116 $
//      $URL: https://svn01.fh-hagenberg.at/se/minilib/ml5/trunk/product/ml5/inc/ml5/container/vector_iterator.h $
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

#pragma once

#include "./iterator.h"

// -------------------------------------------------------------------------------------------------

namespace ml5 {

template <typename T> class vector_iterator final : public iterator <T>, MI5_DERIVE (vector_iterator <T>, iterator <T>) {
   MI5_INJECT (vector_iterator <T>)

   template <typename> friend class vector;

   public:
      explicit vector_iterator (T * ptr, std::size_t size);   // cannot be private because of make_unique

      T &  get_current () const override;
      bool is_at_end   () const noexcept override;
      void to_next     () override;

   private:
      T * m_ptr {nullptr};
      T * m_end {nullptr};
};

}   // namespace ml5

// -------------------------------------------------------------------------------------------------

#include "./vector_iterator.inl"
