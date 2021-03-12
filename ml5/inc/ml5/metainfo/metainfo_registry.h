//       $Id: metainfo_registry.h 607 2019-11-02 22:46:30Z p27116 $
//      $URL: https://svn01.fh-hagenberg.at/se/minilib/ml5/trunk/product/ml5/inc/ml5/metainfo/metainfo_registry.h $
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

#include "./metainfo_base.h"

#define MI5_REGISTRY ml5::metainfo_registry::instance ()

namespace ml5 {

// -------------------------------------------------------------------------------------------------

class ML5_DLL_EXPORT metainfo_registry final {
   template <typename> friend struct metainfo;

   struct value_t final {
      std::string                           tunit;   // the translation unit, the meta-info object lives in
      util::wrapped_t <metainfo_base const> minfo;   // meta info (non owning)

      constexpr metainfo_base const & get_metainfo () const noexcept {
         return util::unwrap (minfo);
      }
   };

   using key_t      = std::type_index;
   using registry_t = std::unordered_multimap <std::type_index, value_t>;

   public:
      static metainfo_registry & instance () noexcept;

      metainfo_registry (metainfo_registry const &) = delete;
      metainfo_registry (metainfo_registry &&) = delete;

     ~metainfo_registry ();

      metainfo_registry & operator = (metainfo_registry const &) = delete;
      metainfo_registry & operator = (metainfo_registry &&) = delete;

      std::ostream & write (std::ostream & os = std::cout) const;

   private:
      metainfo_registry ();

      bool deregister (std::string const & tunit, metainfo_base const & minfo) noexcept;
      void enregister (std::string         tunit, metainfo_base const & minfo) noexcept;

      registry_t & m_registry;   // owning reference (because of DLL problems with cl)
};

// -------------------------------------------------------------------------------------------------

inline std::ostream & operator << (std::ostream & lhs, metainfo_registry const & rhs) {
   return rhs.write (lhs);
}

// -------------------------------------------------------------------------------------------------

}   // namespace ml5
