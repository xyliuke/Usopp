//
// Copyright (c) 2012 Artyom Beilis (Tonkikh)
//
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_NOWIDE_INTEGRATION_FILESYSTEM_HPP_INCLUDED
#define BOOST_NOWIDE_INTEGRATION_FILESYSTEM_HPP_INCLUDED

#include <boost/nowide/utf8_codecvt.hpp>
#include <boost/filesystem/path.hpp>

namespace boost {
namespace nowide {
    ///
    /// Install utf8_codecvt facet into boost::filesystem::path
    /// such that all char strings are interpreted as UTF-8 strings
    /// \return The previous imbued path locale.
    ///
    inline std::locale nowide_filesystem()
    {
        std::locale tmp = std::locale(std::locale(), new boost::nowide::utf8_codecvt<wchar_t>());
        return boost::filesystem::path::imbue(tmp);
    }
} // namespace nowide
} // namespace boost

#endif
