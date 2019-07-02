//
// Copyright (c) 2019 Mo Morsi (mo at devnull dot network)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef NUDB_DETAIL_STOP_WATCH_HPP
#define NUDB_DETAIL_STOP_WATCH_HPP

#include <chrono>

namespace nudb {
namespace detail {

struct stop_watch
{
    using clock = std::chrono::steady_clock;
    using time_point = clock::time_point;
    time_point start_;

    stop_watch() : start_(clock::now())
    {
    }

    std::chrono::duration<double>
    elapsed() const
    {
        return std::chrono::duration_cast<std::chrono::duration<double>>(
            clock::now() - start_);
    }
};


} // detail
} // nudb

#endif
