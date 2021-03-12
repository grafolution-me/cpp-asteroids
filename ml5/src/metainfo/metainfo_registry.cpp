//       $Id: metainfo_registry.cpp 624 2020-01-10 17:52:44Z p20068 $
//      $URL: https://svn01.fh-hagenberg.at/se/minilib/ml5/trunk/product/ml5/src/metainfo/metainfo_registry.cpp $
// $Revision: 624 $
//     $Date: 2020-01-10 18:52:44 +0100 (Fr., 10 Jän 2020) $
//   Creator: peter.kulczycki<AT>fh-hagenberg.at
//  Creation: June 1, 2018
//   $Author: p20068 $
// Copyright: (c) 2018 Peter Kulczycki (peter.kulczycki<AT>fh-hagenberg.at)
//            (c) 2018 Michael Hava (michael.hava<AT>fh-hagenberg.at)
//   License: This document contains proprietary information belonging to
//            University of Applied Sciences Upper Austria, Campus Hagenberg. It
//            is distributed under the Boost Software License, Version 1.0 (see
//            http://www.boost.org/LICENSE_1_0.txt).

#include "../../inc/ml5/metainfo/metainfo_registry.h"

namespace ml5 {

metainfo_registry & metainfo_registry::instance () noexcept {
   static metainfo_registry registry; return registry;
}

metainfo_registry::~metainfo_registry () {
   Expects (std::empty (m_registry)); delete &m_registry;
}

std::ostream & metainfo_registry::write (std::ostream & os) const {
   struct value_t final {
      value_t (std::string_view const t, metainfo_base const & m)
         : name    {m.name ()}
         , p_minfo {&m}
         , tunit   {t} {
      }

      constexpr metainfo_base const & get_metainfo () const noexcept {
         return util::deref (p_minfo);
      }

      std::string           name;                // name of the class this meta info manages
      metainfo_base const * p_minfo {nullptr};   // meta info (non owning)
      std::string           tunit;               // the translation unit, the meta-info object lives in
   };

   std::vector <value_t> sorted; sorted.reserve (std::size (m_registry));

   for (auto const & entry : m_registry) {
      sorted.emplace_back (entry.second.tunit, entry.second.get_metainfo ());
   }

   std::sort (std::begin (sorted), std::end (sorted), [] (value_t const & lhs, value_t const & rhs) {
      return (lhs.name < rhs.name) || ((lhs.name == rhs.name) && (lhs.tunit < rhs.tunit));
   });

   for (value_t const & entry : sorted) {
      os << "Type " << std::quoted (entry.name);

      if (entry.tunit != ML5_STRINGIZE_MACRO (ML5_TRANSLATION_UNIT_UNKNOWN)) {
         os << " registered in translation unit " << std::quoted (entry.tunit);
      }

      os << ".\n";
   }

   return os;
}

metainfo_registry::metainfo_registry () : m_registry {util::deref_new <registry_t> ()} {
}

bool metainfo_registry::deregister (std::string const & tunit, metainfo_base const & minfo) noexcept {
   auto const range {m_registry.equal_range (minfo.type ())};

   for (auto itor {range.first}; itor != range.second; ++itor) {
      if (itor->second.tunit == tunit) {
         m_registry.erase (itor); return true;
      }
   }

   return false;
}

void metainfo_registry::enregister (std::string tunit, metainfo_base const & minfo) noexcept {
   m_registry.emplace (minfo.type (), value_t {std::move (tunit), minfo});
}

}   // namespace ml5
